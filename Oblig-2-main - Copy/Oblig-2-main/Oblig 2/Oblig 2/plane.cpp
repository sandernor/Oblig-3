#include "plane.h"
#include "vertex2.h"

PLANE::PLANE()
{
    //bottom yellow
   mVertices.push_back(Vertex{-3,-0.1,-3 ,0,0.2,1});
   mVertices.push_back(Vertex{3,-0.1,-3,0,0.2,1});
   mVertices.push_back(Vertex{-3,-0.1,3,0,0.2,1});
   mVertices.push_back(Vertex{3,-0.1,3,0,0.2,1});
   mVertices.push_back(Vertex{3,-0.1,-3,0,0.2,1});
   mVertices.push_back(Vertex{-3,-0.1,3,0,0.2,1});
}

PLANE::~PLANE()
{

}

void PLANE::init(GLint matrixUniform)
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
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(0));
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : colors
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof( Vertex ),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
    glEnableVertexAttribArray(1);

    //enable the matrixUniform
    // mMatrixUniform = glGetUniformLocation( matrixUniform, "matrix" );

    glBindVertexArray(0);
}

void PLANE::draw()
{
    glBindVertexArray( mVAO );
    glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
    glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void PLANE::rotate()
{

}

void PLANE::move(float x, float y, float z)
{

}

