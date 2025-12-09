#include<iostream>
using namespace std;
int main(){
    int m,t,s;
    cin>>m>>t>>s;
    if(t==0){
        cout<<0;
    }
    
    
    else{
        if(s<m*t&&s%t==0)
            cout<<m-s/t;
    
        if(s>=m*t)
            cout<<0;
        if(s<m*t&&s%t!=0)
            cout<<m-s/t-1;
    }    
    
            
}