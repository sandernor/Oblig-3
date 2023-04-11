#ifndef TETRA2_H
#define TETRA2_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"
#include "cube3.h"

class TETRA : public VisualObject
{
private:

public:
    TETRA();
    ~TETRA() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void rotate() override;
    void move(float x, float y, float z) override;
    void move(float dt, double a, double b, double c, double d);
    double xFunction(double x, double a, double b, double c, double d) const;
    void move(player* player1);

    QVector3D mVelocity{-1, 0, 0};
    QVector3D mPosition{0, 0, 0};

    QVector3D LastPos{0, 0, 0};
    bool back = false;
    bool attack = false;
    bool done = true;
    bool done2 = false;
};

#endif // CUBE2_H
