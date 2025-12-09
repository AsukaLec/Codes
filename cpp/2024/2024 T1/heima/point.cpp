#include <iostream>
using namespace std;
int main(){
    int a=10;
    int *p;
    p=&a;
    cout<<&a<<endl;
    cout<<*p<<" "<<p<<endl;
    int **p1=&p;
    cout<<p1<<" "<<&p;
}