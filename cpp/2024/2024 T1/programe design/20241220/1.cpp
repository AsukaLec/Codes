#include <iostream>
using namespace std;
int main(){
    int ans[252]={0};
    int arr1[252]={0};
    int arr2[252]={0};

    for(int i=1;i<252;i+=2){
        arr1[i]=(i+1)/2-1;
        arr2[i]=(i+1)/2-1;
        ans[i]=(i+1)/2-1;
    }
    int n,m;
    cin>>n;
    for(int i=0;i<n;i++){
        int q,p;
        cin>>q>>p;
        arr1[2*p]=q;
    }
    cin>>m;
    for(int i=0;i<m;i++){
        int q,p;
        cin>>q>>p;
        arr2[2*p]=q;
    }


    for(int i=1;i<252;i+=2){
        for(int k=1;k<252;k+=2){
            ans[((arr1[i]+arr2[k])*2)]+=arr1[i-1]*arr2[k-1];
        }
    }

    for(int i=250;i>=0;i-=2){
        if(ans[i]!=0){
            cout<<ans[i]<<" "<<ans[i+1]<<" ";
        }
    }
    cout<<endl;

    // for(int i=0;i<102;i++){
    //     cout<<arr1[i]<<" ";
    // }
    // cout<<endl;
    // for(int i=0;i<102;i++){
    //     cout<<arr2[i]<<" ";
    // }
}