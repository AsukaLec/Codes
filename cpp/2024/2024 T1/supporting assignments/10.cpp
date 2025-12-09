#include <iostream>
#include <iomanip>
#include <cstdio>


using namespace std;
int main(){
   double m,n;
   cin>>m>>n;
   double s,h;
   s=m;
   h=m;
   for(int i=1;i<n;i++){
    h=h/4;
    s+=h*2;
   }
   h=h/4;
   
   h=h*1000;
   int a=h-int(h)/10*10;
   
   if(a>=5){
    h=int(h)/10*10;
    h+=10;
    h=h/1000;

   }
   else{
    h=h/1000;
   }
   
   
   
   
   
   printf("%.2f\n", s);
   

   printf("%.2f\n", h);


}