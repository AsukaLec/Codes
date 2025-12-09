#include <cmath>
#include<iostream>
using namespace std;

int loop(int x){
    int n=0;
    int a=x;
  
    while(x/10!=0){
        n=n+1;
        x=x/10;
    }
    
    int s=0;
    x=a;
    for(int i=0;i<=n;i++){
        s=s+x%10*pow(10,n-i);
        x=x/10;
    }
    
    
    if(a==s){
        return 1;

    }
    else{
        return 0;
    }
}
int main(){
    int a,b;
    cin>>a>>b;
    for(int i=a;i<=b;i++){
        if(i%2==0&&loop(i)){
            cout<<i<<endl;
        }
    }
    
}