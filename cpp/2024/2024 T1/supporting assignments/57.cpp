#include <iostream>
using namespace std;
int main(){
    char a0;
    cin>>a0;
    switch (a0)
    {
    case('a'):
    cout<<"z"; 
        break;
    case('b'):
    cout<<"x"; 
        break;
    case('c'):
    cout<<"y"; 
        break;
    case('x'):
    cout<<"b"; 
        break;
    case('y'):
    cout<<"c"; 
        break;
    case('z'):
    cout<<"a"; 
        break;
    
    default:
        break;
    }
}