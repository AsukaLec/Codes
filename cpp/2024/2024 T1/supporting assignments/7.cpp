#include <iostream>
#include <cmath>
using namespace std;

int tonggou(int i){
    int t=i*i;
    int a=i;
    int n=0;
    while(a!=0){
        a=a/10;
        n+=1;
    }
    int k=t;
    for(int i=1;i<=n;i++){
        k=k/10;
    }
    for(int i=1;i<=n;i++){
        k=k*10;
    }

    if(k+i==t){
        return 1;
    }
   
    else{
        return 0;
    }
}


int main(){
    int m,n;
    cin>>m>>n;
    for(int i=m;i<=n;i++){
        if(tonggou(i)==1){
            cout<<i<<endl;
        }
    }
}






// int weishu(int a){
//     int n=1;
//     while(a/10!=0){
//         n=n+1;
//     }
//     return n;                                                                                                                            xx,x,x,x ,,mcxxcmxcccm,cmcmc                                                                       
// }


// int main(){
//     int a,b;
//     cin>>a>>b;
//     int power=0;
//     int c=0;
//     int d=0;
//     int k;
    
//     if(a==0){
//         cout<<"0"<<endl;
//         for (int i=a+1;i<=b;i++){
//         power=i*i;
//         c=weishu(i);
        
//         k=power/pow(10,c);
//         d=power-k*pow(10,c);
//         if(d==i){
//             cout<<i<<endl;
//         }
        
//        }

//     }
//     else{
//         for (int i=a;i<=b;i++){
//         power=i*i;
//         c=weishu(i);
//         k=power/pow(10,c);
//         d=power-k*pow(10,c);
//         if(d==i){
//             cout<<i<<endl;
//         }
        
//        }

//     }
    
// }