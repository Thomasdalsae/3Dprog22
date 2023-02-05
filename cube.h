#ifndef CUBE_H
#define CUBE_H
#include "interactiveobject.h"

class Cube : public InteractiveObject
{
public:
    Cube();
    ~Cube() override;
   void init(GLint matrixuniform) override;
   void draw() override;
private:

};

#endif // CUBE_H
