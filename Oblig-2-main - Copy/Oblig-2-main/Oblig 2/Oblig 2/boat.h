#ifndef BOAT_H
#define BOAT_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"
#include "cube3.h"

class BOAT : public VisualObject
{
private:

public:
    BOAT();
    ~BOAT() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;
    void follow(player* player1);

    float m_xyz[3];
};

#endif // BOAT_H
