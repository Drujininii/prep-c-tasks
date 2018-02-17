#include <iostream>
#include <fstream>
#include "Field.h"
#include "test_txt.h"

using namespace std;

int main(int argc, char* argv[])
    {
        if (argc != 2) {
            std::cerr << "usage: " << argv[0] << " labyrinth.txt" << std::endl;
            return 1;
        }
        ifstream file;
        file.exceptions(ifstream::failbit | ifstream::badbit);

        try {
            Field field;
            int i = 0;
            if(!i)
                i++;
            cout << i << endl;
            file.open(argv[1]);
            file >> field;
            int n = 3;

            field.alg(field.final_position.i, field.final_position.j, n);
            field.return_dir();
//            field.print();
//            test_txt test1;
//            test1.read();
//            test1.print();
        }
        catch(...){
            cout << "error" << endl;
            return -1;
        }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}