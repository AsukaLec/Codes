#include <iostream>
#include<cmath>
using namespace std;
int main(){
    double  x,m;
    
    cin>>x;
    m=x;
    int n=0;

    for( int k=0,t=x;t!=0;k++){
        x=x/10;
        t=int(x);
        n=k+1;

    }
    
    float sum=0;
    int a;
    m=m/pow(10,n);
    for(int i=0;i<n-1;i++){
        m=m*10;
        
        a=int(m);
      
        m=m-a;
        sum=sum+a;
        
    }
    
    m=m*10;
   
    sum=sum+m;
    cout<<sum;
}