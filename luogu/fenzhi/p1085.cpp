#include <iostream>
using namespace std;
int main(){
    int n,m;
    int ans[7][2];
    int total=0;

    for(int i=0;i<7;i++){
        cin>>n>>m;
        if(n+m<=8){
            ans[i][0]=0;
            total+=1;
        }
        else ans[i][0]=n+m-8;

        ans[i][1]=i+1;
    }

    for(int i=0;i<6;i++){
        int max=ans[i][0];
        for(int k=i;k<7;k++){
            if(max<ans[k][0]){
                max=ans[k][0];
            }
            if(max!=ans[i][0]){
                swap(ans[i][0],ans[k][0]);
                swap(ans[i][1],ans[k][1]);
            }
        }
    }

    if(total==7){
        cout<<0;
    }
    else
    cout<<ans[0][1];
}