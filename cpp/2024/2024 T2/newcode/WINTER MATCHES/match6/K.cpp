#include <bits/stdc++.h>
using namespace std;
int main (){
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        long long  now,target;
        cin>>now>>target;
        if(now%2==0){
            if(target%4==1) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
        else{
            if(target%4==3) cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
}