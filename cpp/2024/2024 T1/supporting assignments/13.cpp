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
    
    for(int i=0; i<m-1; i++){
        int max = i;
        for(int k=i+1; k<m; k++){
            if (arr2[max]<arr2[k]){
                max = k; 
            }
        }
        if (max!=i){
            swap(arr2[max],arr2[i]);
        }
    }


    int t=0;

    for(int i=0;i<m;i++){
        
        for(int k=0;k<n;k++){
            
            if(arr2[i]==arr1[k]){
                cout<<arr2[i]<<" ";
                t+=1;
                goto flag;
                
            }
        }
        flag: t+=0;
    }

    if(t==0){
        cout<<"No Answer";
    }
}