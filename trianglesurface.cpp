#include "trianglesurface.h"
#include <fstream>
#include <QTextStream>
#include <QDir>

TriangleSurface::TriangleSurface()
{
    //                x    y     z   r g b
    Vertex v0{0.0,0.0,0.0, 1,0,0};    mVertices.push_back(v0);
    Vertex v1{0.5,0.0,0.0, 0,1,0};    mVertices.push_back(v1);
    Vertex v2{0.5,0.5,0.0, 0,0,1};    mVertices.push_back(v2);
    Vertex v3{0.0,0.0,0.0, 0,0,1};    mVertices.push_back(v3);
    Vertex v4{0.5,0.5,0.0, 0,1,0};    mVertices.push_back(v4);
    Vertex v5{0.0,0.5,0.0, 1,0,0};    mVertices.push_back(v5);
    mMatrix.setToIdentity();
}

TriangleSurface::~TriangleSurface() {
    mNormals.clear();
}

TriangleSurface::TriangleSurface(std::string filnavn)
{
   mVertices.clear();
   readFile(filnavn);
   mMatrix.setToIdentity();
}

void TriangleSurface::readFile(std::string filnavn) {
   std::fstream inn;
   inn.open(filnavn, std::fstream::in);

   if (inn.is_open()) {
       qDebug() << "file open\n";
       int n;
       Vertex vertex;
       inn >> n;
       mVertices.reserve(n);
       for (int i=0; i<n; i++) {
           inn >> vertex;
           mVertices.push_back(vertex);
//           qDebug() << mVertices[i][0] << ", " << mVertices[i][1] << ", " << mVertices[i][2] << ", " << mVertices[i][3] << ", " << mVertices[i][4] << ", " << mVertices[i][5];
       }
       inn.close();

       // create vector of normals to draw.
       for (size_t i = 0; i < mVertices.size(); i+=2) {
           mNormals.push_back(new LineSegment{mVertices[i][0], mVertices[i][1], mVertices[i][2],
                                          mVertices[i][0]+mVertices[i][3], mVertices[i][1]+mVertices[i][4], mVertices[i][2]+mVertices[i][5]});
       }
   } else {
       qDebug() << "file not open\n";
   }
}

void TriangleSurface::init(GLint matrixUniform)
{
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

    for (auto normal : mNormals) {
        normal->init(matrixUniform);
    }
}

void TriangleSurface::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());

    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

    if (!bDrawUnitNormals) return;

    for (auto normal : mNormals) {
        normal->draw();
    }
}

void TriangleSurface::move(float dx, float dy, float dz)
{
    InteractiveObject::move(dx, dy, dz);
    for (auto normal : mNormals) {
        normal->move(dx, dy, dz);
    }
}

void TriangleSurface::Rotate(float deg, float x, float y, float z)
{
    InteractiveObject::Rotate(deg, x, y, z);

    for (auto normal : mNormals) {
        normal->Rotate(deg, x, y, z);
    }
}



