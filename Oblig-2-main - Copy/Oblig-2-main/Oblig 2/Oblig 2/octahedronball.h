#ifndef OCTAHEDRONBALL_H
#define OCTAHEDRONBALL_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include "vertex2.h"
#include "visualobject.h"

class OctahedronBall : public VisualObject {
private:
   int m_rekursjoner;
   int m_indeks;               // brukes i rekursjon, til å bygge m_vertices
   void lagTriangel(const QVector3D& v1, const QVector3D& v2, const QVector3D& v3);
   void subDivide(const QVector3D& a, const QVector3D& b, const QVector3D& c, int n);
   void oktaederUnitBall();
public:
   OctahedronBall(int n=0);
   ~OctahedronBall();
   void init(GLint matrixUniform)override;
   void draw() override;
   void rotate() override;
   void move(float x, float y, float z) override;

};


#endif // OCTAHEDRONBALL_H
