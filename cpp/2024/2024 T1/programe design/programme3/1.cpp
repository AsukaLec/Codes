#include <iostream>
using namespace std;


int main (){
    int t;
    int m=0;
    int b=0;
    int e=0
    cin>>t;
    int arr[t];
    for(int i=1;i<=t;i++){
        for(int b=1;b<=i;b++){
           if(i%b==0){
            m=m+1;
           }
         }
        
        if(m==2){
        e=i;
            for(int a=1;a<=e;a++){
                if(e&a==0){
                    m=m+1;
                }
                if(m)
            }
           }
        m=m-m;
    }
    

   for(int c=0;t!=1;){
    if (arr[c]==0){
        break;
    }
    if(t%arr[c]==0){
       cout<<arr[c]<<" "; 
       t=t/arr[c];
    }
    else{
         c=c+1;
    }
    
    }
}

