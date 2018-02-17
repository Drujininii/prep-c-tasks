//
// Created by tsv on 09.05.16.
//

#include "Field.h"
#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;

std::istream& operator>>(std::istream& is, Field& field)
{
    size_t rows = 0;
    size_t cols = 0;

    is >> rows >> cols;

    field.cols = cols;
    field.rows = rows;
    field.field.resize(rows);
    for (auto& row: field.field) {
        row.resize(cols);
    }
    cout << rows << " " << cols << endl;

    BlockType block_type;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            is >> field.field[i][j];
            if (field.field[i][j] == 2) {
                field.start_position = {i, j};
                field.field[i][j] = -1;
            }
            if (field.field[i][j] == 3) {
                field.final_position = {i, j};
                field.field[i][j] = 2;
            }
        }
    }
    return is;
}


bool Field::is_done()
{
    return done;
}

void Field::result(std::ostream& os)
{
    const auto elapsed_time_mcs = get_time_elapsed_mcs().count();
    os << "Total steps: " << tic_count << ", time: " << elapsed_time_mcs << " mcs" << std::endl;
}

void Field::start()
{
    start_time = std::chrono::steady_clock::now();
}

std::chrono::microseconds Field::get_time_elapsed_mcs() const
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_time);
}

//void Field::print() {
//    ofstream fout;
//    fout.open("Map.txt", ios_base::out | ios_base::trunc);
//    for (size_t i = 0; i < field.size(); ++i) {
//        for (size_t j = 0; j < field.size(); ++j) {
//            fout << field[i][j];
//            fout << "\t";
//            }
//        fout << '\n';
//        }
//    fout.close();
//    }

void Field::alg(size_t i, size_t j, int &n) {
    while(1) {
        if (field[i - 1][j] == -1){
            field[start_position.i][start_position.j] = n;
            return;
        }
        if (field[i + 1][j] == -1){
            field[start_position.i][start_position.j] = n;
            return;
        }

        if (field[i][j - 1] == -1) {
            field[start_position.i][start_position.j] = n;
            return;
        }
        if (field[i][j + 1] == -1) {
            field[start_position.i][start_position.j] = n;
            return;
        }

//        cout << n << endl;
        switch (prev_directions) {//проверка и выход из тупика
            case Direction::UP: {
                if ((field[i - 1][j] == 1 || field[i - 1][j] < (n - 1))
                    && (field[i][j - 1] == 1 || field[i][j - 1] < (n - 1))
                    && (field[i][j + 1] == 1 || field[i][j + 1] < (n - 1))) {
                    check_lockup(i, j);

                    i = current_position.i;
                    j = current_position.j;
                    n = field[i][j] + 1;
                }
                break;
            }
            case Direction::LEFT: {
                if ((field[i - 1][j] == 1 || field[i - 1][j] < (n - 1))
                    && (field[i][j - 1] == 1 || field[i][j - 1] < (n - 1))
                    && (field[i + 1][j] == 1 || field[i + 1][j] < (n - 1))) {
                    check_lockup(i, j);
                    i = current_position.i;
                    j = current_position.j;
                    n = field[i][j] + 1;
                }
                break;
            }
            case Direction::RIGHT: {
                if ((field[i - 1][j] == 1 || field[i - 1][j] < (n - 1))
                    && (field[i][j + 1] == 1 || field[i][j + 1] < (n - 1))
                    && (field[i + 1][j] == 1 || field[i + 1][j] < (n - 1))) {
                    check_lockup(i, j);
                    i = current_position.i;
                    j = current_position.j;
                    n = field[i][j] + 1;
                }
                break;
            }
            case Direction::DOWN: {
                if ((field[i + 1][j] == 1 || field[i + 1][j] < (n - 1))
                    && (field[i][j - 1] == 1 || field[i][j - 1] < (n - 1))
                    && (field[i][j + 1] == 1 || field[i][j + 1] < (n - 1))) {
                    check_lockup(i, j);
                    i = current_position.i;
                    j = current_position.j;
                    n = field[i][j] + 1;
                }
                break;
            }
        }


        i--;
        if (field[i][j] == 0) {
            field[i][j] = n;
            n++;
            prev_directions = Direction::UP;
            continue;
        }
        i++;
        i++;
        if (field[i][j] == 0) {
            field[i][j] = n;
            n++;
            prev_directions = Direction::DOWN;
            continue;
        }
        i--;

        j++;
        if (field[i][j] == 0) {
            field[i][j] = n;
            n++;
            prev_directions = Direction::RIGHT;
            continue;
        }
        j--;
        j--;
        if (field[i][j] == 0) {
            field[i][j] = n;
            n++;
            prev_directions = Direction::LEFT;
            continue;
        }
        j++;
    }
}

void Field::check_lockup(size_t i, size_t j) {
    int k = 0;
    while((field[i+1][j] != 0) && (field[i-1][j] != 0) && (field[i][j-1] != 0) && (field[i][j+1] != 0)){
        k++;
        if(field[i+1][j] == field[i][j] - 1)
            i++;
        else if(field[i-1][j] == field[i][j] - 1)
            i--;
        else if(field[i][j+1] == field[i][j] - 1)
            j++;
        else if(field[i][j-1] == field[i][j] - 1)
            j--;
        else {
            cout << "error check_lockup" << endl;
            throw;
        }
    }
    current_position.i = i;
    current_position.j = j;

    return;
}

void Field::return_dir() {
    ofstream fout;
    fout.open("Runner.txt", ios_base::out | ios_base::trunc);
    size_t i = start_position.i;
    size_t j = start_position.j;
    fout << "#include \"Runner.hpp\"" << endl;
    fout << "Runner::Runner() :dir({";
    while(field[i][j] != 2){
        if(field[i-1][j] == field[i][j] - 1){
            fout << "0" << "," << " ";
            i--;
            continue;
        }
        if(field[i+1][j] == field[i][j] - 1){
            fout << "1" << "," <<" ";
            i++;
            continue;
        }
        if(field[i][j-1] == field[i][j] - 1){
            fout << "2" <<  "," <<" ";
            j--;
            continue;
        }
        if(field[i][j+1] == field[i][j] - 1){
            fout << "3" << "," << " ";
            j++;
            continue;
        }
    }
    fout << "0";
    fout << "})" << endl;
    fout << "{dir.pop_back(); prev_directions = Direction::RIGHT; count = 0;}" << endl;
    fout << "Direction Runner::step() {return static_cast<Direction>(dir[count++]); }" << endl;
    fout.close();
    std::cout << "ok" << std::endl;
}


