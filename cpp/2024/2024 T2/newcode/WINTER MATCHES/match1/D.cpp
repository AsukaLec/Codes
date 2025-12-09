#include <iostream>
#include <cmath>

using namespace std;
int main(){
    int a=0;
    cin>>a;

    for(int i=0;i<a;i++){
        int t=0;
        cin>>t;

        int a1=0,a2=0,b1=0,b2=0;
        cin>>a1;
        a2=1;
        
        int k=1;
        int p;
        cin>>p;
        
        while(p==a1){
            a2+=1;
            k+=1;
            cin>>p;
        }

        b1=p;b2=1;

        for(int b=k+1;b<=t;b++){
            int q;
            cin>>q;
            if(q==a1) a2+=1;
            if(q==b1) b2+=1;
        }

        if(t%2==0&&a2==t/2&&b2==t/2) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;




    }
}