#ifndef HEIGHTMAPREAD_H
#define HEIGHTMAPREAD_H

#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLTexture>
#include <QColor>
#include <QMatrix4x4>
#include <vector>
#include "vertex2.h"
#include "visualobject.h"

class HR : public VisualObject
{
public:
    HR();
    ~HR() override;
    void init(GLint matrixUniform) override;
    void draw() override;
    void move(float x, float y, float z) override;
    void rotate() override;
    void write(std::string filnavn);

    float tcPos[3];

    int width, height, nChannels;

    class QOpenGLTexture* texture;
    QString texturepath;

    float yValue;
    QColor pColor;
    float yMod = 0.0025;
    float xzMod = 0.01;
    float genMod = 2;
};

#endif // HEIGHTMAPREAD_H
