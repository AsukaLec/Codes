#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        int total;
        cin>>total;
        int a,b,c;
        cin>>a>>b>>c;
        if(total<=a+b+c&&2*total>=a+b+c) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
}