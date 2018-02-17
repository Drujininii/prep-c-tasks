//
// Created by ed_grolsh on 31.10.16.
//

#include "Ball.h"
#include <iostream>
#include <math.h>

double Ball::volume()
{
    return (4/3)*area_circle(r)*r;
}

double Ball::area()
{
    return 2*r*circumference(r);
}

void Ball::show_figure_data()
{
    std::cout << "Ball radius: " << r << " Ball volume = " << volume() << " Ball area = " << area() << std::endl;
}