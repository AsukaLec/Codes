#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    char opt;
    cin>>n>>opt;
    switch (opt)
    {
    case  '+':
        cout<<1<<" "<<n-1;
        break;
    case '-':
        cout<<n+1<<" "<<1;
        break;
    case '*':
        cout<<1<<" "<<n;
        break;
        
    default:
        break;
    }
}