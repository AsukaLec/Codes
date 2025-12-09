#include <bits/stdc++.h>
using namespace std;
int main(){
    long long ans=0;
    int times;
    cin>>times;
    int v=0;

    while(times--){
        char opt;
        cin>>opt;
        switch (opt)
        {
        case '0':
            v += 10;
            ans += v;
            break;
        
        case '1':
            if(v>5){
                v -= 5;
                ans += v;
            }
            else v=0;
            break;
        
        case '2':
            if(v>=10){
                v -= 10;
                ans += v;
                v += 10;
            }
            
            break;

        default:
            break;
        }
    }
    cout<<ans;
}