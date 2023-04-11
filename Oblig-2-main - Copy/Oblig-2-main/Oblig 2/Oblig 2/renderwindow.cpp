#include "renderwindow.h"
#include <QTimer>
#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLDebugLogger>
#include <QKeyEvent>
#include <QStatusBar>
#include <QDebug>

#include <string>

#include "shader.h"
#include "mainwindow.h"
#include "logger.h"

RenderWindow::RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow)
    : mContext(nullptr), mInitialized(false), mMainWindow(mainWindow)

{
    //This is sent to QWindow:
    setSurfaceType(QWindow::OpenGLSurface);
    setFormat(format);
    //Make the OpenGL context
    mContext = new QOpenGLContext(this);
    //Give the context the wanted OpenGL format (v4.1 Core)
    mContext->setFormat(requestedFormat());
    if (!mContext->create()) {
        delete mContext;
        mContext = nullptr;
        qDebug() << "Context could not be made - quitting this application";
    }

    //This is the matrix used to transform (rotate) the triangle
    //You could do without, but then you have to simplify the shader and shader setup
/*    mMVPmatrix = new QMatrix4x4{};
    mMVPmatrix->setToIdentity(); */   //1, 1, 1, 1 in the diagonal of the matrix
//    mVmatrix = new QMatrix4x4{};
//    mPmatrix = new QMatrix4x4{};
//    mVmatrix->setToIdentity();    //1, 1, 1, 1 in the diagonal of the matrix/    mPmatrix = new QMatrix4x4{};
//    mPmatrix->setToIdentity();    //1, 1, 1, 1 in the diagonal of the matrix

    mCamera = new Camera();

    //Make the gameloop timer:
    mRenderTimer = new QTimer(this);

    //mObjects.push_back(new XYZ());
    //mObjects.push_back(new TriangleSurface());
    //mObjects.push_back(new CUBE());
    //mObjects.push_back(new TETRA());
   // mObjects.push_back(new InterObj());
//    VSO = new InterObj();
//    mObjects.push_back(VSO);

//    xyz = new XYZ();
//    mObjects.push_back(xyz);

    FXY = new fxy();
    mObjects.push_back(FXY);

    tetra = new TETRA();
    mObjects.push_back(tetra);

//    FX = new fx();
//    mObjects.push_back(FX);

    TS = new TriangleSurface();
    mObjects.push_back(TS);

    TS2 = new TriangleSurface();
    mObjects.push_back(TS2);

//    LO = new LineObject();
//    mObjects.push_back(LO);

//    LO2 = new LineObject();
//    mObjects.push_back(LO);

//    cube = new CUBE();
//    mObjects.push_back(cube);

//    OB = new OctahedronBall(3);
//    mObjects.push_back(OB);

    cooba = new CUBE;
    mObjects.push_back(cooba);

//    Parabel* points = new Parabel(true);
//    mObjects.push_back(points);
//    Parabel* parCurve = new Parabel(false);
//    parCurve->matrixSet(parCurve->mVertices);
//    parCurve->curvePoints(-5, 20);
////    pApprox->write("parabel");
//    mObjects.push_back(parCurve);

    X3Curve* pointsx3 = new X3Curve(true);
    mObjects.push_back(pointsx3);
    curvex3 = new X3Curve(false);
    curvex3->generate();
    curvex3->curvePoints(0.5, 6);
//    pApprox->write("parabel");
    mObjects.push_back(curvex3);

    HOUSE = new house();
    mObjects.push_back(HOUSE);

    door = new DOOR();
    mObjects.push_back(door);

    plane = new PLANE();
    mObjects.push_back(plane);

    PU = new pickup();
    PU1 = new pickup();
    PU2 = new pickup();
    PU3 = new pickup();
    PU4 = new pickup();
    PU5 = new pickup();
    PU6 = new pickup();
    mObjects.push_back(PU);
    mObjects.push_back(PU1);
    mObjects.push_back(PU2);
    mObjects.push_back(PU3);
    mObjects.push_back(PU4);
    mObjects.push_back(PU5);
    mObjects.push_back(PU6);

    OAR = new Opickup();
    mObjects.push_back(OAR);

//    boat = new BOAT();
//    mObjects.push_back(boat);


    player1 = new player();
    mObjects.push_back(player1);

    TC = new texCube;
    mObjects.push_back(TC);

    HM = new HR();
    mObjects.push_back(TC);

}

