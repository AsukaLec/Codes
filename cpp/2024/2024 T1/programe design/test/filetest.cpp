#include<iostream>
using std::cout;
using namespace std;
int main(){
    int a=0;
        std::cin>>a;
    if(a<=999&&a>=100){
        if(a%100==0){
            int d;
            d=a/100;
        
            std::cout<<d<<std::endl;

        }
        else{
        int b,c,b1,a1;
        b=a%100;
        c=b%10;
        b1=(b-c)/10;
        a1=(a-b)/100;
        std::cout<<c<<b1<<a1;
        } 
    }
    else{
        std::cout<<-1<<std::endl;
    }
}
