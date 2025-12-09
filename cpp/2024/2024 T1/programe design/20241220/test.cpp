#include <iostream>
using namespace std;

A operator -(A&,A&){

}
    class A{
        public:
            int a,b;
           friend A operator - (A&C1 ,A&C2);
    };


int main(){

    A a,b;
    cout<<a-b;


}