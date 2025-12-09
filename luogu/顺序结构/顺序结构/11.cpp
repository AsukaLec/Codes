#include <iostream>
#include <iomanip>
using namespace std;
int main (){
    float s,v,t;
    cin>>s>>v;
    t=s/v;
    t=t+10;
    int h;
    float m;

    h=t/60;
    m=t-60*h;


    if(t<=480){
    
       cout<<setfill('0')<<setw(2)<<7-h<<":";
       cout<<setiosflags(ios::fixed);
       cout<<setfill('0')<<setw(2)<<setprecision(0)<<59-m;
    }
    else{
        cout<<setfill('0')<<setw(2)<<31-h<<":";
        cout<<setiosflags(ios::fixed);
        cout<<setfill('0')<<setw(2)<<setprecision(0)<<59-m;
    }
}