#include <iostream>
using namespace std;
int main(){
    int n,k,a=0,b,c;
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        c=i/10;
        b=i-10*c;
        if((b==k||i%k==0)&&b!=4){
            a=a+1;
           
        }
    }
    cout<<a;
}