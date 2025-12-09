#include <iostream>
#include <cmath>
using namespace std;
int main() {
    float a,b,c;
    cin>>a>>b>>c;
    float maxnum,minnum;
    if(a>b){
        maxnum=a;
        minnum=b;
    }
    else{
        maxnum=b;
        minnum=a;

    }

    if(maxnum<c){
       maxnum=c;
    }
    if(minnum>c){
        minnum=c;
    }

    float midnum=a+b+c-maxnum-minnum;

    if(midnum+minnum>maxnum &&maxnum-minnum<midnum ){
        if(pow(midnum,2)+pow(minnum,2)==pow(maxnum,2)){
            cout<<1;
        }
        else{
            cout<<0;
        }
    }
    else{
        cout<<-1;
    }


    return 0;
}