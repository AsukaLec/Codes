#include <iostream>
using namespace std;
 int main(){
    int n,m;
    
    cin>>n;
    int arr1[n];
    for(int i=0;i<n;i++){
        cin>>arr1[i];
    }
    cin>>m;
    int arr2[m];
    for(int i=0;i<m;i++){
        cin>>arr2[i];
    }

    // int n=6,m=4;
    // int arr1[n]={2,5,8,11,20,35};
    // int arr2[m]={1,6,15,60};

    int arr[n+m];
    for(int i=0;i<n;i++){
        arr[i]=arr1[i];
    }

    for(int i=0;i<m;i++){
        arr[i+n]=arr2[i];
    }
    

    for(int i=0;i<n+m;i++){
        int mini=999999;
        int k=0;
        for(int t=0;t<n+m;t++){
            if(arr[t]<mini){
                mini=arr[t];
                k=t;
            }
        }
        cout<<arr[k]<<" ";
        arr[k]=1000000;
        
    }
 }
