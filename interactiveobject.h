#ifndef INTERACTIVEOBJECT_H
#define INTERACTIVEOBJECT_H

#include "visualobject.h"

class InteractiveObject : public VisualObject
{
public:
    InteractiveObject();
    ~InteractiveObject() override;
    void init(GLint matrixuniform)override;
    void draw() override;
    void move(float x, float y, float z) override;
    void Rotate(float l,float r, float u, float d ) override;

private:
    float mx, my ,mz ,RotationAngle , RotationX ,RotationY ,FloatZ;

};

#endif // INTERACTIVEOBJECT_H
