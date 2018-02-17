#include <iostream>

using namespace std;

static int x = 1;

class A{
public:
    int x;
    A(int val){x = val; ::x = 2;}
    void foo(){cout << "this->x = " << this->x << "; x = " << ::x << endl;}

};

class S {
public:
    int i;
    S(int a){i=a; cout<<"CONS"<<endl;}
    S(const S &ob){this->i = ob.i;cout<<"COPY"<<endl;}
};

void foo(S cpob){
    S ob2(3);
    cpob = ob2;
    cout<<"foo"<<endl;
}

int main() {

    A ob(10);
    ob.foo();
    S ob1(1);
    foo(ob1);
    return 0;
}