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
#include <fstream>
#include <iostream>
#include <QDir>


#include "XYZ_H.h"
#include "cube.h"
#include "shader.h"
#include "mainwindow.h"
#include "logger.h"
#include "camera.h"
#include "trianglesurface.h"



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
        mMVPmatrix = new QMatrix4x4{};
        mMVPmatrix->setToIdentity();    //1, 1, 1, 1 in the diagonal of the matrix

        mPmatrix = new QMatrix4x4{};
        mPmatrix->setToIdentity();

        mVmatrix = new QMatrix4x4{};
        mVmatrix->setToIdentity();
   //Make the gameloop timer;
    mRenderTimer = new QTimer(this);


    InitMoveKeys();

   //mObjects.push_back(new XYZ());
   //mObjects.push_back(new Curve());
   mObjects.push_back(new Cube());
   mObjects.push_back(new TriangleSurface{"../3Dprog22/vertices.dat"});
   auto trSurf = reinterpret_cast<TriangleSurface*>(mObjects[1]);
   trSurf->drawUnitNormals(true);

   mObjects.push_back(new XYZ());
   //mObjects.push_back(new Curve());
   //mObjects.push_back(new Cube());
   // mObjects.push_back(new TriangleSurface);

  //mObjects.push_back(new Curve("/GItRepos/3Dprog22/Curve.txt"));
    //mObjects.push_back(new TriangleSurface()); // make a new text file
    //TriangleSurface("F:/GItRepos/3Dprog22/Triangle.txt");
    //Directly read TXT file without contruct,,
   //mObjects.push_back(new TriangleSurface("F:/GItRepos/3Dprog22/Trianglee.txt"));
    //mia = new InteractiveObject();
   mia = mObjects[0];

  //mia = new OctahedronBall(2);
   //mObjects.push_back(mia);
}

RenderWindow::~RenderWindow()
{
    mObjects.clear();

    //cleans up the GPU memory
    glDeleteVertexArrays( 1, &mVAO );
    glDeleteBuffers( 1, &mVBO );
}

//Fjerna simple global for verices of a trainge <.<.<.<.<



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
    mShaderProgram = new Shader("../3Dprog22/plainshader.vert", "../3Dprog22/plainshader.frag");


    // Get the matrixUniform location from the shader
    // This has to match the "matrix" variable name in the vertex shader
    // The uniform is used in the render() function to send the model matrix to the shader


    mPmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "pmatrix" );
    mVmatrixUniform = glGetUniformLocation(mShaderProgram->getProgram(),"vmatrix");
    mMmatrixUniform = glGetUniformLocation( mShaderProgram->getProgram(), "matrix" );
        mCamera.init(mPmatrixUniform,mVmatrixUniform);
        /*
    for (auto it=mObjects.begin();it!= mObjects.end(); it++)
        (*it)->init(mPmatrixUniform);
    for (auto it=mObjects.begin();it!= mObjects.end(); it++)
        (*it)->init(mVmatrixUniform);
    */
    for (auto it=mObjects.begin();it!= mObjects.end(); it++)
        (*it)->init(mMmatrixUniform);
    glBindVertexArray(0);       //unbinds any VertexArray - good practice


}

