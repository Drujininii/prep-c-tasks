//
// Created by ed_grolsh on 01.11.16.
//

#ifndef DZ6_ENTE_DATA_H
#define DZ6_ENTE_DATA_H


#include "Volume_Figure.h"

class Enter_Data {
public:
    Enter_Data();
    ~Enter_Data();
    void add_data();
    bool choice();
    bool memory_check();
    bool ask_one_more();
    bool add_ball();
    bool add_cylinder();
    bool number_check(double, char *);
    void show();
private:
    int max_ell;
    int current_ell;
    Volume_Figure **volume_figure;

};


#endif //DZ6_ENTE_DATA_H
