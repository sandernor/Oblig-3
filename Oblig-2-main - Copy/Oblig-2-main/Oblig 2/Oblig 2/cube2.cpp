#include "cube2.h"

CUBE::CUBE()
{
    //bottom yellow
   mVertices.push_back(Vertex{0,0,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0,0,0.5,1,1,1});

   //top white
   mVertices.push_back(Vertex{0,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});

   //side 1 green
   mVertices.push_back(Vertex{0,0,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0,1,1,1});

   //side 3 blue
   mVertices.push_back(Vertex{0,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});

   //side 2 red
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0,1,1,1});
   mVertices.push_back(Vertex{0.5,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0.5,0.5,0.5,1,1,1});

   //side 4 orange
   mVertices.push_back(Vertex{0,0,0,1,1,1});
   mVertices.push_back(Vertex{0,0,0.5,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});
   mVertices.push_back(Vertex{0,0,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0,1,1,1});
   mVertices.push_back(Vertex{0,0.5,0.5,1,1,1});
   mMatrix.setToIdentity();
}

CUBE::~CUBE()
{

}

void CUBE::init(GLint matrixUniform)
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

void CUBE::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
}

void CUBE::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
}

void CUBE::rotate()
{
    mMatrix.rotate(1.f, 2.f, 1.0, 0.f);
}
