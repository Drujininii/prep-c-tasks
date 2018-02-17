//
// Created by tsv on 09.05.16.
//

#include "Runner.hpp"

Runner::Runner() :dir({1, 3, 1, 3, 1, 1, 2, 2, 1, 1, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0,
                       3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 3, 0, 0, 0,
                       3, 3, 3, 1, 1, 3, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 3, 1, 3, 3, 0, 0,
                       3, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0})
{
    dir.pop_back(); prev_directions = Direction::RIGHT; count = 0;
}

Direction Runner::step() {
    return static_cast<Direction>(dir[count++]);
}


