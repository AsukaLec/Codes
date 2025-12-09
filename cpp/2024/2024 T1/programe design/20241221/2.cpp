#include <iostream>
using namespace std;
int main(){
    int m;
    cin>>m;

    int arr[m+1];
    for(int i=0;i<m;i++){
        cin>>arr[i];
    }
    arr[m]=m+1;
    
    // int m=4;
    // int arr[m+1]={1,4,3,2,5};

    int arr1[m+1];
    arr1[m]=m+1;
    int a=0,b=0;
    
    for(int i=0;i<m;i++){
        if(arr[i]>arr[i+1]){
            b+=1;
        }
        else{
            int t1=a;
            int t2=b;
            for(int k=1;k<=b-a+1;k++){
                
                arr1[t1]=arr[t2];
                t1+=1;
                t2-=1;
            }
            b+=1;
            a=b;
        }

    }
    
    int t=0;
    for(int i=0;i<m;i++){
        if(arr1[i]>arr1[i+1]){
            t+=1;
        }
    }
    if(t==0){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl; 
    }
}