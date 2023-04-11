#ifndef VISUALCURVE_H
#define VISUALCURVE_H


#include "visualobject.h"


class VisualCurve : public VisualObject
{
public:
   VisualCurve();
   ~VisualCurve() override;
   void init(GLint matrixUniform) override;
   void draw() override;
};


#endif // VISUALCURVE_H
