#include<iostream>
#include<iomanip>
#include<string>
#include<cmath>
using namespace std;

int main(){
    string input,num,a;
    getline(cin,input);
    int pos=input.find('e',0);
    num=input;
    a=input;
    num.erase(pos);
    a.erase(0,pos+1);

    float num0=stof(num);
    float a0=stof(a);

    float ans=num0*pow(10,a0);

    cout<<fixed<<setprecision(6)<<ans;
}