#ifndef TEXTUREDCUBE_H
#define TEXTUREDCUBE_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class texCube: public VisualObject
{
private:

public:
    texCube();
    ~texCube() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;

    float tcPos[3];
    std::vector<Vertex> points;

    class QOpenGLTexture* texture;
    QString texturepath;

    GLint texUniform{0};


};
#endif // TEXTUREDCUBE_H
