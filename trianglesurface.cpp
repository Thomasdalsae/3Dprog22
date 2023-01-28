#include "trianglesurface.h"

TriangleSurface::TriangleSurface() : VisualObject()
{
  //                x    y     z   r g b
 /*
  Vertex v0{0.0,0.0,0.0, 1,0,0};    mVertices.push_back(v0);
  Vertex v1(0.5,0.0,0.0, 0,1,0);    mVertices.push_back(v1);
  Vertex v2{0.5,0.5,0.0, 0,0,1};    mVertices.push_back(v2);
  Vertex v3{0.0,0.0,0.0, 0,0,1};    mVertices.push_back(v3);
  Vertex v4{0.5,0.5,0.0, 0,1,0};    mVertices.push_back(v4);
  Vertex v5{0.0,0.5,0.0, 1,0,0};    mVertices.push_back(v5);
*/

  mMatrix.setToIdentity();
  //readFile("C:/Users/thoma/Desktop/3Dprog22-main/3Dprog22/Triangle.txt");

    //Have write to file under construct function
  // make changes on construct algo then run it to make new txt file.
   // construct();

  //readFile("/GItRepos/3Dprog22/Triangle.txt");
}

TriangleSurface::~TriangleSurface(){}

void TriangleSurface::init(GLint matrixUniform){
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

TriangleSurface::TriangleSurface(std::string filnavn) : VisualObject()
{
   readFile(filnavn);
   mMatrix.setToIdentity();
}




//   }
//}
void TriangleSurface::readFile(std::string fileName) {
        std::ifstream inn;
        inn.open(fileName.c_str());
        mVertices.clear();
        if (inn.is_open()) {
            int n;
            Vertex vertex;
            inn >> n;
            mVertices.reserve(n);
            for (int i = 0; i < n; ++i) {
                inn >> vertex;
                mVertices.push_back(vertex);
                std::cout << vertex << std::endl;
            }
        }
    }

    void TriangleSurface::toFile(std::string fileName) {
        std::fstream o;
        o.open(fileName.c_str(), std::ios::out);
        o << mVertices.size() << std::endl;
        for (int i = 0; i < mVertices.size(); ++i) {
            o << mVertices[i] << std::endl;
        }
        o.close();
    }

void TriangleSurface::draw(){
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}


void TriangleSurface::construct()
{
  float xmin=-1.0f, xmax=0.0f, ymin=-1.0f, ymax=0.0f, h=0.05f;
  for (auto x=xmin; x<xmax; x+=h)
      for (auto y=ymin; y<ymax; y+=h)
      {
          float z = cos(M_PI*x)*sin(M_PI*y);
          mVertices.push_back(Vertex{x,y,z,x,y,z});
          z = cos((M_PI*x+h))*sin(M_PI*y);
          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
          z = cos(M_PI*x)*sin(M_PI*(y+h));
          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
          z = cos(M_PI*(x+h))*sin(M_PI*y);
          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
          z = cos(M_PI*(x+h))*sin(M_PI*(y+h));
          mVertices.push_back(Vertex{x+h,y+h,z,x,y,z});
      }

 toFile("/GItRepos/3Dprog22/Triangle.txt");

}
