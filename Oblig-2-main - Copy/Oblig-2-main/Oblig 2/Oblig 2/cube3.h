#ifndef CUBE3_H
#define CUBE3_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class player : public VisualObject
{
private:

public:
    player();
    ~player() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void drawBoat();
    void move(float x, float y, float z) override;
    void rotate() override;
    void rotate2();

    float m_xyz[3];
    bool boat = false;
    std::vector<Vertex> camCirk;

    std::vector<Vertex> boatV;
};

#endif // CUBE3_H
