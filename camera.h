#ifndef CAMERA_H
#define CAMERA_H
#include <QOpenGLFunctions_4_1_Core>
#include <QVector3D>
#include <qmatrix4x4>

class Camera : public QOpenGLFunctions_4_1_Core {
public:
    Camera();

    ~Camera() {
    };
    void init(GLint pMatrixUniform, GLint vMatrixUniform);
    void perspective(int degrees, double aspect, double nearplane, double farplane);
    void lookAt(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
    void update();
    void translate(float dx, float dy, float dz);

private:
    GLint mPmatrixUniform; //OPenGL reference to the uniform in the shader program
    GLint mVmatrixUniform;
    QVector3D mEye;
    QMatrix4x4 mPmatrix{};
    QMatrix4x4 mVmatrix{}; //Going into the camera class
};

#endif // CAMERA_H
