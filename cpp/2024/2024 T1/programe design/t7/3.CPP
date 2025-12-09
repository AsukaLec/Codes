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

    int arr[n+m];
    for(int i=0;i<n;i++){
        arr[i]=arr1[i];
    }

    for(int i=0;i<m;i++){
        arr[i+n]=arr2[i];
    }
    // int n=8,m=5;
    // int arr[n+m]={5,105,4,32,8,7,9,-60,5,2,87,10,105};
    
    
    
    
    for(int i=0;i<n+m;i++){
        int k=0;
        int maxi=-999999;
        for(int t=0;t<n+m;t++){
            if(arr[t]>maxi){
                maxi=arr[t];
                k=t;
            }
        }
        
        for(int q=0;q<n+m;q++){
            if((arr[q]==maxi)&&(q!=k)){
                arr[q]=-1000000;
            }
        }
        
        if(arr[k]!=-1000000){
            cout<<arr[k]<<" ";
   
        }
        
        arr[k]=-1000000;

    }
}

  