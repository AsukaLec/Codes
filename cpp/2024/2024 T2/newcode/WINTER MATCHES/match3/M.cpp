#include <iostream>
using namespace std;
int main(){
    int ans=0;
    for(int i=0;i<8;i++){
        char charc;
        cin>>charc;
        ans+=charc;
    }
    if(ans==865) cout<<"happy new year";
    else cout<<"I AK IOI";
  
}