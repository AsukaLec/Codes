#include <iostream>
using namespace std;

class base{
    public:
    virtual void f1() const{
        cout<<"base"<<endl;
    }
};

class base111 : public base{
    public:
    virtual void f1() const {
        cout<<"base111"<<endl;
    }
};

void fun(base *ptr){
    ptr->f1();
}

int main(){
    base a;
    base111 b;

    fun(&a);
    fun(&b);

}