#ifndef VERTEX2_H
#define VERTEX2_H

//#include "qvectornd.h"
#include <iostream>
#include <fstream>
#include <QOpenGLFunctions_4_1_Core>
#include <QVector3D>

class Vertex {
//! Overloaded ostream operator which writes all vertex data on an open textfile stream
   friend std::ostream& operator<< (std::ostream&, const Vertex&);

   //! Overloaded ostream operator which reads all vertex data from an open textfile stream
   friend std::istream& operator>> (std::istream&, Vertex&);

private:
//    float m_normal[3];
//    float m_st[2];
//    float m_xyz[3];

public:
    float m_xyz[3];
    float m_normal[3];
    float m_st[2];
    QVector3D vNorm;
    int index;
//    QVector3D m_xyz{};

    Vertex();
    Vertex(float x, float y, float z, float r, float g, float b);
    Vertex(float x, float y, float z, float u, float v);
    Vertex(float x, float y, float z);
    Vertex(float x, float y, float z, float r, float g, float b, int i);
};

#endif // VERTEX_H