RenderWindow::~RenderWindow()
{
    //cleans up the GPU memory
    glDeleteVertexArrays( 1, &mVAO );
    glDeleteBuffers( 1, &mVBO );
}

// Sets up the general OpenGL stuff and the buffers needed to render a triangle
void RenderWindow::init()
{
    //Get the instance of the utility Output logger
    //Have to do this, else program will crash (or you have to put in nullptr tests...)
    mLogger = Logger::getInstance();

    //Connect the gameloop timer to the render function:
    //This makes our render loop
    connect(mRenderTimer, SIGNAL(timeout()), this, SLOT(render()));
    //********************** General OpenGL stuff **********************

    //The OpenGL context has to be set.
    //The context belongs to the instanse of this class!
    if (!mContext->makeCurrent(this)) {
        mLogger->logText("makeCurrent() failed", LogType::REALERROR);
        return;
    }

    //just to make sure we don't init several times
    //used in exposeEvent()
    if (!mInitialized)
        mInitialized = true;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Print render version info (what GPU is used):
    //Nice to see if you use the Intel GPU or the dedicated GPU on your laptop
    // - can be deleted
    mLogger->logText("The active GPU and API:", LogType::HIGHLIGHT);
    std::string tempString;
    tempString += std::string("  Vendor: ") + std::string((char*)glGetString(GL_VENDOR)) + "\n" +
            std::string("  Renderer: ") + std::string((char*)glGetString(GL_RENDERER)) + "\n" +
            std::string("  Version: ") + std::string((char*)glGetString(GL_VERSION));
    mLogger->logText(tempString);

    //Start the Qt OpenGL debugger
    //Really helpfull when doing OpenGL
    //Supported on most Windows machines - at least with NVidia GPUs
    //reverts to plain glGetError() on Mac and other unsupported PCs
    // - can be deleted
    startOpenGLDebugger();

    //general OpenGL stuff:
    glEnable(GL_DEPTH_TEST);            //enables depth sorting - must then use GL_DEPTH_BUFFER_BIT in glClear
    //    glEnable(GL_CULL_FACE);       //draws only front side of models - usually what you want - test it out!
    glClearColor(0.4f, 0.4f, 0.4f, 1.0f);    //gray color used in glClear GL_COLOR_BUFFER_BIT

    //Compile shaders:
    //NB: hardcoded path to files! You have to change this if you change directories for the project.
    //Qt makes a build-folder besides the project folder. That is why we go down one directory
    // (out of the build-folder) and then up into the project folder.
    plainShader = new QOpenGLShaderProgram();

    plainShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../Oblig 2/plainshader.vert");
    plainShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../Oblig 2/plainshader.frag");

    plainShader->link();

    mMatrixUniform = glGetUniformLocation(plainShader->programId(), "mmatrix");
    mPmatrixUniform = glGetUniformLocation(plainShader->programId(), "ppmatrix");
    mVmatrixUniform = glGetUniformLocation(plainShader->programId(), "vvmatrix");


    camPosP = &player1->camCirk[index];
    QVector3D cameraPosition{camPosP->m_xyz[0],camPosP->m_xyz[1],camPosP->m_xyz[2]};

    plainShader->bind();
    plainShader->setUniformValue("lightPosition", QVector3D(1.0f, 1.5f, -1.0f));
    plainShader->setUniformValue("cameraPosition", cameraPosition);
    plainShader->setUniformValue("materialAmbient", QVector3D(0.2f, 0.2f, 0.2f));
    plainShader->setUniformValue("materialDiffuse", QVector3D(0.8f, 0.8f, 0.8f));
    plainShader->setUniformValue("materialSpecular", QVector3D(1.0f, 1.0f, 1.0f));

    plainShader->release();





    // Get the matrixUniform location from the shader
    // This has to match the "matrix" variable name in the vertex shader
    // The uniform is used in the render() function to send the model matrix to the shader
    // Flere matriser her! Skal legges inn i kameraklasse
//    mPmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "pmatrix" );
//    mVmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "vmatrix" );

//    mMatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "matrix" );
//    mPmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "pmatrix" );
//    mVmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "vmatrix" );
    //mCamera.init(mPmatrixUniform, mVmatrixUniform);

    textureShader = new QOpenGLShaderProgram();

    textureShader->addShaderFromSourceFile(QOpenGLShader::Vertex, "../Oblig 2/textureShader.vert");
    textureShader->addShaderFromSourceFile(QOpenGLShader::Fragment, "../Oblig 2/textureShader.frag");

    textureShader->link();

    texUniform = glGetUniformLocation(textureShader->programId(), "matrix");
    texPUniform = glGetUniformLocation(textureShader->programId(), "pmatrix");
    texVUniform = glGetUniformLocation(textureShader->programId(), "vmatrix");

    textureShader->bind();
    textureShader->setUniformValue("textureSampler", 0);
    textureShader->release();

//    mMatrixUniform = glGetUniformLocation( textureShader->programId(), "matrix" );
//    mPmatrixUniform = glGetUniformLocation( textureShader->programId(), "pmatrix" );
//    mVmatrixUniform = glGetUniformLocation( textureShader->programId(), "vmatrix" );

    FXY->write("filnavn");
    TS->readFile("filnavn");

    HM->write("heightData");
    TS2->readFile("heightData");
//    FX->write("kurve");
//    LO->readFile("kurve");
    //LO2->readFile("parabel");
    //qDebug()<<FX->numInt();

    glPointSize(5);





    mia = xyz;


    for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
    {

        if ((*it) != TC)
        {
            (*it)->init(mMatrixUniform);
        }
        else
        {
            (*it)->init(texUniform);
        }



    }
    glBindVertexArray(0);       //unbinds any VertexArray - good practice

//    for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
//    {
//        i+=5;


//        (*it)->move(i,0,0);

//    }

    HOUSE->move(-0.5, 0, 0.5);
    door->move(-0.575, 0, 0.125);

    PU->move(-1.5, 1.05, 0.5);
    PU1->move(2.5, 1.05, -1.5);
    PU2->move(0.5, 0.05, 0.5);
    PU3->move(2.5, -0.05, 1.5);
//    PU4->move(-1.5, 1.05, -1.5);
//    PU5->move(-0.4, 0.05, 0.7);
//    PU6->move(-0.6, 0.05, 0.7);

    OAR->move(-0.5, 0, 0.7);
//    boat->move(0, -1, 0);

    curvex3->rotate();
    curvex3->move1();

    tetra->move(-1.3, -0.1, -0.4);
    //tetra->mPosition = QVector3D{-1.3, -0.1, -0.4};

    TC->move(0.5, 0.2, 0.5);
    TS2->move(5, -1, 5);

    cooba->move(-2.5f, 1.5f, -2.5f);
}

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{
//    mPmatrix->setToIdentity();
//    mVmatrix->setToIdentity();
//    mMatrixUniform = glGetUniformLocation( plainShader->programId(), "matrix" );
//    mPmatrixUniform = glGetUniformLocation( plainShader->programId(), "pmatrix" );
//    mVmatrixUniform = glGetUniformLocation( plainShader->programId(), "vmatrix" );

    collision();

    mCamera->init(mPmatrixUniform, mVmatrixUniform);
    mCamera->perspective(60, 16.0/9.0, 0.1, 50.0);
    mCamera->translate(side,up,back);

    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    //initializeOpenGLFunctions();    //must call this every frame it seems...

    //clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //what shader to use
    //glUseProgram(mShaderProgram->getProgram());
    plainShader->bind();
    plainShader->setUniformValue("ppmatrix", mCamera->mPmatrix);
    plainShader->setUniformValue("vvmatrix", mCamera->mVmatrix);

    camPosP = &player1->camCirk[index];
    QVector3D cameraPosition{camPosP->m_xyz[0],camPosP->m_xyz[1],camPosP->m_xyz[2]};
    plainShader->setUniformValue("cameraPosition", cameraPosition);

    up = player1->m_xyz[1]+1;
    camPosP = &player1->camCirk[index];
    //plainShader->setUniformValue("cameraPosition", cameraPosition);


    double x;
    double z;
    x = player1->m_xyz[0];
    z = player1->m_xyz[2];

    if (x > -0.875 && z > 0.125 && x < -0.125 && z < 0.875)
    {
        mCamera->lookAt(QVector3D{-0.8, 0.7, 0.15}, QVector3D{player1->m_xyz[0],player1->m_xyz[1],player1->m_xyz[2]}, QVector3D{0,1,0});
    }
    else
    {
        mCamera->lookAt(QVector3D{player1->m_xyz[0]+camPosP->m_xyz[0],up,player1->m_xyz[2]+camPosP->m_xyz[2]}, QVector3D{player1->m_xyz[0],player1->m_xyz[1],player1->m_xyz[2]}, QVector3D{0,1,0});
    }



   // Flere matriser her! Skal legges i kameraklasse
   //glUniformMatrix4fv( mPmatrixUniform, 1, GL_FALSE, mPmatrix->constData());
   //glUniformMatrix4fv( mVmatrixUniform, 1, GL_FALSE, mVmatrix->constData());

    mCamera->update();

    for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
    {
        //(*it)->draw();

//        if (player1->m_xyz[1] < -0.09)
//            player1->drawBoat();

        if (*it != TC)
        {
            plainShader->setUniformValue("mmatrix", (*it)->mMatrix);
            (*it)->draw();
        }

    }

    plainShader->release();
//    mMatrixUniform = glGetUniformLocation( textureShader->programId(), "matrix" );
//    mPmatrixUniform = glGetUniformLocation( textureShader->programId(), "pmatrix" );
//    mVmatrixUniform = glGetUniformLocation( textureShader->programId(), "vmatrix" );
    textureShader->bind();



    textureShader->setUniformValue("pmatrix", mCamera->mPmatrix);
    textureShader->setUniformValue("vmatrix", mCamera->mVmatrix);
    textureShader->setUniformValue("matrix", TC->mMatrix);
    TC->draw();
    textureShader->release();




    //Calculate framerate before
    // checkForGLerrors() because that call takes a long time
    // and before swapBuffers(), else it will show the vsync time
    calculateFramerate();

    //using our expanded OpenGL debugger to check if everything is OK.
    checkForGLerrors();

    //Qt require us to call this swapBuffers() -function.
    // swapInterval is 1 by default which means that swapBuffers() will (hopefully) block
    // and wait for vsync.
    mContext->swapBuffers(this);

    //just to make the triangle rotate - tweak this:
    //                   degree, x,   y,   z -axis

    if(mRotate)
    {
        for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
        {
            if (*it==PU || *it==PU1 || *it==PU2 || *it==PU3 || *it==PU4 || *it==PU5 || *it==PU6 || *it==OAR || *it==TC)
                (*it)->rotate();

                //(*it)->rotate();

        }
        //mMVPmatrix->rotate(1.f, 0.f, 1.0, 0.f);
    }


    FXY->collision(player1, boat);



    bool check = door->collision(player1);
    if(check == true)
    {
        if (door->once == false)
            door->rotate();
        qDebug() << check;

        open = true;
    }

    if (player1->m_xyz[0] < -1.1 && player1->m_xyz[0] > -1.9 && player1->m_xyz[2] < -0.1 && player1->m_xyz[2] > -0.9)
        tetra->attack = true;
    else
    {
        tetra->attack = false;
        tetra->done2 = false;
        if (tetra->done == false)
        tetra->move(tetra->mPosition.x()-tetra->LastPos.x(), 0.1f, tetra->mPosition.z()-tetra->LastPos.z());
    }

    if (tetra->attack == false)
        tetra->move(0.001, curvex3->a, curvex3->b, curvex3->c, curvex3->d);
    else
        tetra->move(player1);
    //else


//    if (player1->m_xyz[1] < -0.95)
//        player1->drawBoat();
//    else
//        for(int i = 61; i < player1->mVertices.size(); i++)
//        {
//            player1->mVertices.erase(player1->mVertices.begin()+i);
//        }




}

