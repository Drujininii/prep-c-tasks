//
// Created by ed_grolsh on 17.10.16.
//
#include <cstdlib>
#ifndef FIRST_DZ_H
#define FIRST_DZ_H
namespace list {
    class data {
    public:
        data();
        ~data();
        void add_data(const double value);//добавление первого элемента
        void add_data(const double value, data *previous, data *next);//добавление нового элемента
        void set_next(data *);
        void set_previous(data *);
        class data *get_next();
        class data *get_previous();
        double get_elem();

    private:
        class data *previous;
        class data *next;
        double value;
    };

    class dynamic_list {

    public:
        dynamic_list();
        void add_element(const double value);
        double get_element(const size_t number);
        class data *find_data(const size_t i);
        void delete_data(data *ptr);
        size_t get_size();

    private:
        size_t size;
        class data *head;
    };
}

#endif //FIRST_DZ_H

