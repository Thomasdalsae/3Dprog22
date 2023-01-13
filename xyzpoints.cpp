
#include "xyzpoints.h"
#include "vertex.h"


XYZPoints::XYZPoints()
{
    mVertices.push_back(Vertex0{0,0,0,1,0,0});
    mVertices.push_back(Vertex0{1,0,0,1,0,0});
    mVertices.push_back(Vertex0{0,0,0,0,1,0});
}
