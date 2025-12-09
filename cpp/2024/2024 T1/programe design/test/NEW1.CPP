#include <iostream>
using namespace std;

class A{
    
    public: A(int a){cout<<"A "<<a<<endl;}
};

class B{
    public:
    B(int a){cout<<"B "<<a<<endl;}
};

class C{
    public:
    C(){cout<<"C "<<endl;}
};

class new1 : public A, public B, public C{
    public:
        new1(int a,int b, int c, int d):A(a),member1(b),member2(c),B(d){}
    
     B member2;
    A member1;
   
    C member3;
};

int main(){
    new1 aaa(1,2,3,4);
    return 0;
}