#include <iostream>
using namespace std;
int main(){
    int sum=0;
    int n;
    cin>>n;
    int t=n;
    for(int i=1;i<=n;i++,t-- ){
        sum=sum+i*t;
    }
    cout<<sum;
}