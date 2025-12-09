#include <iostream>
using namespace std;
int main(){
    int n,m,q;
    cin>>n>>m>>q;
    q-=1;
    int arr[n];


    for(int i=0;i<n;i++){
        arr[i]=1;
    }

    for(int i=1;i<n;i++){
        
        for(int k=1;k<m;k++){
            q+=1;
            if(q>n-1){
                q=0;
            }

            while(arr[q]==0){
                q+=1;
                if(q>n-1){
                q=0;
                }
            }
        }
        
        arr[q]=0;
        q+=1;
        
        while(arr[q]==0){
            q+=1;
            if(q>n-1){
            q=0;
            }
        }
        
        if(q>n-1){
            q=0;
        }
        
        while(arr[q]==0){
            q+=1;
            if(q>n-1){
            q=0;
            }
        }

    }
    
    for(int i=0;i<n;i++){
        if(arr[i]==1){
            cout<<i+1;
        }
    }

}

















// int main()
// {
//     int n=7,m=4,q=3;
//     //cin>>n>>m>>q;
//     int a=n;
//     int arr[n];
//     for(int i=0;i<n;i++){
//         arr[i]=i+1;
//     }
    
//     int k=0;
   
//     for(int i=1;i<n;i++){
        
//         k=q;
//         for(int t=1;t<m;t++){
            
//             k=k+1;
            
//             if(k>n)
//             k=k-n;

//             while(!arr[k-1]){
//                 k=k+1;
//                 if(k>n)
//                 k=k-n;
//             }

//         }
//         arr[k-1]=0;
//         q=k+1;
//         while(!arr[q-1]){
//                 q=q+1;
//                 if(q>n)
//                 q=q-n;
//             }

//     }
    
//     if(q>a)
//     q=q%a;
   
//     cout<<arr[q];
// }
