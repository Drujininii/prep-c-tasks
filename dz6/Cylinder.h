//
// Created by ed_grolsh on 31.10.16.
//

#ifndef DZ6_CYLINDER_H
#define DZ6_CYLINDER_H


#include "Volume_Figure.h"
#include "Circle.h"

class Cylinder: public Volume_Figure, virtual protected Circle {
public:
    //~Cylinder() {std::cout << "dest Cylinder" << std::endl;}
    Cylinder(double radius, double height) {r = radius; h = height;}
    double volume();
    double area();
    void show_figure_data();
private:
    double r;
    double h;
};

#endif //DZ6_CYLINDER_H
