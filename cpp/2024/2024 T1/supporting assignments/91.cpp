#include <iostream>
using namespace std;
int main(){
    int q,p;
    cin>>q;
    int arr1[q][3];
    int m_max=0,n_max=0;
    for(int i=0;i<q;i++){
        for(int k=0;k<3;k++){
            cin>>arr1[i][k];
            if(k==0){
                if(arr1[i][k]>m_max){
                    m_max=arr1[i][k];
                }
            }
            if(k==1){
                if(arr1[i][k]>n_max){
                    n_max=arr1[i][k];
                }
            }
        }
    }

    cin>>p;
    int arr2[p][3];
    for(int i=0;i<p;i++){
        for(int k=0;k<3;k++){
            cin>>arr2[i][k];
            if(k==0){
                if(arr2[i][k]>m_max){
                    m_max=arr2[i][k];
                }
            }
            if(k==1){
                if(arr2[i][k]>n_max){
                    n_max=arr2[i][k];
                }
            }
        }
    }

    m_max+=1;
    n_max+=1;
    if(m_max!=n_max){
        if(m_max>n_max){
            n_max=m_max;
        }
        if(m_max<n_max){
            m_max=n_max;
        }
    }

    int arr3[m_max][n_max];
    for(int i=0;i<m_max;i++){
        for(int k=0;k<n_max;k++){
            arr3[i][k]=0;
        }
    }

    int arr4[m_max][n_max];
    for(int i=0;i<m_max;i++){
        for(int k=0;k<n_max;k++){
            arr4[i][k]=0;
        }
    }

    for(int i=0;i<q;i++){
        arr3[arr1[i][0]][arr1[i][1]]=arr1[i][2];
    }
    for(int i=0;i<p;i++){
        arr4[arr2[i][0]][arr2[i][1]]=arr2[i][2];
    }
    // cout<<endl;
    // for(int i=0;i<m_max;i++){
    //     for(int k=0;k<n_max;k++){
    //         cout<<arr3[i][k]<<" ";

    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i=0;i<m_max;i++){
    //     for(int k=0;k<n_max;k++){
    //         cout<<arr4[i][k]<<" ";

    //     }
    //     cout<<endl;
    // }

    for(int i=0;i<m_max;i++){
        for(int k=0;k<n_max;k++){
            int t=0;
            for(int s=0;s<n_max;s++){
                t+=arr3[i][s]*arr4[s][k];
            }
            if(t!=0){
                cout<<i<<" "<<k<<" "<<t;
                cout<<endl;
            }
        }
        
    }


}