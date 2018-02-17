//
// Created by ed_grolsh on 31.10.16.
//

#ifndef DZ6_FIGURE_H
#define DZ6_FIGURE_H

#include <iostream>

class Volume_Figure {
public:
    virtual ~Volume_Figure(){std::cout << "dest V F";}
    virtual double volume() = 0;
    virtual double area() = 0;
    virtual void show_figure_data() = 0;
};


#endif //DZ6_FIGURE_H
