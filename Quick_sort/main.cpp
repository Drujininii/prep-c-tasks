// Quicksort.cpp: определяет точку входа для консольного приложения.
//

#include <vector>
#include <iostream>

template<class T>
class Quick_sort {
public:
    Quick_sort(std::vector<T> &vector);
    Quick_sort() = delete;
    ~Quick_sort() {};
private:
    T get_pivot(std::vector<T> &vector, int start_seq, int end_seq);
    int partition(std::vector<T> &vector, int start_seq, int end_seq);
    void quick_sort(std::vector<T> &vector, int start_seq, int end_seq);
};


template<class T>
Quick_sort<T>::Quick_sort(std::vector<T> &vector) {
    quick_sort(vector, 0, vector.size() - 1);
};


template<class T>
void Quick_sort<T>::quick_sort(std::vector<T> &vector, int start_seq, int end_seq) {
    int part_idx = partition(vector, start_seq, end_seq);
    if (end_seq - start_seq <= 1)
        return;
    quick_sort(vector, start_seq, part_idx - 1);
    quick_sort(vector, part_idx + 1, end_seq);
    return;
};


template<class T>
int Quick_sort<T>::partition(std::vector<T> &vector, int start_seq, int end_seq) {
    if (start_seq >= end_seq)
        return 0;
    int pivot = get_pivot(vector, start_seq, end_seq);
    int i = start_seq;
    int j = end_seq - 1;
    while (i < j) {
        while (vector[i] < pivot)
            i++;
        while (vector[j] >= pivot && j >= 0)
            j--;
        if (i < j) {
            std::swap(vector[i], vector[j]);
            i++;
            j--;
        }
    }
    if (vector[i] > vector[end_seq])
        std::swap(vector[i], vector[end_seq]);
    return i;
}


template<class T>
T Quick_sort<T>::get_pivot(std::vector<T> &vector, int start_seq, int end_seq) {
    return vector[end_seq];
}



int main()
{
    std::vector<int> my_vector = {0, 5, 12, 32, 16, 1, -17, 28, 10, 16, 32};
//    int new_elem;
//    for (int i = 0; i < 5; i++) {
//        std::cout << "ENTER new elem: ";
//        std::cin >> new_elem;
//        my_vector.push_back(new_elem);
//    }
    Quick_sort<int> sort_obj(my_vector);
    for (int i = 0; i <  my_vector.size(); i++) {
        std::cout << my_vector[i] << " ";
    }
    return 0;
}

