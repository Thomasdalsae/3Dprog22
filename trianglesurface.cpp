#include "trianglesurface.h"

TriangleSurface::TriangleSurface() : VisualObject()
{
  //                x    y     z   r g b
  Vertex v0{0.0,0.0,0.0, 1,0,0};    mVertices.push_back(v0);
  Vertex v1(0.5,0.0,0.0, 0,1,0);    mVertices.push_back(v1);
  Vertex v2{0.5,0.5,0.0, 0,0,1};    mVertices.push_back(v2);
  Vertex v3{0.0,0.0,0.0, 0,0,1};    mVertices.push_back(v3);
  Vertex v4{0.5,0.5,0.0, 0,1,0};    mVertices.push_back(v4);
  Vertex v5{0.0,0.5,0.0, 1,0,0};    mVertices.push_back(v5);

  mMatrix.setToIdentity();


}

TriangleSurface::~TriangleSurface(){}


TriangleSurface::TriangleSurface(std::string filnavn) : VisualObject()
{
   readFile(filnavn);
   mMatrix.setToIdentity();
}

void TriangleSurface::readFile(std::string filnavn) {
   std::ifstream inn;
   inn.open(filnavn.c_str());

   if (inn.is_open()) {
       int n;
       Vertex vertex;
       inn >> n;
       mVertices.reserve(n);
       for (int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
       }
       inn.close();
   }
}


void TriangleSurface::construct()
{
  float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.25f;
  for (auto x=xmin; x<xmax; x+=h)
      for (auto y=ymin; y<ymax; y+=h)
      {
          float z = sin(M_PI*x)*sin(M_PI*y);
          mVertices.push_back(Vertex{x,y,z,x,y,z});
          z = sin(M_PI*(x+h))*sin(M_PI*y);
          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
          z = sin(M_PI*x)*sin(M_PI*(y+h));
          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
          z = sin(M_PI*(x+h))*sin(M_PI*y);
          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
          z = sin(M_PI*(x+h))*sin(M_PI*(y+h));
          mVertices.push_back(Vertex{x+h,y+h,z,x,y,z});
      }
}
