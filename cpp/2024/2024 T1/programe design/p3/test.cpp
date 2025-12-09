#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double  fac(int n){ //求阶乘
    unsigned  f;
    if(n==0)
       f=1;
    else
       f=fac(n-1)*n;
    
    return f;

}

double  di(int n){ //dishu
    unsigned  f=1;
    int t=1;
    for(int i=1;i<=n;i++){
       f=f*t;
       t=t+2;
    }
    return f;
}

double Pi(int n){
    double s,j;
    for(int i=1;i<=n;i++){
        j=fac(i-1)/di(i);
        s=(s/2+j)*2;
    }
    return s;
}


int main (){
   double e;
   cin>>e;
   int a=2;
   cout<<Pi(1);
}