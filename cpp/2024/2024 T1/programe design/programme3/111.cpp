#include <iostream>
using namespace std;
int main (){
    int t=0;
    cin>>t;
    for(int i=2;i<t;){
        if(t%i==0){
            cout<<i<<" ";
            t=t/i;
        }
        
    }
}