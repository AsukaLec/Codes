#include <iostream>
using namespace std;
int main(){
    int a;
    cin>>a;
    int arr[a][a];
    arr[0][0]=0;
    for(int i=1;i<a;i++){
        cin>>arr[0][i];
    }
    for(int i=1;i<a;i++){
        cin>>arr[i][0];
    }

    for(int t=1;t<a;t++){
        for(int k=1;k<a-t;k++){
            arr[t][k]=arr[t-1][k]+arr[t][k-1];
        }
    }
    
    for(int t=1;t<a;t++){
        for(int k=a-1;k>a-1-t;k--){
            arr[t][k]=arr[a-1-k][a-1-t];
        }
    }
    
    
    for(int t=0;t<a;t++){
        for(int k=0;k<a;k++){
            cout<<arr[t][k]<<" ";
        }
        cout<<endl;
    }

}