#ifndef TRIANGLESURFACE_H
#define TRIANGLESURFACE_H


#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"


class TriangleSurface : public VisualObject
{
private:

public:
   TriangleSurface();
   TriangleSurface(std::string filnavn);
   ~TriangleSurface() override;
   // void construct();
   void readFile(std::string filnavn);
   void init(GLint shader) override;
   void draw() override;
   void move(float x, float y, float z) override;
   void rotate() override;
   void rotate2();
   void rotate(float x, float y, float z, float a);
};

#endif
