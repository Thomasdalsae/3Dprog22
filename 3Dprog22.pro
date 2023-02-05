QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    XYZ.cpp \
    camera.cpp \
    cube.cpp \
    curve.cpp \
    linesegment.cpp \
    logger.cpp \
    mainwindow.cpp \
    octahedronball.cpp \
    renderwindow.cpp \
    shader.cpp \
    tetrahedron.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp

HEADERS += \
    XYZ_H.h \
    camera.h \
    cube.h \
    curve.h \
    linesegment.h \
    logger.h \
    mainwindow.h \
    octahedronball.h \
    renderwindow.h \
    shader.h \
    tetrahedron.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    Curve.txt \
    Triangle.txt \
    TriangleTest \
    plainshader.frag \
    plainshader.vert