void RenderWindow::collision()
{
    qDebug() << "player"<< player1->m_xyz[0] << "___" << player1->m_xyz[2];
    qDebug() << "PU1"<< PU1->pickPos[0] << "___" << PU1->pickPos[2];
    qDebug() << "PU2"<< PU2->pickPos[0] << "___" << PU2->pickPos[2];
    qDebug() << "PU3"<< PU3->pickPos[0] << "___" << PU3->pickPos[2];
    qDebug() << "PU0"<< PU->pickPos[0] << "___" << PU->pickPos[2];
    qDebug() << "OAR"<< OAR->pickPos[0] << "___" << OAR->pickPos[2];



    if(player1->m_xyz[0] > -1.5-0.05f && player1->m_xyz[0] < -1.5+0.05f && player1->m_xyz[2] > 0.5-0.05f && player1->m_xyz[2] < 0.5+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 2.5-0.05f && player1->m_xyz[0] < 2.5+0.05f && player1->m_xyz[2] > -1.5-0.05f && player1->m_xyz[2] < -1.5+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU1)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 0.5-0.05f && player1->m_xyz[0] < 0.5+0.05f && player1->m_xyz[2] > 0.5-0.05f && player1->m_xyz[2] < 0.5+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU2)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 2.5-0.05f && player1->m_xyz[0] < 2.5+0.05f && player1->m_xyz[2] > 1.5-0.05f && player1->m_xyz[2] < 1.5+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU3)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 0-0.05f && player1->m_xyz[0] < 0+0.05f && player1->m_xyz[2] > 0-0.05f && player1->m_xyz[2] < 0+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU4)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 0-0.05f && player1->m_xyz[0] < 0+0.05f && player1->m_xyz[2] > 0-0.05f && player1->m_xyz[2] < 0+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU5)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }
    if(player1->m_xyz[0] > 0-0.05f && player1->m_xyz[0] < 0+0.05f && player1->m_xyz[2] > 0-0.05f && player1->m_xyz[2] < 0+0.05f)
    {
        for(int i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == PU6)
            {
                mObjects.erase(mObjects.begin()+i);
            }
        }
    }

