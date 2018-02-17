//
// Created by ed_grolsh on 30.11.16.
//

#include "test_txt.h"
#include <fstream>
#include <iostream>

void test_txt::read() {
    int val = 0;
    std::ifstream fin;
    fin.open("Runner.txt");
    while(fin>>val){
        dir.push_back(static_cast<Direction >(val));
    }

    fin.close();
}

//void test_txt::print() {
//    int i = 0;
//    for(; i < dir.size(); ++i)
//    std::cout << static_cast<int>(dir[i]);
//}
