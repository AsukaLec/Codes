#include<iostream>
using namespace std;
int main(){
    int m1,m2,n1,n2;
    cin>>m1>>n1;
    int arr1[m1][n1];
    for(int i=0;i<m1;i++){
        for(int k=0;k<n1;k++){
            cin>>arr1[i][k];
        }
    }
    cin>>m2>>n2;
    int arr2[m2][n2];
    for(int i=0;i<m2;i++){
        for(int k=0;k<n2;k++){
            cin>>arr2[i][k];
        }
    }

    cout<<arr1[m1/2][n1/2]<<endl;

    if(n1==m2){
        for(int i=0;i<m1;i++){
            for(int k=0;k<n2;k++){
                int t=0;
                for(int s=0;s<n1;s++){
                    t+=arr1[i][s]*arr2[s][k];
                }
                cout<<t<<" ";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"ERROR!"<<endl;
    }

    if((m1==m2)&&(n1==n2)){
        for(int i=0;i<m1;i++){
            for(int k=0;k<n1;k++){
                cout<<arr1[i][k]+arr2[i][k]<<" ";
            }
            cout<<endl;
        }
    }
    else{
        cout<<"ERROR!"<<endl;
    }

    for(int i=0;i<m2-1;i++){
        for(int k=0;k<n2;k++){
            cout<<arr2[i][k]<<" ";
        }
        cout<<endl;
    }
    for(int k=0;k<n2;k++){
        cout<<arr2[m2-1][k]<<" ";
    }
}