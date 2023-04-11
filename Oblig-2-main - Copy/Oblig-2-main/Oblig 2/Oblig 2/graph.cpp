#include "graph.h"
#include "vertex.h"

GRAPH::GRAPH()
{
    //axes
   mVertices.push_back(Vertex0{0,0,0,1,0,0});
   mVertices.push_back(Vertex0{1,0,0,1,0,0});
   mVertices.push_back(Vertex0{0,0,0,0,1,0});
   mVertices.push_back(Vertex0{0,1,0,0,1,0});

   //graph
  mVertices.push_back(Vertex0{0,0,0,0,0,1});
  mVertices.push_back(Vertex0{0.1,0.05,0,0,0,1});

  mVertices.push_back(Vertex0{0.1,0.05,0,0,0,1});
  mVertices.push_back(Vertex0{0.2,0.1,0,0,0,1});

  mVertices.push_back(Vertex0{0.2,0.1,0,0,0,1});
  mVertices.push_back(Vertex0{0.3,0.15,0,0,0,1});

  mVertices.push_back(Vertex0{0.3,0.15,0,0,0,1});
  mVertices.push_back(Vertex0{0.4,0.2,0,0,0,1});

  mVertices.push_back(Vertex0{0.4,0.2,0,0,0,1});
  mVertices.push_back(Vertex0{0.5,0.25,0,0,0,1});

  mVertices.push_back(Vertex0{0.5,0.25,0,0,0,1});
  mVertices.push_back(Vertex0{0.6,0.3,0,0,0,1});

  mVertices.push_back(Vertex0{0.6,0.3,0,0,0,1});
  mVertices.push_back(Vertex0{0.7,0.45,0,0,0,1});

  mVertices.push_back(Vertex0{0.7,0.45,0,0,0,1});
  mVertices.push_back(Vertex0{0.8,0.6,0,0,0,1});

  mVertices.push_back(Vertex0{0.8,0.6,0,0,0,1});
  mVertices.push_back(Vertex0{0.9,0.78,0,0,0,1});

  mVertices.push_back(Vertex0{0.9,0.78,0,0,0,1});
  mVertices.push_back(Vertex0{1,1,0,0,0,1});


}

void GRAPH::init(GLuint mVAO, GLuint mVBO)
{
   initializeOpenGLFunctions();

   //Vertex Buffer Object to hold vertices - VBO
   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex0 ), mVertices.data(), GL_STATIC_DRAW );

   // 1rst attribute buffer : vertices
   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   // 2nd attribute buffer : colors
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  6 * sizeof( GLfloat ),  (GLvoid*)(3 * sizeof(GLfloat)) );
   glEnableVertexAttribArray(1);
}

void GRAPH::draw()
{
   //actual draw call
   //setContext(context);
   glDrawArrays(GL_LINES, 0, mVertices.size());
}
