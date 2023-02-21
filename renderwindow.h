#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions_4_1_Core>
#include <QTimer>
#include <QElapsedTimer>
#include <vector>

#include "visualobject.h"
#include "camera.h"

#include "octahedronball.h"
#include "disc.h"
#include "graphpoints.h"

class QOpenGLContext;
class Shader;
class MainWindow;

/// This inherits from QWindow to get access to the Qt functionality and
// OpenGL surface.
// We also inherit from QOpenGLFunctions, to get access to the OpenGL functions
// This is the same as using "glad" and "glw" from general OpenGL tutorials
class RenderWindow : public QWindow, protected QOpenGLFunctions_4_1_Core {
    Q_OBJECT

public:
    RenderWindow(const QSurfaceFormat& format, MainWindow* mainWindow);
    ~RenderWindow() override;

    QOpenGLContext* context() {
        return mContext;
    }

    void exposeEvent(QExposeEvent*) override; //gets called when app is shown and resized

    bool mRotate{false}; //Check if triangle should rotate
    bool XYZ_render{false};
    bool Curve_render{false};
    bool Plane_render{false};
    bool Cube_render{false};
    bool drawNormals{false};
    bool Disc_render{false};
    bool GrapPoints_render{false};

private
    slots:
    
    void render(); //the actual render - function

private:
    //Vertex m_v;
    //Disc disc{};
    std::map<int, bool> pressedKeys{};
    std::vector<VisualObject*> mObjects;
    VisualObject* mia;
    Camera mCamera{};
    void init(); //initialize things we need before rendering

    QOpenGLContext* mContext{nullptr}; //Our OpenGL context
    bool mInitialized{false};

    Shader* mShaderProgram{nullptr}; //holds pointer the GLSL shader program

    GLint mPmatrixUniform; //OPenGL reference to the uniform in the shader program
    GLint mVmatrixUniform;
    GLint mMmatrixUniform;

    GLuint mVAO; //OpenGL reference to our VAO
    GLuint mVBO; //OpenGL reference to our VBO


    QMatrix4x4* mMVPmatrix{nullptr}; //The matrix with the transform for the object we draw
    QMatrix4x4* mPmatrix{nullptr};
    QMatrix4x4* mVmatrix{nullptr};

    QTimer* mRenderTimer{nullptr}; //timer that drives the gameloop
    QElapsedTimer mTimeStart;      //time variable that reads the calculated FPS

    MainWindow* mMainWindow{nullptr}; //points back to MainWindow to be able to put info in StatusBar

    class QOpenGLDebugLogger* mOpenGLDebugLogger{nullptr}; //helper class to get some clean debug info from OpenGL
    class Logger* mLogger{nullptr};                        //logger - Output Log in the application

    ///Helper function that uses QOpenGLDebugLogger or plain glGetError()
    void checkForGLerrors();

    void calculateFramerate(); //as name says

    ///Starts QOpenGLDebugLogger if possible
    void startOpenGLDebugger();

protected:
    //The QWindow that we inherit from have these functions to capture
    // - mouse and keyboard.
    // Uncomment to use (you also have to make the definitions of
    // these functions in the cpp-file to use them of course!)
    //
    //    void mousePressEvent(QMouseEvent *event) override{}
    //    void mouseMoveEvent(QMouseEvent *event) override{}
    void keyPressEvent(QKeyEvent* event) override; //the only one we use now
    void keyReleaseEvent(QKeyEvent* event) override;
    //    void wheelEvent(QWheelEvent *event) override{}

    void MoveByInput(VisualObject*);
    void RotateByInput(VisualObject*);
    void InitMoveKeys();
};

#endif // RENDERWINDOW_H
