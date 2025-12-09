#include <iostream>
using namespace std;
int main (){
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    int s1,s2;
    s1=a*3600+b*60+c;
    s2=d*3600+e*60+f;
    cout<<s2-s1;
}