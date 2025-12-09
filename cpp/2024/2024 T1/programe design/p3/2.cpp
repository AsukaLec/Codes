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
    double x;
    int n;
    cin>>x>>n;
    double s=0;
    double a;
   
    for(int i=1;i<n+1;i++){
        
        if(i==1){
            s=s+1;
        }
        if(i!=1){
            s=s+pow(x,i)/fac(i);
        }
        cout<<s<<endl;
    }
    cout<<setiosflags(ios::fixed);
    cout<<setprecision(6)<<s;//输出6位小数
}