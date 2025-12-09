#include<iostream>
using namespace std;

class one
{
public:
       virtual void f(){cout<<"1";}
};

class two:public one
{
public:
       two(int t=0){cout<<"2";}
};

class three:public two
{
public:
       virtual void f(){two::f();cout<<"3"; }
};


int main()
{
       one aa,*p;
       two bb(0);
       three cc;
    //    p=&bb;
    //    p->f();
    //    cout<<endl;
       p=&cc;
       p->f();
       return 0;
}
//生成对象时，先调用构造函数
