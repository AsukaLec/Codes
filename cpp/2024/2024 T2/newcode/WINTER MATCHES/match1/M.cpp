#include <iostream>
#include <cmath>

using namespace std;
int main(){
    int a;
    cin>>a;
    int arr[a];
    for(int i=0;i<a;i++){
        cin>>arr[i];
    }
    int t=0, maxi=arr[0];
    for(int i=1;i<a;i++){
        if(maxi<arr[i]){
            t=i;
            maxi=arr[i];
        }
    }





    for(int i=0;i<a;i++){
        arr[i]*=2;
    }
    arr[t]/=2;

    if(t+1==a){
        int ans[a];
        for(int i=0;i<t;i++){
            ans[i]=abs(maxi-arr[i]);
        }

        int max0=ans[0];
        for(int i=1;i<t;i++){
            if(max0<ans[i]){
                max0=ans[i];
            }
        }
        cout<<max0;
    }
    else{
        int ans1[t],ans2[a-1-t],max0,max1,max2;
        for(int i=0;i<t;i++){
            ans1[i]=abs(maxi-arr[i]);
        }
        max1=ans1[0];
        for(int i=1;i<t;i++){
            if(max1<ans1[i]){
                max1=ans1[i];
            }
        }


        for(int i=t+1;i<a;i++){
            ans2[i-t-1]=abs(maxi-arr[i]);
        }
        max2=ans2[0];
        for(int i=0;i<a-1-t;i++){
            if(max2>ans2[i]){
                max2=ans2[i];
            }
        }

        max0=min(max1,max2);
        cout<<max0;
    }



}