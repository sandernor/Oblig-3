#ifndef PICKUP_H
#define PICKUP_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class pickup : public VisualObject
{
private:

public:
    pickup();
    ~pickup() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;

    float pickPos[3];
    std::vector<Vertex> points;
};

#endif // PICKUP_H
