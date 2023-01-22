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
    GLfloat x;
    GLfloat y;

};

#endif // POINTS_H


void Graph(){


Points graph[2000];
for(int i = 0; i < 2000; i++){
    float x = (i - 1000.0) /100.0;
    graph[i].x = x;
    graph[i].y = sin(x * 10.0) / (1.0 + x*x);
    }
}
