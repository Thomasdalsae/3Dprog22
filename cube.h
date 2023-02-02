#ifndef CUBE_H
#define CUBE_H
#include "visualobject.h"

class Cube : public VisualObject
{
public:
    Cube();
    ~Cube() override;
   void init(GLint matrixuniform) override;
   void draw() override;
   void move(float x, float y, float z);
   void Rotate(float l,float r, float u, float d );
private:
   float mx, my ,mz ,RotationAngle , RotationX ,RotationY ,FloatZ;
};

#endif // CUBE_H
