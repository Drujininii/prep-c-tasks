//
// Created by ed_grolsh on 24.10.16.
//

#include "Worker.h"
#include <iostream>
#include <cstring>
#include <cstddef>
#include <ctype.h>
#include <limits>
#include <string.h>
#include <fstream>
#include <cctype>

#define current_year 2016
#define Ml 1000000
#define Mb 1024*1024
#define ERR_WRITE is.clear();\
errnum = 2;\
return is;


int errnum;

Workers::Workers() {
    max_number_of_workers = 10;
    if (sizeof(Worker) * max_number_of_workers < 250 * Mb) {
        workers = new class Worker[max_number_of_workers];
        if (workers == nullptr) {
            std::cout << "Ошибка выделения памяти" << std::endl;
            errnum = 1;
            return;
        }
        current_number_of_workers = 0;
    }
    else {
        std::cout << "Ошибка выделения памяти" << std::endl;
        errnum = 1;
        return;
    }
}

Workers::~Workers()
{
    delete[] workers;
}

void Workers::set_worker()
{
    char choice = '0';
    while(choice != 'n') {//выделение памяти
        if ((current_number_of_workers == max_number_of_workers) && ((sizeof(Worker) * max_number_of_workers) < (250 * Mb)))
        {
            class Worker *temp_mem;
            int new_max_number = max_number_of_workers * 2;
            temp_mem = new class Worker[new_max_number];
            if(temp_mem == nullptr) {
                std::cout << "Ошибка выделения памяти 1" << std::endl;
                errnum = 4;
                return;
            }
            for (int i = 0; i < max_number_of_workers; i++)                      //написать конструктор копирования
                temp_mem[i] = workers[i];
            delete[] workers;
            workers = temp_mem;
            max_number_of_workers = new_max_number;
        }
        else if(current_number_of_workers == max_number_of_workers){
            std::cout << "Ошибка выделения памяти 2" << std::endl;
            errnum = 5;
            return;
        }
        std::cin >> workers[current_number_of_workers];//добавление записи
        if(errnum != 0)
            return;
        current_number_of_workers++;

        std::cout << "Добавить еще работника? (y/n)" << std::endl;
        do {                                                           //как определить количество символов в потоке??
            choice = (char) std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        while((choice != 'y') && (choice != 'n'));
    }
}


std::ostream &operator << (std::ostream &os, const class Worker &worker)
{
    os << worker.name << ", " << worker.position << ", ";
    os << worker.year_revenue << ", " << worker.salary << " " << "рублей" << std::endl;
    return os;
}

std::istream &operator >> (std::istream &is, class Worker &worker) {
    char buffer[40];
   //ввод фамилии
    if(worker.name_write(buffer, is) != nullptr)
        ;
    else {
        ERR_WRITE
    }
    //ввод инициалов
    std::cout << "Введите инициалы без пробелов латинскими буквами(пример: I.I.)" << std::endl;
    is.get(buffer, 5);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    strcat(worker.name, buffer);
    //проверка имени на валидность
    if(worker.test_name(buffer, is) != nullptr)
        ;
    else {
        ERR_WRITE
    }
    std::cout << "ФИО: " << worker.name <<  std::endl;
    //ввод должности
    std::cout << "Введите должность(максимум 39 символов)" << std::endl;
    is.get(worker.position, 39);
    for (auto i = 0; worker.position[i] != '\0'; i++)
        if (isalpha(worker.name[i]))
            worker.position[i] = tolower(worker.position[i]);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //ввод года трудоустройства
    if(worker.year_test_valid(buffer, is) != nullptr)
        ;
    else {
        ERR_WRITE
    }
    //ввод зарплаты
    if(worker.write_salary(buffer, is) != nullptr)
        ;
    else {
        ERR_WRITE
    }
    return is;
}

char *Worker::year_test_valid(char *buffer, std::istream &is)
{
    std::cout << "Введите год трудоустройства" << std::endl;
    do {
        is >> buffer;
        auto i = 0;
        while(buffer[i] != '\0')
            if(isdigit(buffer[i]) && i < 4)
                i++;
            else {
                std::cout << "Недопустимый формат года" << std::endl;
                is.clear();
                errnum = 2;
                return nullptr;
            }
        year_revenue = atoi(buffer);
        if (year_revenue < 2017 && year_revenue > 1930) {
            std::cout << year_revenue << std::endl;
            break;
        } else
            std::cout << year_revenue << " - очень странный год трудоустрйоства, введите еще раз" << std::endl;
    }
    while(year_revenue >= 2017 || year_revenue <= 1930);
    return buffer;
}

char *Worker::name_write(char *buffer, std::istream &is)
{
    std::cout << "Введите Фамилию латинскими буквами(максимум 35 символов)" << std::endl;
    is.get(name, 34);     //контроль ввода!
    if (is.good());
    else {
        std::cout << "Ошибка при записи" << std::endl;
        is.clear();
        errnum = 2;
        return nullptr;
    }
    int i = 0;
    while (name[i] != '\0')
        i++;
    name[i] = ' ';
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return buffer;
}

char *Worker::write_salary(char *buffer, std::istream &is)
{
    std::cout << "Введите зарплату в рублях(максимум 10млн)" << std::endl;
    is.get(buffer, 9);
    auto i = 0;
    while(buffer[i] != '\0')
        if((isdigit(buffer[i]) || buffer[i] == '.') && i < 8)
            i++;
        else {
            std::cout << "Недопустимый формат зарплаты" << std::endl;
            is.clear();
            errnum = 2;
            return nullptr;
        }
    salary = atof(buffer);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return buffer;
}

char *Worker::test_name(char *buffer, std::istream &is)
{
    for (auto i = 0; name[i] != '\0'; i++){
        if (isalpha(name[i]))
            name[i] = toupper(name[i]);
        else if (name[i] == ' ' || name[i] == '.')
            continue;
        else {
            std::cout << "Недопустимые значения ФИО" << std::endl;
            is.clear();
            errnum = 2;
            return nullptr;
        }
    }
    return buffer;
}

const class Worker &Workers::get_worker(int number)
{
    if(number > 0 && number <= current_number_of_workers)
    return workers[number - 1];
    else{
        std::cout << "Неверный номер работника." <<std::endl;
        errnum = 3;
        return workers[current_number_of_workers - 1];
    }
}

void Workers::get_more_year()
{
    char buffer[3];
    std::cout << "Введите необходимый стаж(максимум 99)" << std::endl;
    std::cin.get(buffer, 2);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto i = 0;
    while(buffer[i] != '\0'){
        if(buffer[i] >= '0' && buffer[i] <= '9' && i < 3)
        i++;
        else{
            std::cout << "Недопустимый формат стажа" << std::endl;
            errnum = 6;
            return;
        }
    }
    auto experience = atoi(buffer);
    if(experience >= 0 && experience <= 100)
    for(auto i = 0; i < current_number_of_workers; i++){
        if((current_year - workers[i].get_years()) > experience)
            std::cout << workers[i];
    }
    else {
        std::cout << "Неверный формат стажа" << std::endl;
        errnum = 4;
        return;
    }
}

int Worker::get_years()
{
    return year_revenue;
}

void Workers::get_more_salary()
{
    char buffer[9];
    std::cout << "Введите порог поиска по зарплате(максимум 10 млн)" << std::endl;
    std::cin.get(buffer, 8);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    auto i = 0;
    while(buffer[i] != '\0')
        if(buffer[i] >= '0' && buffer[i] <= '9' && i < 8)
        i++;
        else {
            std::cout << "Недопустимый формат заработной платы" << std::endl;
            errnum = 7;
            return;
        }
    auto salary = atof(buffer);
    if(salary >= 0 && salary <= 10*Ml)
        for(auto i = 0; i < current_number_of_workers; i++){
            if((workers[i].get_salary()) > salary)
                std::cout << workers[i];
        }
    else {
        std::cout << "Неверный формат заработной платы" << std::endl;
        errnum = 4;
        return;
    }
}

auto Worker::get_salary()-> decltype(salary)
{
    return salary;
}

void Workers::get_list_position()
{
    auto i = 0;
    char find_position[40];
    std::cout << "Введите должность для поиска(максимум 39 символов)" << std::endl;
    std::cin.get(find_position, 39);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while(find_position[i] != '\0') {
        find_position[i] = tolower(find_position[i]);
        i++;
    }
    for(auto i = 0; i < current_number_of_workers; i++){
        if(workers[i].get_position(find_position)){
            std::cout << workers[i];
        }
        else {
            std::cout << "Нет работника с такой должностью" << std::endl;
            return;
        }
    }
}

bool Worker::get_position(const char *find_position)
{
    if(strcmp(position, find_position) == 0)
        return true;
    else
        return false;
}
