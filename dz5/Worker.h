//
// Created by ed_grolsh on 24.10.16.
//

#ifndef DZ5_WORKER_H
#define DZ5_WORKER_H

#include <iostream>
#include <cstring>
class Worker;
std::ostream &operator << (std::ostream &os, const Worker &worker);

    class Workers {
    public:
        Workers();
        ~Workers();
        void set_worker();
        const class Worker &get_worker(const int);
        void get_more_year();
        void get_more_salary();
        void get_list_position();
    private:
        class Worker *workers;
        int current_number_of_workers;
        int max_number_of_workers;
    };

    class Worker {
    public:
        Worker() {
            name = new char[40];
            position = new char[40];
            *position = '\0';
            year_revenue = 0;
            salary = 0;
        }
        Worker(const Worker &another){
            name = new char[40];
            strcpy(name, another.name);
            position = new char[40];
            strcpy(position, another.position);
            year_revenue = another.year_revenue;
            salary = another.salary;
        }
        ~Worker(){
            delete[] name;
            delete[] position;
            year_revenue = 0;
            salary = 0;
        }
        void set();
        void get(char *);
        int get_years();
        auto get_salary();
        bool get_position(const char *);
        friend std::ostream &operator << (std::ostream &os, const Worker &worker);
        friend std::istream &operator >> (std::istream &is, class Worker &worker);
        char *year_test_valid(char *buffer, std::istream &is);
        char *name_write(char *buffer, std::istream &is);
        char *write_salary(char *buffer, std::istream &is);
        char *test_name(char *buffer, std::istream &is);
    private:
        char *name;
        char *position;
        int year_revenue;
    public:
        double salary;
    };


#endif //DZ5_WORKER_H