//    if(player1->m_xyz[0] > OAR->pickPos[0]-0.08f && player1->m_xyz[0] < OAR->pickPos[0]+0.08f && player1->m_xyz[2] > OAR->pickPos[2]-0.08f && player1->m_xyz[2] < OAR->pickPos[2]+0.08f)
//    {
//        qDebug() << "cock n balls";
//        for(unsigned long long i = 0; i < mObjects.size()-1; i++)
//        {
//            if (mObjects[i] == OAR)
//            {
//                mObjects.erase(mObjects.begin()+i);
//                qDebug() << "cock n balls";
//            }
//            player1->boat = true;
//        }
//    }

    //OAR
    if(player1->m_xyz[0] > -0.5-0.08f && player1->m_xyz[0] < -0.5+0.08f && player1->m_xyz[2] > 0.7-0.08f && player1->m_xyz[2] < 0.7+0.08f)
    {
        qDebug() << "cock n balls";
        for(unsigned long long i = 0; i < mObjects.size()-1; i++)
        {
            if (mObjects[i] == OAR)
            {
                mObjects.erase(mObjects.begin()+i);
                qDebug() << "cock n balls";
            }
            player1->boat = true;
        }
    }

    //OAR->move(-0.5, 0, 0.7);

}

//This function is called from Qt when window is exposed (shown)
// and when it is resized
//exposeEvent is a overridden function from QWindow that we inherit from
void RenderWindow::exposeEvent(QExposeEvent *)
{
    //if not already initialized - run init() function - happens on program start up
    if (!mInitialized)
        init();

    //This is just to support modern screens with "double" pixels (Macs and some 4k Windows laptops)
    const qreal retinaScale = devicePixelRatio();

    //Set viewport width and height to the size of the QWindow we have set up for OpenGL
    glViewport(0, 0, static_cast<GLint>(width() * retinaScale), static_cast<GLint>(height() * retinaScale));

    //If the window actually is exposed to the screen we start the main loop
    //isExposed() is a function in QWindow
    if (isExposed())
    {
        //This timer runs the actual MainLoop
        //16 means 16ms = 60 Frames pr second (should be 16.6666666 to be exact...)
        mRenderTimer->start(16);
        mTimeStart.start();
    }
}

