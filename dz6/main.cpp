
#include "Enter_Data.h"

extern short int err_code;

int main() {
    Enter_Data data;//можно же без нью?

    data.add_data();
    if (err_code)
        return err_code;

    data.show();

    return 0;
}