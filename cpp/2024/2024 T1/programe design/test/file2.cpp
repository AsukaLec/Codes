#include<iostream>
using namespace std;
int main()
{
    int a=0;
      cin>>a;
    if (a>99|a<1000);
    {
        int b,c,b1,a1;
        b=a%100;
        c=b%10;
        b1=(b-c)/10;
        a1=(a-b)/100;
        cout<<c<<b1<<a1;
    }
    else    
    {
        cout<<-1<<endl;
    }
    

    
    
       
  
}