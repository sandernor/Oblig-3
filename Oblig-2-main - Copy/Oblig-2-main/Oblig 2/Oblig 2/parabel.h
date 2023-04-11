#ifndef PARABEL_H
#define PARABEL_H

#include "visualobject.h"

class Parabel : public VisualObject
{
public:
    Parabel(bool inPoints = false);
    ~Parabel() override;

    void init(GLint matrixUniform) override;
    void draw() override;
    void matrixSet(const std::vector<Vertex> &points);
    void curvePoints(double xMin, double xMax);
    void rotate() override;
    void write(std::string filnavn);

private:
    double xFunction(double x) const;
    std::vector<double> QR(const std::vector<std::vector<double>> &A, const std::vector<double> &b);
    double dotProduct(const std::vector<std::vector<double>> &A, const std::vector<double> &b, int j);

    bool points = false;
    double a = 0, b = 0, c = 0;
};

#endif // PARABEL_H
