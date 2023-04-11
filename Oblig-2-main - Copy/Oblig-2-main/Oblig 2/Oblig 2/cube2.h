#ifndef CUBE2_H
#define CUBE2_H

#include <QOpenGLFunctions_4_1_Core>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class CUBE : public VisualObject
{
private:

public:
    CUBE();
    ~CUBE() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;
};

#endif // CUBE2_H
