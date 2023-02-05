#pragma once
#include "visualobject.h"

class Tetrahedron : public VisualObject
{
public:
	Tetrahedron();
    ~Tetrahedron() override;

    void init(GLint matrixUniform) override;
    void draw() override;
};

