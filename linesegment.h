#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "interactiveobject.h"


class LineSegment : public InteractiveObject
{
public:
    LineSegment();
    ~LineSegment() override;
    LineSegment(class std::initializer_list<float> vals);

    virtual void init(GLint shader) override;
    virtual void draw() override;

};

#endif // LINESEGMENT_H
