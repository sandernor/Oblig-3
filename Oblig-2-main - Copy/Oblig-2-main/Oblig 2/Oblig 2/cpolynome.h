#ifndef KUBISKPOLYNOM_H
#define KUBISKPOLYNOM_H


#include "visualcurve.h"


class KubiskPolynom : public VisualCurve
{
public:
   KubiskPolynom();
   ~KubiskPolynom();
private:
   double p(double a, double b, double c, double d, double x);
};


#endif // KUBISKPOLYNOM_H
