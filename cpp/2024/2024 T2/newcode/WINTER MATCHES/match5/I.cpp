#include <bits/stdc++.h>
using namespace std;
int main(){
    int times;
    cin>>times;
    while(times--){
        long long n,m;
        cin>>n>>m;
        int t=0;
        for(int i=0;i<100;i++){
            if(m%2==0) m/=2;
            else m*=m;

            if(m==n){
                t+=1;
            }
        }
        if(t!=0) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    
}