#include <iostream>
using namespace std;

int sum(int n){
    int s=0;
    for(int k=1;k<n;k++){
        if(n%k==0){
        s=s+k;
        }
    }
    return s;
}




int main(){
    int a,b;
    cin>>a>>b;
  
    int t=0;

    int c=0,d=0;
    
   

    for(int i=a;i<b;i++){
        c=sum(i);
        d=sum(c);
        
        
        if(d==i&&c>i){
            cout<<i<<" " <<c<<endl;
            t=t+1;

        }
    } 
    if(t==0){
        cout<<"NONE";
    }

    
}