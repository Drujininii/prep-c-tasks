//
// Created by ed_grolsh on 30.11.16.
//

#ifndef LABIRINT_FIELD_H
#define LABIRINT_FIELD_H


#include <vector>
#include <istream>
#include <chrono>

//#include "Runner.hpp"
#include "utils.h"


using std::vector;

class Field {
private:
    struct Position {
        size_t i;
        size_t j;
    };

    size_t rows;
    size_t cols;
    size_t tic_count = 0;
    bool done = false;


    vector<vector<int>> field;

    std::chrono::steady_clock::time_point start_time;

    std::chrono::microseconds get_time_elapsed_mcs() const;
   Direction prev_directions;


public:
    Field(){prev_directions = Direction::UP;}
    Position start_position;
    Position final_position;
    Position current_position;
    void alg(size_t i, size_t j, int &n);
    void print();
    friend std::istream& operator>>(std::istream& is, Field& field);
    void check_lockup(size_t i, size_t j);
    void return_dir();

    bool tic();
    bool is_done();


    void result(std::ostream& os);
    void start();
};

std::istream& operator>>(std::istream& is, Field& field);
std::istream& operator>>(std::istream& is, BlockType& block_type);


#endif //LABYRINTH_FIELD_HPP


