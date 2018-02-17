//
// Created by ed_grolsh on 31.10.16.
//

#ifndef DZ6_BALL_H
#define DZ6_BALL_H


#include <iostream>
#include "Volume_Figure.h"
#include "Circle.h"

class Ball: public Volume_Figure, virtual protected Circle {
public:
    //~Ball(){std::cout << "dest Ball" << std::endl;}
    Ball(double radius) {r = radius;}
    double volume();
    double area();
    void show_figure_data();
private:
    double r;
};


#endif //DZ6_BALL_H
