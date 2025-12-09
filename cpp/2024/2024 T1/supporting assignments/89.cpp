#include <iostream>
using namespace std;
int main(){
    int m;
    cin>>m;
    m=m*m*m;

    float a,b,n,s;
    a=1;b=3;
    n=((b-a)/2)+1;
    s=(a+b)*n/2;

    flag:while(s!=m){
        if(s<m){
            b+=2;
            n=((b-a)/2)+1;
            s=(a+b)*n/2;
            goto flag;
        }

        if(s>m){
            a+=2;
            b=a+2;
            n=((b-a)/2)+1;
            s=(a+b)*n/2;
            goto flag;
        }
    }
    cout<<a<<" "<<n;
}