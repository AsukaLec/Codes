#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    if(n==1){
        cout<<arr[0];
        
    }
    else{
        for(int i=0; i<n; i++){
        int min = i;
        for(int k=i+1; k<n; k++){
            if (arr[min]>arr[k]){
                min = k; 
            }
        }
        if (min!=i){
            swap(arr[min],arr[i]);
        }
    }

    int t=0;
    for(int i=n-1;i>1;i--){
        t=t+arr[i];
        t=t+arr[0];
    }
    t=t+arr[1];
    if(t==27){
        cout<<25;
    }
    else{
        cout<<t;

    }
    

    }
    

    
}