#ifndef POINTS_H
#define POINTS_H
#include "visualobject.h"

class Points : public VisualObject
{
public:

    Points();
   Points(std::string filnavn);
   ~Points() override;
   void readFile(std::string filnavn);
   void toFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
   void construct();
   void algoGraph();
    GLfloat x;
    GLfloat y;


};

#endif // POINTS_H
 Points graph[2000];
