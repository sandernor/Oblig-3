//#include "cube.h"
//#include "vertex.h"

//CUBE::CUBE()
//{
//    //bottom yellow
//   mVertices.push_back(Vertex0{0,0,0,1,1,0});
//   mVertices.push_back(Vertex0{0.5,0,0,1,1,0});
//   mVertices.push_back(Vertex0{0,0,0.5,1,1,0});
//   mVertices.push_back(Vertex0{0.5,0,0.5,1,1,0});
//   mVertices.push_back(Vertex0{0.5,0,0,1,1,0});
//   mVertices.push_back(Vertex0{0,0,0.5,1,1,0});

//   //top white
//   mVertices.push_back(Vertex0{0,0.5,0,1,1,1});
//   mVertices.push_back(Vertex0{0.5,0.5,0,1,1,1});
//   mVertices.push_back(Vertex0{0,0.5,0.5,1,1,1});
//   mVertices.push_back(Vertex0{0.5,0.5,0.5,1,1,1});
//   mVertices.push_back(Vertex0{0.5,0.5,0,1,1,1});
//   mVertices.push_back(Vertex0{0,0.5,0.5,1,1,1});

//   //side 1 green
//   mVertices.push_back(Vertex0{0,0,0,0,1,0});
//   mVertices.push_back(Vertex0{0,0.5,0,0,1,0});
//   mVertices.push_back(Vertex0{0.5,0,0,0,1,0});
//   mVertices.push_back(Vertex0{0.5,0,0,0,1,0});
//   mVertices.push_back(Vertex0{0.5,0.5,0,0,1,0});
//   mVertices.push_back(Vertex0{0,0.5,0,0,1,0});

//   //side 3 blue
//   mVertices.push_back(Vertex0{0,0,0.5,0,0,1});
//   mVertices.push_back(Vertex0{0,0.5,0.5,0,0,1});
//   mVertices.push_back(Vertex0{0.5,0,0.5,0,0,1});
//   mVertices.push_back(Vertex0{0.5,0.5,0.5,0,0,1});
//   mVertices.push_back(Vertex0{0.5,0,0.5,0,0,1});
//   mVertices.push_back(Vertex0{0,0.5,0.5,0,0,1});

//   //side 2 red
//   mVertices.push_back(Vertex0{0.5,0,0,1,0,0});
//   mVertices.push_back(Vertex0{0.5,0.5,0,1,0,0});
//   mVertices.push_back(Vertex0{0.5,0.5,0.5,1,0,0});
//   mVertices.push_back(Vertex0{0.5,0,0,1,0,0});
//   mVertices.push_back(Vertex0{0.5,0,0.5,1,0,0});
//   mVertices.push_back(Vertex0{0.5,0.5,0.5,1,0,0});

//   //side 4 orange
//   mVertices.push_back(Vertex0{0,0,0,1,0.5,0});
//   mVertices.push_back(Vertex0{0,0,0.5,1,0.5,0});
//   mVertices.push_back(Vertex0{0,0.5,0.5,1,0.5,0});
//   mVertices.push_back(Vertex0{0,0,0,1,0.5,0});
//   mVertices.push_back(Vertex0{0,0.5,0,1,0.5,0});
//   mVertices.push_back(Vertex0{0,0.5,0.5,1,0.5,0});
//}

//void CUBE::init(GLuint mVAO, GLuint mVBO)
//{
//   initializeOpenGLFunctions();

//   //Vertex Buffer Object to hold vertices - VBO
//   glBufferData( GL_ARRAY_BUFFER, mVertices.size()*sizeof( Vertex0 ), mVertices.data(), GL_STATIC_DRAW );

//   // 1rst attribute buffer : vertices
//   glBindBuffer(GL_ARRAY_BUFFER, mVBO);
//   glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,6 * sizeof(GLfloat), (GLvoid*)0);
//   glEnableVertexAttribArray(0);

//   // 2nd attribute buffer : colors
//   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  6 * sizeof( GLfloat ),  (GLvoid*)(3 * sizeof(GLfloat)) );
//   glEnableVertexAttribArray(1);
//}

//void CUBE::draw()
//{
//   //actual draw call
//   //setContext(context);
//   glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
//}

