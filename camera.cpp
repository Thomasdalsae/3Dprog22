#include "camera.h"

Camera::Camera() : mEye{0,0,0}
{
    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
}

void Camera::init(GLint pMatrixUniform, GLint vMatrixUniform)
{

    mPmatrix.setToIdentity();
    mVmatrix.setToIdentity();
    mPmatrixUniform = pMatrixUniform;
    mVmatrixUniform = vMatrixUniform;
}

void Camera::perspective(int degrees, double aspect, double nearplane, double farplane)
{
    mPmatrix.perspective(degrees,aspect,nearplane,farplane);
}

void Camera::lookAt(const QVector3D &eye, const QVector3D &at, const QVector3D &up)
{
    mVmatrix.lookAt(eye,at,up);
}

void Camera::update()
{
    initializeOpenGLFunctions();
    glUniformMatrix4fv(mPmatrixUniform,1,GL_FALSE,mPmatrix.constData()); // if using our own matrices use GL_TRUE INSTEAD
    glUniformMatrix4fv(mVmatrixUniform,1,GL_FALSE,mVmatrix.constData()); // if using our own matrices use GL_TRUE INSTEAD

}

void Camera::translate(float dx, float dy, float dz)
{
    mEye + QVector3D(dx, dy, dz);
}
