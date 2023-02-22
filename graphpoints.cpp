#include "graphpoints.h"

GraphPoints::GraphPoints() : VisualObject()
{

    mMatrix.setToIdentity();


    construct();
}

GraphPoints::~GraphPoints(){};

void GraphPoints::init(GLint matrixUniform) {
    mMatrixUniform = matrixUniform;

    initializeOpenGLFunctions();

    //Vertex Array Object - VAO
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    //Vertex Buffer Object to hold vertices - VBO
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

    // 1rst attribute buffer : vertices
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    glBindVertexArray(0);
}

GraphPoints::GraphPoints(std::string filnavn) : VisualObject() {
    readFile(filnavn);
    mMatrix.setToIdentity();
}


//   }
//}
void GraphPoints::readFile(std::string fileName) {
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

void GraphPoints::toFile(std::string fileName) {
    std::fstream o;
    o.open(fileName.c_str(), std::ios::out);
    o << mVertices.size() << std::endl;
    for (int i = 0; i < mVertices.size(); ++i) {
        o << mVertices[i] << std::endl;
    }
    o.close();
}

void GraphPoints::draw() {
    glBindVertexArray(mVAO);
    glUniformMatrix4fv(mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_POINTS, 0, mVertices.size());
}


/*
void GraphPoints::construct() {


    mVertices.push_back(Vertex{1,8,0,1,0,0});
    mVertices.push_back(Vertex{2,3,0,1,0,0});
    mVertices.push_back(Vertex{4,1,0,1,0,0});
    mVertices.push_back(Vertex{4,5,0,1,0,0});
    mVertices.push_back(Vertex{4,5,0,1,0,0});
    mVertices.push_back(Vertex{5,5,0,1,0,0});
    mVertices.push_back(Vertex{7,8,0,1,0,0});
    mVertices.push_back(Vertex{7,3,0,1,0,0});
    mVertices.push_back(Vertex{8,5,0,1,0,0});
    qDebug("Entering GraphPOints");

    toFile("/GItRepos/3Dprog22/PointsOblig2.txt");
}
*/



void GraphPoints::construct() {


    mVertices.push_back(Vertex{1,8,0,1,0,0});
    mVertices.push_back(Vertex{2,3,0,1,0,0});
    mVertices.push_back(Vertex{3,1,0,1,0,0});
    mVertices.push_back(Vertex{4,5,0,1,0,0});

    qDebug("Entering GraphPOints");

    toFile("/GItRepos/3Dprog22/PointsOblig2.txt");
}


// toFile("C:/Users/thoma/Desktop/3Dprog22-main/3Dprog22/Curve.txt");
//}
