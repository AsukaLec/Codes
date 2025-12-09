#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;



int main (){
    int a,b;
    cin>>a>>b;
    
    int s1=1;
    cout<<a<<","<<1;
    for(int i=2;i<a;i++){
        if(a%i==0){
            cout<<"+"<<i;
            s1=s1+i;
        }
    }
    cout<<"="<<s1<<endl;

    int s2=1;
    cout<<b<<","<<1;
    for(int i=2;i<b;i++){
        if(b%i==0){
            cout<<"+"<<i;
            s2=s2+i;
        }
    }
    cout<<"="<<s2<<endl;

    if(s1==b&&s2==a){
        cout<<1;

    }
    else{
        cout<<0;
    }
}