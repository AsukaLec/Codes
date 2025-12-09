#include <bits/stdc++.h>
using namespace std;
int main(){
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        int n,t,k;
        cin>>n>>t>>k;
        int ans=0;

        ans = n/(t+1);
        if(ans>k) cout<<k+1<<endl;
        else cout<<ans<<endl;
    }
}