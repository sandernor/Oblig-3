#ifndef HOUSE_H
#define HOUSE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"
#include "cube3.h"

class house : public VisualObject
{
private:

public:
    house();
    ~house() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;
    bool collision(player* player1, float d, float e);

    float doorBox[3];
    bool open = false;
    std::vector<Vertex> points;
};


#endif // HOUSE_H
