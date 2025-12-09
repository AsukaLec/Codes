#include<iostream>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    int x=2;
    int n0=n;
    while(x<=n0){
        while((n%x==0)&&(m%x==0)){
            n /=x;
            m /=x;
        }
        x+=1;
    }
    cout<<n<<" "<<m;
}