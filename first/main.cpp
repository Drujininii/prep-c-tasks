#include <iostream>
#include "library.h"
#include <fstream>
#include <cstdlib>

using namespace list;
static dynamic_list *bufer_work(const char *, dynamic_list *);
static char *read(char **, char *);
static dynamic_list *print(dynamic_list *, char **);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "нет имени файла" << '\n';
        return -1;
    }
    char *buf = new char[255];
    buf = read(argv, buf);
    if(buf == NULL)
        return -1;
    dynamic_list *ob = new dynamic_list;
    ob = bufer_work(buf, ob);
    ob = print(ob, argv);
    if(ob == NULL){
        delete ob;
        delete buf;
        return -1;
    }
    delete buf;
    delete ob;
    return 0;
}

static dynamic_list *bufer_work(const char *bufer, dynamic_list *ob)
{
    int i = 0;
    char c;
    while (*(bufer + i) != '\0') {
        double valu;
        c = *(bufer + i);
        if (((c >= '0' && c <= '9') || c == '-') && (*(bufer + i - 1) == ' ' || i == 0)) { //преобразование в дабл, если найдено начало числа
            valu = atof(bufer + i);
            ob->add_element(valu);
            i++;
            continue;
        }
        if (c == ' ') { //пропуск пробелов
            i++;
            continue;
        }
        i++;
    }
    return ob;
}

static char *read(char *argv[], char *buf)
{
    std::ifstream fin;
    fin.open(argv[1]);
    if (!fin.is_open()) {// если файл не открыт
        std::cout << "Файл для чтения не может быть открыт!\n";
        delete buf;
        return NULL;
    }
    fin.getline(buf, 255);
    fin >> buf;
    if(!fin.eof()) {
        std::cout << "слишком большой файл" << '\n';
        fin.close();
        delete buf;
        return NULL;
    }
    std::cout << "буфер" << buf << '\n';
    fin.close();
    return buf;
}

static dynamic_list *print(dynamic_list *ob, char *argv[])
{
    std::ofstream fout;
    fout.open(argv[2], std::ios_base::out | std::ios_base::trunc);
    if (!fout.is_open()) {// если файл не открыт
        std::cout << "Файл для записи не может быть открыт!\n";
        return NULL;
    }
    for (size_t i = (ob->get_size()); i > 0; i--){
        fout << ob->get_element(i) << ' ';
    }
    fout.close();
    return ob;
}