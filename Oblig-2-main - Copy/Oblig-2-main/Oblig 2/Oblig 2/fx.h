#ifndef FX_H
#define FX_H


#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class fx : public VisualObject
{
private:

public:
   fx();
   ~fx() override;
   void init(GLint matrixUniform) override;
   void draw() override;
   void rotate() override;
   void write(std::string filnavn);
   float numInt();
};

#endif // FX_H
