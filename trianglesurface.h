#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H

#include "visualobject.h"
#include "QVector3D"

class TriangleSurface : public VisualObject
{
public:
   TriangleSurface();
   TriangleSurface(std::string filnavn);
   ~TriangleSurface() override;
   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
   void construct();
};
#endif
