#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H
#include "visualobject.h"
#include <QMatrix4x4>
#include <vector>
#include <fstream>
#include <iostream>
#include <vertex.h>
#include <QFile>
#include <QTextStream>
#include "visualobject.h"
#include "QVector3D"


class InteractiveObject : public VisualObject
{
public:
    InteractiveObject();
    ~InteractiveObject() override;
    void init(GLint matrixUniform) override;
    void draw()override;
    void move(float x,float y,float z){}

private:
    float mx, my ,mz ; // position
};

#endif // INTERACTIVEOBJECT_H
