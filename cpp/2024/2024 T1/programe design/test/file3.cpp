#include<iostream>
using namespace std;
int main(){
    float a;
    cin>>a;
    int b;
    b=a/1;
    int c1,c2;
    c1=b;
    c2=b+1;
    float d1,d2;
    d1=a-c1;
    d2=c2-a;
    if(d1>=d2){
        cout<<c2<<endl;
    }
    else{
        cout<<c1<<endl;
    }

}