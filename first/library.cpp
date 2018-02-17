//
// Created by ed_grolsh on 17.10.16.
//
#include <iostream>
#include "library.h"
using namespace list;
data::data()
{
    previous = NULL;
    next = NULL;
    value = 0;
}

data::~data()
{
    //delete data;
    previous = NULL;
    next = NULL;
    value = 0;
}

dynamic_list::dynamic_list()
{
    size = 0;
    head = NULL;
}

void dynamic_list::add_element(const double value)
{
    std::cout << "добавление элемента " << value << '\n';
    class data *ptr_new = new class data;
    class data *ptr_last;
    class data *ptr_next;
    if(size == 0) {
        std::cout << "size = " << size <<'\n';
        ptr_new->add_data(value);
        head = ptr_new;
    }
    else {
        ptr_last = find_data(size); //поиск указателя на последний элемент элемент
        ptr_next = ptr_last->get_next();
        ptr_new->add_data(value, ptr_last, ptr_next);
        ptr_last->set_next(ptr_new);
    }
    size++;
    std::cout << "size = " << size <<'\n';

}

class data *dynamic_list::find_data(const size_t i)
{
    class data *ptr;
    ptr = head;
    if(head == NULL){
        std::cout << "в списке нет элементов\n";
    }
    for(size_t j = 0; j < (i - 1); j++){
        ptr = ptr->get_next();
    }
    return ptr;
}

inline class data *data::get_next()
{
    return next;
}

//добавление нового элемента ЭТО  ЗАКОННО?
void data::add_data(const double val, class data *ptr_last, class data *ptr_next)
{
    value = val;
    previous = ptr_last;
    next = ptr_next;
}

//добавление первого элемента
inline void data::add_data(const double val)
{
    value = val;
    std::cout << "добавляемое значени " << value << '\n';
}

inline double data::get_elem()
{
    return value;
}

inline class data *data::get_previous()
{
    return previous;
}

inline void data::set_next(data *ptr_next)
{
    next = ptr_next;
}

inline void data::set_previous(data *ptr_prev)
{
    previous = ptr_prev;
}
//получение элемента
double dynamic_list::get_element(const size_t number)
{
    double val;
    data *ptr;
    data *ptr_prev;
    data *ptr_next;
    ptr = find_data(number);
    val = ptr->get_elem();
    std::cout << "вынимаемое значение " << val << '\n';
    ptr_prev = ptr->get_previous();//получение указателя на предыдущий элемент
    ptr_next = ptr->get_next();//получение указтеля на следующий элемент
    if(ptr_prev != NULL)
        ptr_prev->set_next(ptr_next);//изменение значения указателя на следующий элемент у предыдущего элемента
    else
        std::cout << "список пуст " << '\n';
    if(ptr_next != NULL)
        ptr_next->set_previous(ptr_prev);//изменение значения указателя на предыдщуий элемент у следующего элемента

    delete_data(ptr);   //что удалит? указатель или класс?
    size--;
    return val;
}

void dynamic_list::delete_data(data *ptr)
{
    delete ptr;
}

size_t dynamic_list::get_size()
{
    return size;
}