// Called each frame - doing the rendering!!!
void RenderWindow::render()
{

    //Additioal matrixes here
    //mPmatrix->setToIdentity();
    //mVmatrix->setToIdentity();
   // mPmatrix->perspective(60,4.0/3.0,0.1,10.0);

    mCamera.init(mPmatrixUniform, mVmatrixUniform);
    mCamera.perspective(60,4.0/3.0,0.1,20.0);

    mTimeStart.restart(); //restart FPS clock
    mContext->makeCurrent(this); //must be called every frame (every time mContext->swapBuffers is called)

    initializeOpenGLFunctions();    //must call this every frame it seems...

       //clear the screen for each redraw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //what shader to use
    glUseProgram(mShaderProgram->getProgram() );

    //Moveing camera
    mCamera.translate(0,0,15);
    mCamera.lookAt(QVector3D{0,0,15},QVector3D{0,0,0}, QVector3D{0,1,0});
    mCamera.update();

    MoveByInput(mia);
    RotateByInput(mia);


//the actual draw call

    for (auto it=mObjects.begin();it!= mObjects.end(); it++)
        (*it)->draw();
    //ree
/*
 if (XYZ_render == true){
    XYZ().draw();
 }
*/
    mMVPmatrix->setToIdentity();

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
//    if(mRotate){
//        //mMVPmatrix->rotate(2.f, 0.f, 1.0, 0.f);
//        //mPmatrix->rotate(2.f, 0.f, 1.0, 0.f);
//        mVmatrix->rotate(2.f, 0.f, 1.0, 0.f);

//    }

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

//Event sent from Qt when program receives a keyPress
// NB - see renderwindow.h for signatures on keyRelease and mouse input
void RenderWindow::keyPressEvent(QKeyEvent *event)
{
    pressedKeys[event->key()] = true;


    if (event->key() == Qt::Key_Escape)
    {
        mMainWindow->close();       //Shuts down the whole program
    }
}

void RenderWindow::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys[event->key()] = false;
}

void RenderWindow::MoveByInput(VisualObject *obj)
{
    QVector3D movVec{};

    QVector3D right{-1,0,0};
    QVector3D up{0,-1,0};
    QVector3D out{0,0,-1};

    for (auto key : pressedKeys) {
        if (key.second) continue;

        switch (key.first) {
        case Qt::Key_Right:
            movVec += right;
            break;

        case Qt::Key_Left:
            movVec -= right;
            break;

        case Qt::Key_Up:
            movVec += up;
            break;

        case Qt::Key_Down:
            movVec -= up;
            break;

        case Qt::Key_Space:
            movVec += out;
            break;

        case Qt::Key_Shift:
            movVec -= out;
            break;

        default:
            break;
        }
    }

    movVec.normalize();
    movVec /= mRenderTimer->interval();
    obj->move(movVec.x(), movVec.y(), movVec.z());
}

void RenderWindow::RotateByInput(VisualObject* obj)
{
    QVector3D rotVec{};
    bool bRotating{false};

    QVector3D xrot{1,0,0};
    QVector3D yrot{0,1,0};
    QVector3D zrot{0,0,1};

    for (auto key : pressedKeys) {
        if (!key.second) continue;

        bRotating = true;

        switch (key.first) {
        case Qt::Key_S:
            rotVec += xrot;
            break;

        case Qt::Key_W:
            rotVec -= xrot;
            break;

        case Qt::Key_D:
            rotVec += yrot;
            break;

        case Qt::Key_A:
            rotVec -= yrot;
            break;

        case Qt::Key_Q:
            rotVec -= zrot;
            break;

        case Qt::Key_E:
            rotVec += zrot;
            break;

        default:
            break;
        }
    }

    rotVec.normalize();
    if(bRotating) obj->Rotate(1.0f, rotVec.x(), rotVec.y(), rotVec.z());
}

void RenderWindow::InitMoveKeys()
{
    // cache key states for move keys:
    pressedKeys[Qt::Key_Right] = false;
    pressedKeys[Qt::Key_Left] = false;
    pressedKeys[Qt::Key_Up] = false;
    pressedKeys[Qt::Key_Down] = false;
    pressedKeys[Qt::Key_Space] = false;
    pressedKeys[Qt::Key_Shift] = false;

    // cache key states for rot keys:
    pressedKeys[Qt::Key_Q] = false;
    pressedKeys[Qt::Key_E] = false;
    pressedKeys[Qt::Key_S] = false;
    pressedKeys[Qt::Key_W] = false;
    pressedKeys[Qt::Key_D] = false;
    pressedKeys[Qt::Key_A] = false;
}
