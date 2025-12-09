#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int n0=n;
    int x=2;
    while(x<=n0){
        while(n%x==0){
            n /= x;
            cout<<x<<" ";
        }
        x+=1;
    }
    
}