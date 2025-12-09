#include <bits/stdc++.h>
using namespace std;
int main(){
    // int n=5,m=6;
    // int ans0 = n & m;
    // int ans1 = n ^ m;
    // int ans2 = n | m ;
    // cout<<ans0<<" "<<ans1<<" "<<ans2;
    int times;
    cin>>times;
    for(int i=0;i<times;i++){
        int a,b;
        cin>>a>>b;
        int k=0;
        for(int i=a;i<=b;i++){
            for(int p=i;p<=b;p++){
                if(i+p==(i&p)+(i^p)+(i|p)) k+=1;
            }
        }
        cout<<k<<endl;
    }
}