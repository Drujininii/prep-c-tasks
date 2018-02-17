//
// Created by ed_grolsh on 31.10.16.
//

#include "Cylinder.h"
#include <iostream>


double Cylinder::area()
{
    return circumference(r)*h + 2*area_circle(r);
}

double Cylinder::volume()
{
    return area_circle(r)*h;
}

void Cylinder::show_figure_data()
{
    std::cout << "Cylinder radius: " << r << " Cylinder height: " << h
              << " Cylinder volume = " << volume() << " Cylinder area = " << area()
              << std::endl;
}