//The way this function is set up is that we start the clock before doing the draw call,
// and check the time right after it is finished (done in the render function)
//This will approximate what framerate we COULD have.
//The actual frame rate on your monitor is limited by the vsync and is probably 60Hz
void RenderWindow::calculateFramerate()
{
    long nsecElapsed = mTimeStart.nsecsElapsed();
    static int frameCount{0};                       //counting actual frames for a quick "timer" for the statusbar

    if (mMainWindow)            //if no mainWindow, something is really wrong...
    {
        ++frameCount;
        if (frameCount > 30)    //once pr 30 frames = update the message == twice pr second (on a 60Hz monitor)
        {
            //showing some statistics in status bar
            mMainWindow->statusBar()->showMessage(" Time pr FrameDraw: " +
                                                  QString::number(nsecElapsed/1000000.f, 'g', 4) + " ms  |  " +
                                                  "FPS (approximated): " + QString::number(1E9 / nsecElapsed, 'g', 7));
            frameCount = 0;     //reset to show a new message in 30 frames
        }
    }
}

//Uses QOpenGLDebugLogger if this is present
//Reverts to glGetError() if not
void RenderWindow::checkForGLerrors()
{
    if(mOpenGLDebugLogger)  //if our machine got this class to work
    {
        const QList<QOpenGLDebugMessage> messages = mOpenGLDebugLogger->loggedMessages();
        for (const QOpenGLDebugMessage &message : messages)
        {
            if (!(message.type() == message.OtherType)) // get rid of uninteresting "object ...
                                                        // will use VIDEO memory as the source for
                                                        // buffer object operations"
                // valid error message:
                mLogger->logText(message.message().toStdString(), LogType::REALERROR);
        }
    }
    else
    {
        GLenum err = GL_NO_ERROR;
        while((err = glGetError()) != GL_NO_ERROR)
        {
            mLogger->logText("glGetError returns " + std::to_string(err), LogType::REALERROR);
            switch (err) {
            case 1280:
                mLogger->logText("GL_INVALID_ENUM - Given when an enumeration parameter is not a "
                                "legal enumeration for that function.");
                break;
            case 1281:
                mLogger->logText("GL_INVALID_VALUE - Given when a value parameter is not a legal "
                                "value for that function.");
                break;
            case 1282:
                mLogger->logText("GL_INVALID_OPERATION - Given when the set of state for a command "
                                "is not legal for the parameters given to that command. "
                                "It is also given for commands where combinations of parameters "
                                "define what the legal parameters are.");
                break;
            }
        }
    }
}

