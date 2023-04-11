#ifndef XYZ2_H
#define XYZ2_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class XYZ : public VisualObject
{
private:

public:
   XYZ();
   ~XYZ() override;
   void init(GLint matrixUniform) override;
   void draw() override;
   void rotate() override;
};
#endif // XYZ_H
