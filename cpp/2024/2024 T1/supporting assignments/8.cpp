#include <iostream>
#include <iomanip>

using namespace std;
int main(){
   int x,n;
   cin>>x>>n;
   float sum=0;
   float k=x;
   for(int i=0;i<n;i++){
       sum=((2*k+x/(k*k))/3);
       k=sum;
   }
   
   
   
   cout<<setiosflags(ios::fixed);
   cout<<setprecision(5)<<sum;
}