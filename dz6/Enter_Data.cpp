//
// Created by ed_grolsh on 01.11.16.
//
//переполнение дабла статья
#include "Enter_Data.h"
#include "Ball.h"
#include "Cylinder.h"
#include <iostream>
#include <limits>
#include <climits>

#define MEMORY_ERROR 1;
//#define NUMBERS_ERROR 2;

unsigned short int err_code;

Enter_Data::Enter_Data() {
    max_ell = 0;
    current_ell = 0;
    volume_figure = NULL;
}


Enter_Data::~Enter_Data()
{
    current_ell = 0;
    max_ell = 0;
}


void Enter_Data::add_data()
{
    while(ask_one_more())
    {
        if (memory_check());
        else {
            std::cout << "Memory ERROR" << std::endl;
            err_code = MEMORY_ERROR;
            return;
        }
        if (choice()) {//стоит ли поменять синтаксис функции?
            if(add_ball());
            else{
                continue;
            }
        }
        else {
            if(add_cylinder());
            else{
                continue;
            }
        }
    }
}


bool Enter_Data::ask_one_more()
{
    char choice;
    std::cout << "Add one more figure? (y/n)" << std::endl;
    do {
        choice = (char) std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while(choice != 'y' && choice != 'n');
    return choice == 'y';
}


bool Enter_Data::memory_check()
{
    if(current_ell != max_ell && current_ell != 0)
        return true;
    int new_max_ell;
    new_max_ell = (max_ell*2 + 1);
    Volume_Figure **temp = new Volume_Figure* [new_max_ell];//Вопрос к Титаевскому по уменьшению быстродействия с массивом указателей
    if(current_ell != 0) {
        for (auto i = 0; i < current_ell; i++) //подразумевается проверка на исключения
            temp[i] = volume_figure[i];                                                                                  //правильная ли операция копирования? я же копирую только указатели?
                                                                                                                        //правильно ли удаление указателей? нужно очистить память только от указателей, но не от данных}
        delete[] volume_figure;                                                                                         //не вызовет ли деструктор объектов?
    }
    volume_figure = temp;
    max_ell = new_max_ell;
    return true;
}


bool Enter_Data::choice()
{
    char choice;
    std::cout << "Would you add ball or cylinder? (b/c)" << std::endl;
    do {
        std::cout << '\r';
        choice = (char) std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while ((choice != 'b') && (choice != 'c'));
    return choice == 'b';
}


bool Enter_Data::add_ball()
{
    char buffer[256] = {0};
    char *end_ptr;
    std::cout << "Enter ball radius: " << std::endl;
    std::cin >> buffer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    double radius = strtod(buffer, &end_ptr);

    if(number_check(radius, end_ptr));
    else
        return false;

    volume_figure[current_ell] = new Ball(radius);
    current_ell++;//подразумевается проверка на исключения
    return true;
}


bool Enter_Data::add_cylinder()
{
    char buffer[256];
    char* end_ptr;
    std::cout << "Enter cylinder radius: " << std::endl;
    std::cin >> buffer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    double radius = strtod(buffer, &end_ptr);

    if(number_check(radius, end_ptr));
    else
        return false;

    std::cout << "Enter cylinder height: " << std::endl;
    std::cin >> buffer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    double height = strtod(buffer, &end_ptr);
    if(number_check(height, end_ptr));
    else
        return false;

    volume_figure[current_ell] = new Cylinder(radius, height);
    current_ell++;//подразумевается проверка на исключения
    return true;
}


bool Enter_Data::number_check(double radius, char *end_ptr)
{
    if (errno == ERANGE) //DOUBLE_MAX-?
    {
        std::cout << "ERROR when writing numbers(too long)" << std::endl;
        return false;
    }
    if(*end_ptr || radius < 0)
    {
        std::cout << "ERROR when writing numbers" << std::endl;
        return false;
    }
    return true;
}


void Enter_Data::show()
{
    std::cout << "Figures data:" << std::endl;
    for(current_ell; current_ell > 0; current_ell--) {
        volume_figure[current_ell - 1]->show_figure_data();
        delete volume_figure[current_ell - 1];                                                                           //правильно ли с очисткой памяти?
    }
    delete[] volume_figure;
    max_ell = 0;
}

