#include "camera.h"

Camera::Camera() : mEye(0,0,0)
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
}

//Camera::~Camera()
//{

//}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;
    translate(0,0,-10.f);
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees, aspect, nearplane, farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.setToIdentity();
    mVmatrix.lookAt(eye, at, up);
    mVmatrix.inverted();
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform, 1, GL_FALSE, mPmatrix.constData());
    glUniformMatrix4fv(mVmatrixUniform, 1, GL_FALSE, mVmatrix.constData());
}

void Camera::translate(float dx, float dy, float dz)
{
    mVmatrix.translate(dx, dy, dz);
}

void Camera::rotate(float x, float y, float z, float a)
{
    mPmatrix.rotate(x,y,z,a);
}

void Camera::cameraCirk()
{

}
