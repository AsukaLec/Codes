#include <iostream>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    

    int arr1[n][m];
    for(int i=0;i<n;i++){
        for(int t=0;t<m;t++){
            cin>>arr1[i][t];
        }
    }
    
    cout<<m<<" "<<n<<endl;
    
    int arr2[m][n];
    for(int k=0;k<n;k++){
        for(int t=0;t<m;t++){
            arr2[t][k]=arr1[n-1-k][t];
        }
    }
    
    if(n==1){
        for(int i=0;i<m-1;i++){
            cout<<arr2[i][0]<<endl;
            }
        cout<<arr2[m-1][0];
    
    }
    else{
        for(int t=0;t<m-1;t++){
            cout<<arr2[t][0];
            for(int k=1;k<n;k++){
                cout<<" "<<arr2[t][k];
            }
            cout<<endl;
        }
        cout<<arr2[m-1][0];
            for(int k=1;k<n;k++){
                cout<<" "<<arr2[m-1][k];
            }
        

    }
}