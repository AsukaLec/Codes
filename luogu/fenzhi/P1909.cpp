#include <iostream>
using namespace std;
int main(){
    int num;
    cin>>num;
    int a1,b1,a2,b2,a3,b3;
    cin>>a1>>b1>>a2>>b2>>a3>>b3;


    int ans1,ans2,ans3;

    if(num%a1==0) ans1=num/a1*b1;
    else ans1=(num/a1+1)*b1;

    if(num%a2==0) ans2=num/a2*b2;
    else ans2=(num/a2+1)*b2;

    if(num%a3==0) ans3=num/a3*b3;
    else ans3=(num/a3+1)*b3;

    int ans;

    if(ans1<ans2) ans=ans1;
    else ans=ans2;

    if(ans>ans3) ans=ans3;

    cout<<ans; 
}