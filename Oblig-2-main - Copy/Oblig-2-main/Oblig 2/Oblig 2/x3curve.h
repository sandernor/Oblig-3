#ifndef X3CURVE_H
#define X3CURVE_H

#include "visualobject.h"

class X3Curve : public VisualObject
{
public:
    X3Curve(bool inPoints = false);
    ~X3Curve() override;
    void init(GLint shader) override;
    void draw() override;
    void generate();
    void curvePoints(double xMin, double xMax);
    void rotate() override;
    void move1();

    float a = 0, b = 0, c = 0, d = 0;

private:
    QMatrix4x4 A;

    QVector4D B;
    QVector4D x;
    bool points = false;

    double xFunction(double x) const;
};

#endif // X3CURVE_H
