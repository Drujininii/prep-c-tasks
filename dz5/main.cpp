#include <iostream>
#include "Worker.h"

#define ERROR_CONSTRUCTOR -1
#define ERROR_SET -2
#define ERROR_GET -3
extern int errnum;

void f(Int a);

int main() {
    int* asd = new int;
//    raw pionter
    auto i = 42;
    class Workers wr;

    if(errnum != 0)
        return ERROR_CONSTRUCTOR ;

    wr.set_worker();
    if(errnum != 0)
        return ERROR_SET;

    int num = 0;
    std::cout << "Номер работника для печати" << std::endl;
    std::cin >> num;

    wr.get_worker(num);
    if(errnum != 0)
        return ERROR_GET;
    std::cout << wr.get_worker(num);

    wr.get_more_year();
    wr.get_more_salary();
    wr.get_list_position();
    return 0;
}