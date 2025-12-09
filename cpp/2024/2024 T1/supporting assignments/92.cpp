#include <iostream>
#include <cmath>

using namespace std;
int main(){
    double pi,pi0;
    int n=2;
    pi0=4.0;
    pi=pi0+4*(-1)/(2*n-1);
    double e;
   cin>>e;
    while((abs(pi-pi0)>e)){
        n+=1;
        double t=pi;
        pi=pi+pow(-1,n-1)*4/(2*n-1);
        pi0=t;
    }
    cout<<n;


}