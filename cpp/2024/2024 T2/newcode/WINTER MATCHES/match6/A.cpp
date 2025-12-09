#include <bits/stdc++.h>
using namespace std;
int main (){
    int k;
    cin>>k;
    for(int i=0;i<k;i++){
        int length;
        cin>>length;
        int arr[length];
        for(int p=0;p<length;p++){
            cin>>arr[p];
        }
        int ans=1;
        for(int q=1;q<length;q++){
            if(arr[q]!=arr[q-1]) ans+=1;
        }
        cout<<ans<<endl;
    }
}