#include "visualcurve.h"


VisualCurve::VisualCurve()
{
   //mVertices.push_back(Vertex{0,0,0,0,0,1});
   //mVertices.push_back(Vertex{1,1,1,0,0,1});
   mMatrix.setToIdentity();
}


VisualCurve::~VisualCurve()
{


}


void VisualCurve::init(GLint matrixUniform)
{
   mMatrixUniform = matrixUniform;
   initializeOpenGLFunctions();


   glGenVertexArrays( 1, &mVAO );
   glBindVertexArray( mVAO );


   glGenBuffers( 1, &mVBO );
   glBindBuffer( GL_ARRAY_BUFFER, mVBO );


   glBufferData( GL_ARRAY_BUFFER,      //what buffer type
                 mVertices.size()*sizeof( Vertex ),   //how big buffer do we need
                 mVertices.data(),             //the actual vertices
                 GL_STATIC_DRAW        //should the buffer be updated on the GPU
                 );


   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(
               0,                  // attribute. No particular reason for 0, but must match layout(location = 0) in the vertex shader.
               3,                  // size
               GL_FLOAT,           // data type
               GL_FALSE,           // normalized?
               sizeof(Vertex),  // stride
               reinterpret_cast<GLvoid*>(0  ));          // array buffer offset
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(Vertex),  reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);
   glBindVertexArray(0);
}


void VisualCurve::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINE_STRIP, 0, mVertices.size());
}
