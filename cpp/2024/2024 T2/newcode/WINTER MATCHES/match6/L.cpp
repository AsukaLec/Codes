#include <bits/stdc++.h>
using namespace std;

int main (){
    int times;
    cin>>times;
    string target="CHICKEN";
    for(int i=0;i<times;i++){
        int length;
        cin>>length;
        string s;
        cin>>s;

        

        if(length<7) cout<<"NO"<<endl;
        if(length==7) {
            if(s==target) cout<<"YES"<<endl;
            else {
                cout<<"NO"<<endl;
            }
        }

        if(length>7){
            if(length%2==0) {
                cout<<"NO"<<endl;;
            }
            else{
                
                string ans="1";

                int t=0;
                int p=s.size();
                while (s[t]!='C'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='C'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='H'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='H'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='I'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='I'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='C'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='C'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='K'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='K'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='E'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='E'){
                    ans += s[t];
                    s.erase(t,1);
                }
                t=0;
                p=s.size();

                while (s[t]!='N'&&t<p-1){
                    t+=1;
                }
                if(s[t]=='N'){
                    ans += s[t];
                    s.erase(t,1);
                }
                ans.erase(0,1);
                sort(s.begin(),s.end());
                // cout<<ans<<" "<<s<<endl;




                if(ans!=target) cout<<"NO"<<endl;
                else{
                    
                    int ssize=s.size();
                    string s0="0";
                    for(int i=1;i<ssize;i++){
                        s0+='0';
                    }
                    
                    

                    for(int m=0;m<ssize/2;m++){
                        for(int n=ssize/2;n<ssize;n++){
                            if(s[m]!='0'){
                                if(s[m]!=s[n]&&s[n]!='0'){
                                    s[m]='0';
                                    s[n]='0';
                                    continue;
                                }
                            }
                            else continue;
                        }
                    }

                    //  cout<<s<<" "<<s0<<endl;
                    if(s==s0) cout<<"YES"<<endl;
                    else cout<<"NO"<<endl;
                }

            }
        }
    }
}