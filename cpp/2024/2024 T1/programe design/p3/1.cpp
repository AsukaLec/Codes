#include <iostream>
using namespace std;
int main (){
    int t;
    cin>>t;
    int a=t;
    int n=1;
    while(t/10!=0){
        t=t/10;
        n=n+1;
    }
    cout<<n<<endl;
    t=a;
    cout<<t<<endl;
    
    ;
    for(int i=0;i<n;i++){
        int s=t%10;
        t=t/10;
        cout<<s;
    }
   
}