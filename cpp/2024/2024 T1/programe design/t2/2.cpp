#include <iostream>
#include <iomanip> 
using namespace std;


int main (){
    int i;
    cin>>i;
    
    for(int k=-1;k<i;k=k+2){
        
    int a=(i-k)/2;
    for(int t=0;t<a;t++){
        cout<<" ";
    }    
    for(int t=0;t<k;t++){
        cout<<"*";
    }
    for(int t=0;t<a;t++){
        cout<<" ";
    }    
    cout<<endl;
}
}