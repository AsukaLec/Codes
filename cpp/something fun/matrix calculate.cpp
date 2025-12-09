#include <iostream>
#include <algorithm>
using namespace std;
// 最大公约数函数定义
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 最小公因数函数定义
int lcm(int a, int b) {
    return abs(a * b) / gcd(a, b);
}   


// void mswap(int* arr,int n,int i,int j){
    // for(int k=0;k<n;k++){
    //     int t=arr[i][k];
    //     arr[i][k]=arr[j][k];
    //     arr[j][k]=t;
    // }
// }

// void mplus(int* arr,int n,int i,int j,int k){
//     for(int q=0;q<n;q++){
//         arr[k][q]=k/arr[k][i]*arr[k][q]-k/arr[i][i]*arr[i][q];
//     }
// }

// void mdiv(int* arr,int i,int n,float k){
//     for(int i=0;i<n;i++){
//         arr[m][n]=arr[m][n]/k;
//     }
// }



int main(){
    int m,n;
    cin>>m>>n;
    float arr[m][n];
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>arr[i][j];
        }
    }

    while(arr[0][0]==0){
        int i=1;
        if(arr[i][0]!=0){
            for(int k=0;k<n;k++){
                int t=arr[0][k];
                arr[0][k]=arr[i][k];
                arr[i][k]=t;
            }
        }
        else{
            i+=1;
        }
    }//初始化矩阵

    for(int i=0;i<m-1;i++){
        
        for(int k=i+1;k<m;k++){
            if(arr[k][i]!=0){
                
                int t=lcm(arr[i][i],arr[k][i]);
            
                for(int q=0;q<n;q++){
                    arr[k][q]=(t/arr[k][i])*arr[k][q]-(t/arr[i][i])*arr[i][q];
                }

            }
            
            
        }
    }
    
    // for(int i=0;i<m;i++){
    //     if(arr[i][i]!=1){
    //         int q=arr[i][i];
    //         mdiv(arr,i,n,q);
    //     }
    // }
    
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
}