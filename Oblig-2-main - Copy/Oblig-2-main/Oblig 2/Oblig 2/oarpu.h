#ifndef OARPU_H
#define OARPU_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class Opickup : public VisualObject
{
private:

public:
    Opickup();
    ~Opickup() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;

    float pickPos[3];
    std::vector<Vertex> points;
};


#endif // OARPU_H
