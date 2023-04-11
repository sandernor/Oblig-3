#ifndef FXY_H
#define FXY_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"
#include "cube3.h"
#include "boat.h"

class fxy : public VisualObject
{
private:

public:
   fxy();
   ~fxy() override;
   void init(GLint matrixUniform) override;
   void draw() override;
   void rotate() override;
   void write(std::string filnavn);
   void collision(player* player1, BOAT* boat);
};
#endif // FXY_H
