#ifndef CUBE_H
#define CUBE_H
#include "visualobject.h"

class Cube : public VisualObject {
public:
    Cube();
    ~Cube() override;
    void init(GLint matrixuniform) override;
    void draw() override;

private:
};

#endif // CUBE_H
