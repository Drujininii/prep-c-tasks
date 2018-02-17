//
// Created by ed_grolsh on 30.11.16.
//

#ifndef LABIRINT_TEST_TXT_H
#define LABIRINT_TEST_TXT_H

#include <vector>
#include "utils.h"

class test_txt {
public:
    void read();
    void print();

private:
    std::vector<Direction> dir;

};


#endif //LABIRINT_TEST_TXT_H
