#ifndef XYZ_H
#define XYZ_H
#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex.h"
class XYZ : protected QOpenGLFunctions_4_1_Core
{
private:
std::vector<Vertex0> mVertices;
//QOpenGLContext *mContext;
public:
XYZ();
//void setContext(QOpenGLContext *context);
void init(GLuint mVAO, GLuint mVBO);
void draw();
};
#endif // XYZ_H
