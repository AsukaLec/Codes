#include <iostream>
using namespace std;
int main (){
    float Pi=3.14;
    float h,r;
    cin>>h>>r;
    float v;
    v=h*Pi*r*r;
    float n;
    n=20000/v;
    if(n-(int)n==0){
        cout<<n;
    }
    else{
        cout<<int(n)+1;
    }
}