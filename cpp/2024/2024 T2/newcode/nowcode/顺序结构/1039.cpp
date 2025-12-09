#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    int n;
    cin>>n;
    float s=pow(n,1.0/3);
    s*=3;
    cout<<fixed<<setprecision(3)<<s;
    return 0;
}