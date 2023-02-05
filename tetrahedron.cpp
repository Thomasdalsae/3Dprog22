#include "tetrahedron.h"
#include <cmath>

Tetrahedron::Tetrahedron()
{
    mVertices.clear();
	// ABD
    mVertices.push_back(Vertex{sqrtf(8/9.0f), 0, -1/3.0f, 25/255.0f, 155/255.0f, 76/255.0f});
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), sqrtf(2/3.0f), -1/3.0f, 137/255.0f, 18/255.0f, 20/255.0f});
	mVertices.push_back(Vertex{0, 0, -1, 13/255.0f, 72/255.0f, 172/255.0f});

	// BCD
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), sqrtf(2/3.0f), -1/3.0f, 25/255.0f, 155/255.0f, 76/255.0f});
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), -sqrtf(2/3.0f), -1/3.0f, 137/255.0f, 18/255.0f, 20/255.0f});
	mVertices.push_back(Vertex{0, 0, -1, 13/255.0f, 72/255.0f, 172/255.0f});

	// CAD
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), -sqrtf(2/3.0f), -1/3.0f, 25/255.0f, 155/255.0f, 76/255.0f});
    mVertices.push_back(Vertex{sqrtf(8/9.0f), 0, -1/3.0f, 137/255.0f, 18/255.0f, 20/255.0f});
	mVertices.push_back(Vertex{0, 0, -1, 13/255.0f, 72/255.0f, 172/255.0f});

	// ACB
    mVertices.push_back(Vertex{sqrtf(8/9.0f), 0, -1/3.0f, 25/255.0f, 155/255.0f, 76/255.0f});
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), -sqrtf(2/3.0f), -1/3.0f, 137/255.0f, 18/255.0f, 20/255.0f});
    mVertices.push_back(Vertex{-sqrtf(2/9.0f), sqrtf(2/3.0f), -1/3.0f, 13/255.0f, 72/255.0f, 172/255.0f});

    mMatrix.setToIdentity();
}

Tetrahedron::~Tetrahedron() {}

void Tetrahedron::init(GLint matrixUniform)
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
}

void Tetrahedron::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}
