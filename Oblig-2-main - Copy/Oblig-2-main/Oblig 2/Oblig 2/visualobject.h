#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"

class VisualObject : public QOpenGLFunctions_4_1_Core {
public:
   VisualObject();
   ~VisualObject();
   virtual void init(GLint matrixUniform)=0;
   virtual void draw()=0;
   virtual void rotate()=0;
   virtual void move(float x, float y, float z) {;}
   //virtual void rotate()=0;
      QMatrix4x4 mMatrix;
std::vector<Vertex> mVertices;

protected:
//   std::vector<Vertex> mVertices;
   GLuint mVAO{0};
   GLuint mVBO{0};
   GLint mMatrixUniform{0};

   QMatrix4x4 mPosition;
   QMatrix4x4 mRotation;
   QMatrix4x4 mScale;
};
#endif // VISUALOBJECT_H
