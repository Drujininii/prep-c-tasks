// Tournamentsort.cpp: определяет точку входа для консольного приложения.
//

#include <vector>
#include <iostream>
#include "TournamentSort.hpp"


template<class T>
class Tour_tree;


using std::cout;
using std::cin;
using std::endl;

template<typename T>
void tournament_sort(std::vector<T> &vector);


template<class T>
void tournament_sort(std::vector<T> &vector) {
    Tour_tree<T> tree(vector);//необходимо явно передавать минимальное значение, т.к. вектор шаблонный
}


int main() {
    std::vector<int> vector = {10, 2, 14, 126, 31, 0};
    tournament_sort(vector);
    for (int i = 0; i < vector.size(); i++) {
        cout << vector[i] << ' ';
    }
    cout << endl;
    return 0;
}