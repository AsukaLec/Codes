#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;
double fac(int n){ //求阶乘
    unsigned long long f;
    if(n==0)
       f=1;
    else
       f=fac(n-1)*n;
       return f;

}

int main (){
    int n;
    cin>>n;
    cout<<fac(n);

}