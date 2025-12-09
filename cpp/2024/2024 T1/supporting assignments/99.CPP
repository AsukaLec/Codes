#include <iostream>
using namespace std;
int main(){
    int a;
    cin>>a;
    int i=0;
    int t=a;
    while(a/10!=0){
        a=a/10;
        i+=1;

    }
    int sum=0;
    for(int k=0;k<=i;k++){
        sum=sum+t-t/10*10;
        t=t/10;
    }
    cout<<sum;
}