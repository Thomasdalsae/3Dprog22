#include "linesegment.h"
#include <initializer_list>

LineSegment::LineSegment()
{

}

LineSegment::~LineSegment()
{

}

LineSegment::LineSegment(std::initializer_list<float> vals)
{
    auto it = vals.begin();

    if(vals.size() > 6) throw std::range_error("Too many values for line");
    mVertices.clear();
    mVertices.push_back(Vertex{*it, *(++it), *(++it), 1, 0, 0});
    mVertices.push_back(Vertex{*(++it), *(++it), *(++it), 0, 1, 0});

//    qDebug() << "(" << mVertices[0][0] << "," << mVertices[0][1] << "," << mVertices[0][2] << ")" << "\n";
//    qDebug() << "(" << mVertices[1][0] << "," << mVertices[1][0] << "," << mVertices[1][2] << ")" << "\n";
//    qDebug() << "(" << mVertices[1][0]-mVertices[0][0] << "," << mVertices[1][1]-mVertices[0][1] << "," << mVertices[1][2]-mVertices[0][2] << ")" << "\n";
}

void LineSegment::init(GLint shader)
{
    mMatrixUniform = shader;

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

void LineSegment::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());

    glDrawArrays(GL_LINES, 0, mVertices.size());
}
