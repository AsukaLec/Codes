#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main(){
    double x;
    int n;
    cin>>x>>n;
    double t=(-1)*x*x/2;
    if(n!=0){
    double ans=1+t;
    for(int i=1;i<n;i++){
        t *=(-1)*x*x/(2*(i+1)*(2*i+1));
        ans+=t;
    }
    cout<<fixed<<setprecision(8)<<ans;
    }
    if(n==0){
        double ans=1;
        cout<<fixed<<setprecision(8)<<ans;
    }
    
}