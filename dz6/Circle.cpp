//
// Created by ed_grolsh on 31.10.16.
//

#include "Circle.h"
#include <math.h>

double Circle::area_circle(double r)
{
    return M_PI*r*r;
}

double Circle::circumference(double r)
{
    return 2*M_PI*r;
}