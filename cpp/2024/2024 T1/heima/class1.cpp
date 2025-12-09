#include<iostream>
using namespace std;

const double pi= 3.14;

class circle{
        public:
           //属性
           int r;
        
        //行为
        double calculate(){
            return 2*pi*r;
        }
    };


int main(){
   
    circle c1,c2;
    
    int t,p;
    cin>>t>>p;
    
    c1.r=t;
    c2.r=p;
    cout<<c1.calculate()<<endl;
    cout<<c2.calculate()<<endl;

}