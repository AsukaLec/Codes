#include <iostream>
#include <cmath>
using namespace std;
int main (){
    int i;
    int a;
    cin>>a;
    int b=0;
    for(i=1;i<447;i++){
        if(a==(pow(i,2)+i)/2){
            cout<<i;
            b=b+1;
        }
        else{
            b=b;

        }
    }
    if(b==0){
        cout<<-1;
    }
}