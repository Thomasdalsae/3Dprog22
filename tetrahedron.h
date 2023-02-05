#pragma once
#include "interactiveobject.h"
class Tetrahedron : public InteractiveObject
{
public:
	Tetrahedron();
    ~Tetrahedron() override;

    void init(GLint matrixUniform) override;
    void draw() override;
};

