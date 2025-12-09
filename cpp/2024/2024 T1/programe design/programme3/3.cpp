#include <iostream>
#include <iomanip> 
using namespace std;


int main (){
    int i;
    cin>>i;
    
    for(int k=1;k<i+2;k=k+2){
        
    int a=(i-k)/2;
     
    for(int t=0;t<k;++t){
        cout<<"*";
    }
  
    cout<<endl;
    }
}