//Tries to start the extended OpenGL debugger that comes with Qt
//Usually works on Windows machines, but not on Mac...
void RenderWindow::startOpenGLDebugger()
{
    QOpenGLContext * temp = this->context();
    if (temp)
    {
        QSurfaceFormat format = temp->format();
        if (! format.testOption(QSurfaceFormat::DebugContext))
            mLogger->logText("This system can not use QOpenGLDebugLogger, so we revert to glGetError()",
                             LogType::HIGHLIGHT);

        if(temp->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        {
            mLogger->logText("This system can log extended OpenGL errors", LogType::HIGHLIGHT);
            mOpenGLDebugLogger = new QOpenGLDebugLogger(this);
            if (mOpenGLDebugLogger->initialize()) // initializes in the current context
                mLogger->logText("Started Qt OpenGL debug logger");
        }
    }
}

void RenderWindow::calcNorm(VisualObject*VO)
{
    QVector<QVector3D> vertPos;
    QVector<QVector3D> faceNormals;
    QVector<int> index;

    for(int i = 0; i < VO->mVertices.size(); i++)
    {
        index[i] = VO->mVertices[i].index;
        vertPos[i] = QVector3D{VO->mVertices[i].m_xyz[0], VO->mVertices[i].m_xyz[1], VO->mVertices[i].m_xyz[2]};
    }

    for (int i = 0; i < index.size(); i += 3)
    {
        QVector3D v0 = vertPos[index[i]];
        QVector3D v1 = vertPos[index[i + 1]];
        QVector3D v2 = vertPos[index[i + 2]];
        QVector3D e1 = v1 - v0;
        QVector3D e2 = v2 - v0;
        QVector3D normal = QVector3D::crossProduct(e1, e2);
        faceNormals.append(normal.normalized());
    }

    // Calculate vertex normals
    QVector<QVector3D> vertexNormals(vertPos.size());
    for (int i = 0; i < index.size(); i += 3)
    {
        int i0 = index[i];
        int i1 = index[i + 1];
        int i2 = index[i + 2];
        vertexNormals[i0] += faceNormals[i / 3];
        vertexNormals[i1] += faceNormals[i / 3];
        vertexNormals[i2] += faceNormals[i / 3];
    }

    for (int i = 0; i < vertexNormals.size(); i++) {
        vertexNormals[i].normalize();
        VO->mVertices[i].vNorm = vertexNormals[i];
    }

}

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();       //Shuts down the whole program
    }

    if (event->key() == Qt::Key_D)
    {
        //VSO->move(0.1,0,0);
//        TS->move(0.1,0,0);
//        cube->move(0.1,0,0);
//        mia->move(0.1,0,0);
        //side +=0.1;
        player1->rotate2();
    }

    if (event->key() == Qt::Key_W)
    {
        //VSO->move(0,0.1,0);
//        TS->move(0,0.1,0);
//        cube->move(0,0.1,0);
//        mia->move(0,0.1,0);
        //back +=0.1;
    }

    if (event->key() == Qt::Key_A)
    {
        //VSO->move(-0.1,0,0);
//        TS->move(-0.1,0,0);
//        cube->move(-0.1,0,0);
//        mia->move(-0.1,0,0);
        //side -=0.1;
        player1->rotate();
    }

    if (event->key() == Qt::Key_S)
    {
        //VSO->move(0,-0.1,0);
//        TS->move(0,-0.1,0);
//        cube->move(0,-0.1,0);
//        mia->move(0,-0.1,0);
        //back -=0.1;
    }

    if (event->key() == Qt::Key_Q)
    {
        //VSO->move(0,-0.1,0);
//        TS->move(0,-0.1,0);
//        cube->move(0,-0.1,0);
//        mia->move(0,-0.1,0);
        //up +=0.1;
        if (index != 7)
            index += 1;
        else if (index == 7)
            index = 0;
    }

    if (event->key() == Qt::Key_E)
    {
        //VSO->move(0,-0.1,0);
//        TS->move(0,-0.1,0);
//        cube->move(0,-0.1,0);
//        mia->move(0,-0.1,0);
        //up -=0.1;
        if (index != 0)
            index -= 1;
        else if (index == 0)
            index = 7;

    }

    if (event->key() == Qt::Key_I)
    {
        //VSO->move(0.1,0,0);
        //TS->rotate(1,-1,0,0);
        //mCamera->translate(0,0,-4.f);
//        if (open != true)
//        {
//            if (HOUSE->collision(player1, 0, 0.02) == false)
//                player1->move(0,0,0.02);
//        }
//        else
//        {
//            player1->move(0,0,0.02);
//        }
        if (open == true)
        {
            if (door->collision(player1) == true)
                player1->move(0,0,0.02);
            else if (HOUSE->collision(player1, 0, 0.04) == true)
                player1->move(0,0,0.02);
            else if (door->collision(player1) != true && HOUSE->collision(player1, 0, 0) != true)
                open = false;
        }
        else if (open != true)
        {
            if (HOUSE->collision(player1, 0, 0.02) == false)
                player1->move(0,0,0.02);
        }

    }

    if (event->key() == Qt::Key_J)
    {
        //VSO->move(0,0.1,0);
        //TS->rotate(1,0,-1,0);
        //mCamera->rotate(1,0,-1,0);
        if (open == true)
        {
            if (door->collision(player1) == true)
                player1->move(0.02,0,0);
            else if (HOUSE->collision(player1, 0.04, 0) == true)
                player1->move(0.02,0,0);
            else if (door->collision(player1) != true && HOUSE->collision(player1, 0, 0) != true)
                open = false;
        }
        else if (open != true)
        {
            if (HOUSE->collision(player1, 0.02, 0) == false)
                player1->move(0.02,0,0);
        }
    }

    if (event->key() == Qt::Key_K)
    {
        //VSO->move(-0.1,0,0);
        //TS->rotate(1,1,0,0);
//        if (open != true)
//        {
//            if (HOUSE->collision(player1, 0, -0.02) == false)
//                player1->move(0,0,-0.02);
//        }
//        else
//        {
//            player1->move(0,0,-0.02);
//        }

        if (open == true)
        {
            if (door->collision(player1) == true)
                player1->move(0,0,-0.02);
            else if (HOUSE->collision(player1, 0, -0.04) == true)
                player1->move(0,0,-0.02);
            else if (door->collision(player1) != true && HOUSE->collision(player1, 0, 0) != true)
                open = false;
        }
        else if (open != true)
        {
            if (HOUSE->collision(player1, 0, -0.02) == false)
                player1->move(0,0,-0.02);
        }
    }

    if (event->key() == Qt::Key_L)
    {
        //VSO->move(0,-0.1,0);
        //TS->rotate(1,0,1,0);
//        if (open != true)
//        {
//            if (HOUSE->collision(player1, -0.02, 0) == false)
//                player1->move(-0.02,0,0);
//        }
//        //HAIL SATAN

//        else
//        {
//            player1->move(-0.02,0,0);
//        }
        if (open == true)
        {
            if (door->collision(player1) == true)
                player1->move(-0.02,0,0);
            else if (HOUSE->collision(player1, -0.04, 0) == true)
                player1->move(-0.02,0,0);
            else if (door->collision(player1) != true && HOUSE->collision(player1, 0, 0) != true)
                open = false;
        }
        else if (open != true)
        {
            if (HOUSE->collision(player1, -0.02, 0) == false)
                player1->move(-0.02,0,0);
        }
    }

    if (event->key() == Qt::Key_C)
    {
//        cyc += 1;

//        if (cyc > 6)
//            cyc = 0;

//        switch (cyc)
//        {
//            case 0:
//            all = false;

////            for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
////            {

////                (*it)->move(-1*i,0,0);

////                i-=5;

////            }

//                mia = xyz;
//            break;

//            case 1:
//            mia = cube;
//        break;
//            case 2:
//            mia = TS;
//        break;

//            case 3:
//            mia = LO;
//        break;
//            case 4:
//            mia = tetra;
//        break;
//        case 5:
//            mia = OB;
//            break;
//        case 6:
//            all = true;

////            for(auto it=mObjects.begin(); it!=mObjects.end(); it++)
////            {
////                i+=5;


////                (*it)->move(i,0,0);

////            }

//            //i = -12;

//            break;
//        }
    }

    //You get the keyboard input like this
//    if(event->key() == Qt::Key_A)
//    {
//        mMainWindow->statusBar()->showMessage(" AAAA");
//    }
//    if(event->key() == Qt::Key_S)
//    {
//        mMainWindow->statusBar()->showMessage(" SSSS");
    //    }
}

