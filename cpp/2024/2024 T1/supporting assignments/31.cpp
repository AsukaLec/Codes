#include <iostream>
#include <string>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    
    
    if((n>=m)||(n<0)||(m<0)){
        cout<<"error";
    }
    
    else{
        int t=0;
        int ans[m];

        for(int i=n;i<=m;i++){
            string str=to_string(i);
            int str_len=str.size();
            int x=i,y=0;
            for(int k=0;k<str_len;k++){
                int d= str[k]-'0';
                y+=d*d*d;
            }

            if(x==y){
                ans[t]=i;
                t+=1;
            }
        }

        if(t==0) cout<<"no";
        
        else{
            for(int i=0;i<t-1;i++){
                cout<<ans[i]<<endl;
            }
            cout<<ans[t-1];
        }
        }
    
}