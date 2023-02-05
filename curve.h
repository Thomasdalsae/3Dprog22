#ifndef CURVE_H
#define CURVE_H

#include <fstream>
#include <iostream>
#include <vertex.h>
#include <QFile>
#include <QTextStream>
#include "visualobject.h"
#include "QVector3D"


class Curve : public VisualObject {
public:
    Curve();
    Curve(std::string filnavn);
    ~Curve() override;
    void readFile(std::string filnavn);
    void toFile(std::string filnavn);
    void init(GLint shader) override;
    void draw() override;
    void construct();
};

#endif // CURVE_H
