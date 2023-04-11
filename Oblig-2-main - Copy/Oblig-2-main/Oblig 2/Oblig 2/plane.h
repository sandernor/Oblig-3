 #ifndef PLANE_H
#define PLANE_H


#include <QOpenGLFunctions_4_1_Core>
#include <vector>
#include "vertex2.h"
#include "VisualObject.h"

class PLANE : public VisualObject
{
private:
   std::vector<Vertex> mVertices;
   //QOpenGLContext *mContext;

public:
   PLANE();
   ~PLANE();
   //void setContext(QOpenGLContext *context);
   void init(GLint matrixUniform) override;
   void draw() override;
   void rotate() override;
   void move(float x, float y, float z) override;
};

#endif // PLANE_H
