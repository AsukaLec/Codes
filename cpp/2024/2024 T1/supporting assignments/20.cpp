#include<iostream>
using namespace std;
int main(){
    int n, m;
    cin>>n>>m;
    int arr0[n][m];
    for(int i=0;i<n;i++){
        for(int k=0; k<m;k++){
            cin>>arr0[i][k];
        }
    }

    for(int i=0;i<n;i++){
        for(int k=0;k<m;k++){
            int max1=-999999;
            for(int q=0;q<m;q++){
                if(arr0[i][q]>=max1){
                    max1=arr0[i][q];
                }
            }
            int max2=-999999;
            if(arr0[i][k]==max1){
                for(int p=0;p<n;p++){
                    if(arr0[p][k]>=max2){
                        max2=arr0[p][k];
                    }
                }
            }
            if(arr0[i][k]==max2){
                cout<<arr0[i][k]<<" "<<i+1<<" "<<k+1<<endl;
            }
        }
    }
}

        // int max=-9999999;
        // int max_pos=0;
        // for(int k=0;k<m;k++){
        //     if(arr0[i][k]>=max){
        //         max=arr0[i][k];
        //         max_pos=k;
        //     }
        // }
        // int max0=-999999;
        // int max_pos0=0;
        // for(int t=0;t<n;t++){
        //     if(arr0[t][max_pos]>=max0){
        //         max0=arr0[t][max_pos];
        //         max_pos0=t;
        //     }
        // }
        // if(max_pos0==i){
        //     cout<<arr0[max_pos0][max_pos]<<" "<<max_pos0+1<<" "<<max_pos+1<<endl;
        // }