#include "points.h"


Points::Points() : VisualObject()
{

}

Points::~Points(){}


 void Points::algoGraph(){
   for(int i = 0; i < 2000; i++){
    float x = (i - 1000.0) /100.0;
    graph[i].x = x;
    graph[i].y = sin(x * 10.0) / (1.0 + x*x);
    }

 }


void Points::init(GLint matrixUniform){
    mMatrixUniform = matrixUniform;


       GLint attribute_coord2d;
    GLuint vbo;

    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    //GL_Static_Draw indicates that we will not write to this buffer oftem,
    //and that the GPU should keep a copy of it in its own memory.
    glBufferData(GL_ARRAY_BUFFER, sizeof graph,graph, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(attribute_coord2d);
    glVertexAttribPointer(attribute_coord2d,2,GL_FLOAT,GL_FALSE,0,0);

    glDrawArrays(GL_LINE_STRIP,0,2000);

    glDisableVertexAttribArray(attribute_coord2d);
    glBindBuffer(GL_ARRAY_BUFFER,0);




}
