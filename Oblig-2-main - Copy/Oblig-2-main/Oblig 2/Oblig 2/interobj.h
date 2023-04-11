#ifndef INTEROBJ_H
#define INTEROBJ_H

#include "visualobject.h"

class InterObj : public VisualObject
{
public:
   InterObj();
   ~InterObj() override;
   void init(GLint matrixUniform) override;
   void draw() override;
   void move(float x, float y, float z) override;
   void rotate() override;


private:
   float mx, my, mz; // posisjon
};

#endif
