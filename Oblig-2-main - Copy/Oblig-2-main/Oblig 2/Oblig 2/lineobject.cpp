#include "lineobject.h"

LineObject::LineObject() : VisualObject()
{
  //                x    y     z   r g b
//  Vertex v0{0.0,0.0,0.0, 1,0,0};    mVertices.push_back(v0);
//  Vertex v1(0.5,0.0,0.0, 0,1,0);    mVertices.push_back(v1);
//  Vertex v2{0.5,0.5,0.0, 0,0,1};    mVertices.push_back(v2);
//  Vertex v3{0.0,0.0,0.0, 0,0,1};    mVertices.push_back(v3);
//  Vertex v4{0.5,0.5,0.0, 0,1,0};    mVertices.push_back(v4);
//  Vertex v5{0.0,0.5,0.0, 1,0,0};    mVertices.push_back(v5);


  mMatrix.setToIdentity();
}

LineObject::LineObject(std::string filnavn) : VisualObject()
{
   readFile(filnavn);
   mMatrix.setToIdentity();
}

LineObject::~LineObject()
{

}

//void TriangleSurface::construct()
//{
//  float xmin=0.0f, xmax=1.0f, ymin=0.0f, ymax=1.0f, h=0.25f;
//  for (auto x=xmin; x<xmax; x+=h)
//      for (auto y=ymin; y<ymax; y+=h)
//      {
//          float z = sin(M_PI*x)*sin(M_PI*y);
//          mVertices.push_back(Vertex{x,y,z,x,y,z});
//          z = sin(M_PI*(x+h))*sin(M_PI*y);
//          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
//          z = sin(M_PI*x)*sin(M_PI*(y+h));
//          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
//          mVertices.push_back(Vertex{x,y+h,z,x,y,z});
//          z = sin(M_PI*(x+h))*sin(M_PI*y);
//          mVertices.push_back(Vertex{x+h,y,z,x,y,z});
//          z = sin(M_PI*(x+h))*sin(M_PI*(y+h));
//          mVertices.push_back(Vertex{x+h,y+h,z,x,y,z});
//      }
//}


void LineObject::readFile(std::string filnavn)
{
   std::ifstream inn;
   inn.open(filnavn.c_str());


   if (inn.is_open()) {
       int n;
       Vertex vertex;
       inn >> n;
       mVertices.reserve(n);
       for (int i=0; i<n; i++) {
            inn >> vertex;
            mVertices.push_back(vertex);
       }
       inn.close();
   }
}

void LineObject::init(GLint matrixUniform)
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

void LineObject::draw()
{
   glBindVertexArray( mVAO );
   glUniformMatrix4fv( mMatrixUniform, 1, GL_FALSE, mMatrix.constData());
   glDrawArrays(GL_LINE_LOOP, 0, mVertices.size());
}

void LineObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
}

void LineObject::rotate()
{
    mMatrix.rotate(2.f, 0.f, 1.0f, 0.f);
}


void LineObject::rotate(float x, float y, float z, float a)
{
    mMatrix.rotate(x,y,z,a);
}
