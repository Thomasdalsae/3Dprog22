QT          += core gui widgets opengl

TEMPLATE    = app
CONFIG      += c++17

TARGET      = 3D-programmering

SOURCES += main.cpp \
    XYZ.cpp \
    curve.cpp \
    logger.cpp \
    mainwindow.cpp \
    renderwindow.cpp \
    shader.cpp \
    trianglesurface.cpp \
    vertex.cpp \
    visualobject.cpp

HEADERS += \
    XYZ_H.h \
    curve.h \
    logger.h \
    mainwindow.h \
    renderwindow.h \
    shader.h \
    trianglesurface.h \
    vertex.h \
    visualobject.h

FORMS += \
    mainwindow.ui

DISTFILES += \
    Triangle.txt \
    TriangleTest \
    plainshader.frag \
    plainshader.vert
