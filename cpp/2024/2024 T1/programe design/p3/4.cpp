#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;



double Pi(int n){
    double s,j;
    s=0.0;
    j=1.0;
    if(n==1){
        s=s+1;
    }
    else{
        s=2;
        for(int i=2;i<=n;i++){
            j=j*(i-1)/(2*i-1);
            s=2*(s/2+j);
        }
    }
    return s;
}


int main (){
   
   double e;
   cin>>e;
   
   int c;
   c=2;
   double j=Pi(c)-Pi(c-1);
   while(j>e){
    c=c+1;
    j=Pi(c)-Pi(c-1);
    }
   
   cout<<c<<" ";
   cout<<setiosflags(ios::fixed);
   cout<<setprecision(7)<<Pi(c);
}