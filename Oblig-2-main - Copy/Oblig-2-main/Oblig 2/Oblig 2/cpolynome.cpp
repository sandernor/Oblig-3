#include "cpolynome.h"


KubiskPolynom::KubiskPolynom() //: VisualCurve()
{
   // regner ut punkter for oppgave 4.6.2
   // (0,1), (1/2, 9/16), (3/2, -5/16), (3, 4)
   // Ser at x går fra 0 til 3


   // Jukser litt og bare velger noen konstanter nå
   // Neste steg: Bruke konstantene fra oppgave 4.6.2


   // Disse finner vi ved å løse et 4x4 ligningssystem
   // Vi kan programmere det, men det var tanken her at dere
   // skulle bruke et annet verktøy og så sette inn tallene
   // Fra fasit: a=0.5, b=-1.0, c=-0.5, d=1.0


   double  a{0.5}, b{-1.0}, c{-0.5}, d{1.0}, dx=0.1;
   for (auto x=0.0; x<3.001; x+=dx)
   {
       auto y = p(a, b, c, d, x);
       mVertices.push_back(Vertex(x, y,0,0,1,0));
   }
   mMatrix.setToIdentity();
}


KubiskPolynom::~KubiskPolynom()
{


}


double KubiskPolynom::p(double a, double b, double c, double d, double x)
{
  return a* x*x*x + b*x*x + c*x + d;
}
