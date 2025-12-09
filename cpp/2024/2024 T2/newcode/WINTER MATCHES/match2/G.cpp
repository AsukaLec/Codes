#include <bits/stdc++.h>
using namespace std;
int main(){
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        long long  tgt,now;
        cin>>tgt>>now;
        int ans =1;
        long long t=now;
        
        if(now==1) cout<<1<<endl;
        else{
            while(now<tgt){
            ans+=1;
            now*=t;
        }
        if((now-tgt)>=tgt-(now/t)) cout<<ans-1<<endl;
        else cout<<ans<<endl;
        }
        
        
    }
}