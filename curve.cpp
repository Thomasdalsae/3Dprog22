#include "curve.h"

Curve::Curve() : VisualObject()
{

  mMatrix.setToIdentity();
  //readFile("C:/Users/thoma/Desktop/3Dprog22-main/3Dprog22/Triangle.txt");

    //Have write to file under construct function
  // make changes on construct algo then run it to make new txt file.
    construct();

  readFile("C:/Users/thoma/Desktop/3Dprog22-main/3Dprog22/Curve.txt");
}

Curve::~Curve(){};

void Curve::init(GLint matrixUniform){
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

Curve::Curve(std::string filnavn) : VisualObject()
{
   readFile(filnavn);
   mMatrix.setToIdentity();
}


//   }
//}
void Curve::readFile(std::string fileName) {
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

    void Curve::toFile(std::string fileName) {
        std::fstream o;
        o.open(fileName.c_str(), std::ios::out);
        o << mVertices.size() << std::endl;
        for (int i = 0; i < mVertices.size(); ++i) {
            o << mVertices[i] << std::endl;
        }
        o.close();
    }

void Curve::draw(){
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINE, 0, mVertices.size());
}


void Curve::construct()
{
    // range is -10 < x < 10;
    GLfloat x = sin(10 * x) / (1+x);
    GLfloat y = sin(10*x)/1+x*x;






}



 toFile("C:/Users/thoma/Desktop/3Dprog22-main/3Dprog22/Curve.txt");
}




