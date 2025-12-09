#include <iostream>
using namespace std;

int main (){
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
    // int n=8,m=4;
    // int arr1[n]={5,1,4,3,8,7,9,6};
    // int arr2[m]={5,2,8,10};

    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i;j<n;j++){
            if(arr1[min]>arr1[j]){
                min=j;
            }
        }
        if(min!=i){
            swap(arr1[i],arr1[min]);
        }
    }
    for(int i=0;i<m-1;i++){
        int min=i;
        for(int j=i;j<m;j++){
            if(arr2[min]>arr2[j]){
                min=j;
            }
        }
        if(min!=i){
            swap(arr2[i],arr2[min]);
        }
    }
    
    int ans[max(n,m)];
    int h=0;
    for(int i=0;i<n;i++){
        int t=0;
        for(int k=0;k<m;k++){
            if(arr1[i]==arr2[k]){
                t+=1;
            }
        }
        if(t==0){
            ans[h]=arr1[i];
            h+=1;
        }
    }
    for(int i=0;i<m;i++){
        int t=0;
        for(int k=0;k<n;k++){
            if(arr2[i]==arr1[k]){
                t+=1;
            }
        }
        if(t==0){
            ans[h]=arr2[i];
            h+=1;
        }
    }

    for(int i=0;i<h-1;i++){
        int min=i;
        for(int j=i;j<h;j++){
            if(ans[min]>ans[j]){
                min=j;
            }
        }
        if(min!=i){
            swap(ans[i],ans[min]);
        }
    }

    for(int i=0;i<h;i++){
        cout<<ans[i]<<" ";
    }
}

    // int a,b;
    // int minimum;
    // int k=0;

    // cin>>a;
    // int arr1[a];


    // for(int i=0;i<a;i++){
    //     cin>>arr1[i];
    // }
    // cin>>b;
    // int arr2[b];

    // for(int i=0;i<b;i++){
    //     cin>>arr2[i];
    // }

    // int arr3[a+b];
    // for(int i=0;i<a;i++){
    //     arr3[i]=arr1[i];

    // }
    // for(int i=a;i<a+b;i++){
    //     arr3[i]=arr2[i-a];
    // }
    
    // //99999999

    // for(int i=0;i<a+b;i++){
        
    //     for(int n=i+1;n<a+b;n++){
    //         if(arr3[i]==arr3[n]){
    //             arr3[i]=99999999;
    //             arr3[n]=99999999;
    //         }
    //     }
    // }
   
    // for(int i=0;i<a+b;i++){
    //     minimum=arr3[i];
        
    //     for(int n=i+1;n<a+b;n++){
    //         if(arr3[n]<minimum){
    //             minimum=arr3[n];
    //             k=n;
    //         }   
    //     }
    //     if(minimum<99999999){
    //         cout<<minimum<<" ";
    //         arr3[k]=99999999;
    //     }
    // }