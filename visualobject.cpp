// VisualObject.cpp
#include "visualobject.h"

VisualObject::VisualObject() {
}

VisualObject::~VisualObject() {
    glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(1, &mVBO);
}

void VisualObject::move(float dx, float dy, float dz) {
    mMatrix.translate(dx, dy, dz); // need to tell it to move
    mPosition = mMatrix * QVector4D{0, 0, 0, 1};
}

void VisualObject::Rotate(float dl, float dr, float du, float dd) {
    mMatrix.rotate(dl, dr, du, dd);
}
