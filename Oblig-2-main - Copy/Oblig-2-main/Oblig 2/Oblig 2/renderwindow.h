#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLShaderProgram>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"
#include "xyz2.h"
#include "cube2.h"
#include "tetra2.h"
#include "trianglesurface.h"
#include "interobj.h"
#include "fxy.h"
#include "fx.h"
#include "lineobject.h"
#include "camera.h"
#include "octahedronball.h"
#include "parabel.h"
#include "x3curve.h"
#include "plane.h"
#include "cube3.h"
#include "house.h"
#include "pickup.h"
#include "door.h"
#include "oarpu.h"
#include "boat.h"
#include "texturedcube.h"
#include "heightmapread.h"

class QOpenGLContext;
class Shader;
class MainWindow;

class TexShader;

/// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core
{


    Q_OBJECT
public:
    RenderWindow(const QSurfaceFormat &format, MainWindow *mainWindow);
    ~RenderWindow() override;

    QOpenGLContext *context() { return mContext; }

    void exposeEvent(QExposeEvent *) override;  //gets called when app is shown and resized

    bool mRotate{true};     //Check if triangle should rotate
    bool rot{false};

    float back = -5;
    float side = 0;
    float up = 0;

    int index = 0;
    bool open = false;
    bool outside = true;

    int cyc = 0;
    int cyc2 = 0;
    bool all = false;
    int i = -12;

private slots:
    void render();          //the actual render - function
    void collision();

private:
    VisualObject* mia;

    void init();            //initialize things we need before rendering

//    std::vector<Vertex0> mVertices;

    QOpenGLContext *mContext{nullptr};  //Our OpenGL context
    bool mInitialized{false};

    Shader *mShaderProgram{nullptr};    //holds pointer the GLSL shader program
                //OpenGL reference to the Uniform in the shader program
    std::vector<VisualObject*> mObjects;
    Camera *mCamera;
    GLint  mPmatrixUniform;
    GLint  mVmatrixUniform;
    GLint  mMatrixUniform;

    GLint  texUniform;
    GLint  texVUniform;
    GLint  texPUniform;
                         //

    //QMatrix4x4 *mMVPmatrix{nullptr};      //  Erstatter denne med
    //QMatrix4x4 *mPmatrix{nullptr};         // denne,
    //QMatrix4x4 *mVmatrix{nullptr};         // og denne

    QOpenGLShaderProgram* textureShader;
    QOpenGLShaderProgram* plainShader;

    VisualObject* VSO;
    XYZ* xyz;
    fxy* FXY;
    fx* FX;
    HR* HM;


    CUBE* cooba;
    TETRA* tetra;
    TriangleSurface* TS;
    TriangleSurface* TS2;
    LineObject* LO;
    LineObject* LO2;
    OctahedronBall* OB;

    X3Curve* curvex3;

    PLANE* plane;
    house* HOUSE;
    DOOR* door;

    pickup* PU;
    pickup* PU1;
    pickup* PU2;
    pickup* PU3;
    pickup* PU4;
    pickup* PU5;
    pickup* PU6;

    Opickup* OAR;

    BOAT* boat;

    texCube* TC;


    player* player1;
    Vertex* camPosP;
    Vertex* end;
    Vertex* begin;
   // Parabel* PB;


    GLuint mVAO;                        //OpenGL reference to our VAO
    GLuint mVBO;                        //OpenGL reference to our VBO

    QTimer *mRenderTimer{nullptr};           //timer that drives the gameloop
    QElapsedTimer mTimeStart;               //time variable that reads the calculated FPS

    MainWindow *mMainWindow{nullptr};        //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger *mOpenGLDebugLogger{nullptr};  //helper class to get some clean debug info from OpenGL
    class Logger *mLogger{nullptr};         //logger - Output Log in the application

    ///Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate();          //as name says

    ///Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();

    void calcNorm(VisualObject* VO);

protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)
    //
    //    void mousePressEvent(QMouseEvent *event) override{}
    //    void mouseMoveEvent(QMouseEvent *event) override{}
    void keyPressEvent(QKeyEvent *event) override;              //the only one we use now
    //    void keyReleaseEvent(QKeyEvent *event) override{}
    //    void wheelEvent(QWheelEvent *event) override{}
};

#endif // RENDERWINDOW_H
