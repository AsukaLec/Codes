#include <iostream>
using namespace std;
int main (){
    int a,b,d;
    cin>>a>>b;
    d=10*a+b;
    int s=(d-d%19)/19;
    cout<<s;
}