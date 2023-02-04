#include "cube.h"

Cube::Cube() : mx{0.0f}, my{0.0f}, mz{0.0f}, RotationAngle{0.0f}, RotationX{0.0f}, RotationY{0.0f}, FloatZ {0.0f}


{
 /*
  Vertex v0{0.0,0.0,0.0, 1,0,0};    mVertices.push_back(v0);
  Vertex v1(0.5,0.0,0.0, 0,1,0);    mVertices.push_back(v1);
  Vertex v2{0.5,0.5,0.0, 0,0,1};    mVertices.push_back(v2);
  Vertex v3{0.0,0.0,0.0, 0,0,1};    mVertices.push_back(v3);
  Vertex v4{0.5,0.5,0.0, 0,1,0};    mVertices.push_back(v4);
  Vertex v5{0.0,0.5,0.0, 1,0,0};    mVertices.push_back(v5);
*/

     /*
    mVertices.push_back(Vertex{0.0,0.0,0.0,1,0,0});
    mVertices.push_back(Vertex{0.5,0.0,0.0,0,1,0});
    mVertices.push_back(Vertex{0.5,0.5,0.0,0,0,1});
    mVertices.push_back(Vertex{0.0,0.0,0.0,0,0,1});
    mVertices.push_back(Vertex{0.5,0.5,0.0,0,1,0});
    mVertices.push_back(Vertex{0.0,0.5,0.0,1,0,0});
    */
    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,1,0,0});
    mVertices.push_back(Vertex{-1.0,-1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,-1.0,0,0,1});
    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,1.0,-1.0,1,0,0});


    mVertices.push_back(Vertex{1.0,-1.0,1.0,1,0,0});
    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{1.0,-1.0,-1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,-1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,-1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,1,0,0});

    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,1,0,0});
    mVertices.push_back(Vertex{-1.0,1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,1.0,-1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,-1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{-1.0,-1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,-1.0,-1.0,1,0,0});

    mVertices.push_back(Vertex{-1.0,1.0,1.0,1,0,0});
    mVertices.push_back(Vertex{-1.0,-1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{1.0,-1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,-1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{1.0,1.0,-1.0,1,0,0});

    mVertices.push_back(Vertex{1.0,-1.0,-1.0,1,0,0});
    mVertices.push_back(Vertex{1.0,1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{1.0,-1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,1.0,-1.0,1,0,0});

    mVertices.push_back(Vertex{1.0,1.0,1.0,1,0,0});
    mVertices.push_back(Vertex{-1.0,1.0,-1.0,0,1,0});
    mVertices.push_back(Vertex{-1.0,1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{1.0,1.0,1.0,0,0,1});
    mVertices.push_back(Vertex{-1.0,1.0,1.0,0,1,0});
    mVertices.push_back(Vertex{1.0,-1.0,1.0,1,0,0});


}

Cube::~Cube(){}

void Cube::init(GLint matrixUniform){

      mMatrixUniform = matrixUniform;

   initializeOpenGLFunctions();

   //Vertex Array Object - VAO
   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );

   //Vertex Buffer Object to hold vertices - VBO
   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );

   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex ), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);

   //enable the matrixUniform
   // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

   glBindVertexArray(0);

}

void Cube::draw(){

   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());


}

void Cube::move(float dx, float dy , float dz){

    mx += dx;
    my += dy;
    mz += dz;



    mMatrix.translate(mx,my,mz); // need to tell it to move

    mx = 0;
    my = 0;
    mz = 0;
}

void Cube::Rotate(float dl, float dr, float du, float dd)
{
  RotationAngle += dl;
  RotationX += dr;
  RotationY += du;
  FloatZ += dd;


  mMatrix.rotate(RotationAngle,RotationX,RotationY,FloatZ);

  RotationAngle = 0;
  RotationX = 0;
  RotationY = 0;
  FloatZ = 0;
}

