#include <iostream>
using namespace std;
int main (){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    int m,n;
    m=a*60+b;
    n=c*60+d;
    int t;
    t=n-m;
    int h,mi;
    h=(t-(t%60))/60;
    mi=t%60;
    cout<<h<<" "<<mi;
}