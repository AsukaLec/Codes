#include <iostream>
using namespace std;
int main(){
    int m,n,a,b,c,d;
    cin>>m>>n;
    b=m-m/10*10;
    a=(m-b)/10;

    d=n-n/10*10;
    c=(n-d)/10;

    int k;
    k=b*1000+d*100+a*10+c;
    cout<<k;


}