#ifndef GRAPHPOINTS_H
#define GRAPHPOINTS_H


#include <fstream>
#include <iostream>
#include <vertex.h>
#include <QFile>
#include <QTextStream>
#include "visualobject.h"
#include "QVector3D"


class GraphPoints : public VisualObject
{
public:
    GraphPoints();

    GraphPoints(std::string filnavn);
    ~GraphPoints() override;
    void readFile(std::string filnavn);
    void toFile(std::string filnavn);
    void init(GLint shader) override;
    void draw() override;
    void construct();
};

#endif // GRAPHPOINTS_H
