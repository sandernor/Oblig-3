#ifndef DOOR_H
#define DOOR_H

#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex2.h"
#include "VisualObject.h"
#include "cube3.h"

class DOOR : public VisualObject
{
private:
   std::vector<Vertex> mVertices;
   //QOpenGLContext *mContext;

public:
   DOOR();
   ~DOOR();
   //void setContext(QOpenGLContext *context);
   void init(GLint matrixUniform) override;
   void draw() override;
   void rotate() override;
   void move(float x, float y, float z) override;
   bool collision(player* player1);
   void open();

   float m_xyz[3];
   bool openD = false;
   bool once = false;
};

#endif // DOOR_H
