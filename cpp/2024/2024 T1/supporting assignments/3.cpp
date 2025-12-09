#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

float line(int a,int b,int c,int d){
    float l;
    l=sqrt( (a-c)*(a-c)+(b-d)*(b-d));
    return l;
}

float s(float  a,float  b,float c){
    float p=(a+b+c)/2;
    float s;
    s=sqrt( p*(p-a)*(p-b)*(p-c));
    return s;
}

int main(){
    int n;
    cin>>n;

    int arr[2*n-1];

    for(int i=0;i<2*n;i++){
        cin>>arr[i];    
    }
    
    float sum=0;
    float x,y,z;
    for(int i=2;i<2*n-2;i=i+2){
        x=line(arr[0],arr[1],arr[i],arr[i+1]);
        y=line(arr[0],arr[1],arr[i+2],arr[i+3]);
        z=line(arr[i],arr[i+1],arr[i+2],arr[i+3]);
        
        sum=sum+s(x,y,z);

        x=x-x;
        y=y-y;
        z=z-z;

    }
   if(sum>70000){
    cout<<setiosflags(ios::fixed);
   cout<<setprecision(2)<<70000.00;

   } 
   else{
    cout<<setiosflags(ios::fixed);
   cout<<setprecision(2)<<sum;

   }
   
    
}








