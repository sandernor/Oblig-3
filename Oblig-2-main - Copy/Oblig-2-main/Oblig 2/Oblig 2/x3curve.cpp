#include "x3curve.h"

X3Curve::X3Curve(bool inPoints)
{
    points = inPoints;
    mVertices.push_back(Vertex{1,3,0,0,1,0});
    mVertices.push_back(Vertex{3,0,0,0,1,0});
    mVertices.push_back(Vertex{4,2,0,0,1,0});
    mVertices.push_back(Vertex{6,-1,0,0,1,0});

    mMatrix.setToIdentity();
}

X3Curve::~X3Curve()
{

}

void X3Curve::init(GLint matrixUniform)
{
    mMatrixUniform = matrixUniform;

    //must call this to use OpenGL functions
    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    //VAO is a conntainer that holds VBOs
    glGenVertexArrays( 1, &mVAO );
    glBindVertexArray( mVAO );

    //Vertex Buffer Object to hold vertices - VBO
    //since the mVAO is bound, this VBO will belong to that VAO
    glGenBuffers( 1, &mVBO );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO );

    //send vertex data to the GPU
    glBufferData( GL_ARRAY_BUFFER,  //buffer type
                  mVertices.size()*sizeof( Vertex ),    //buffer size
                  mVertices.data(), //the vertices themselves
                  GL_STATIC_DRAW ); //whether we update the buffer on the GPU

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0,                                 //attribute - must match layout
                          3,                                 //size
                          GL_FLOAT,                          //data type
                          GL_FALSE,                          //normalized?
                          sizeof(Vertex),                    //stride
                          reinterpret_cast<GLvoid*>(0));     //array buffer offset
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    // Same paramater list as above, but attribute and offset are adjusted accordingly
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    //release vertex array bind(0) = release lol
    glBindVertexArray(0);
}

void X3Curve::draw()
{
//    //what object to draw
//    glBindVertexArray(mVAO);
//    //Since our shader uses a matrix and we rotate the triangle, we send the current matrix here
//    //Must be here to update each frame - if static object, it could be set only once
//    glUniformMatrix4fv(mMatrixUniform,          //the location of the matrix in the shader
//                       1,                       //count
//                       GL_FALSE,                //transpose the matrix before sending it?
//                       mMatrix.constData());    //the data of the matrix
//    //DRAW CALL MOMENT
//    if (points)
//        glDrawArrays(GL_POINTS, 0, mVertices.size());
//    else
//    {
//        glDrawArrays(GL_LINES, 0, mVertices.size());
//        //qDebug() << "Sheesh" << mVertices.size();
//    }
}

void X3Curve::generate()
{
    x = QVector4D{a,b,c,d};

    for (int i = 0; i < mVertices.size(); i++)
    {
        B[i] = mVertices[i].m_xyz[1];
    }

    for (int i = 0; i < mVertices.size(); i++)
    {
        int v = mVertices.size()-1;
        for (int j = 0; j < mVertices.size(); j++)
        {
             A(i,j) = pow(mVertices[i].m_xyz[0], v);
             v-=1;
        }
    }

    x = A.inverted()*B;
    a = x[0];
    b = x[1];
    c = x[2];
    d = x[3];

}

void X3Curve::curvePoints(double xMin, double xMax)
{
    mVertices.clear();
    double h = 0.05f;
    for (double x = xMin; x < xMax; x += h)
    {
        mVertices.push_back(Vertex{static_cast<float>(x),static_cast<float>(xFunction(x)),0,0.8,0,1});
    }
    mMatrix.setToIdentity();

    for(int i = 0; i < mVertices.size(); i++)
    {
        if (mVertices[i].m_xyz[1] < -0.1)
        {
            mVertices.erase(mVertices.begin() +i);
        }
         mVertices[i].m_xyz[0] = mVertices[i].m_xyz[0] * 0.1f;
         mVertices[i].m_xyz[1] = mVertices[i].m_xyz[1] * 0.05f;
         mVertices[i].m_xyz[2] = mVertices[i].m_xyz[2] * 0.1f;
    }

//    rotate();
//    mMatrix.setToIdentity();

//    move(-2, 0, -0.5);
//    mMatrix.setToIdentity();
}

void X3Curve::rotate()
{
    mMatrix.rotate(90.f, 1.f, 0.0, 0.f);
}

void X3Curve::move1()
{
    mMatrix.translate(-1.8, -0.7, 0);
}

double X3Curve::xFunction(double x) const
{
    return a * x * x * x + b * x * x + c * x + d;
}
