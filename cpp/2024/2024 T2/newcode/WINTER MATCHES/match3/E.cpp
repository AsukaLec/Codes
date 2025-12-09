#include <iostream>
#include <iomanip>
using namespace std;
int  judge(double (*arr)[2],int n){
    int k=0;
    for(int i=0;i<n-1;i++){
        int p;
        p=arr[i+1][1]-arr[i][1];
        if(p==-2) k+=1;
    }
    if(k!=0) return 1;
    else return 0;
}


int main(){
    int n,k0;
    cin>>n>>k0;
    double arr[n][2];
    for(int i=0;i<n;i++){
        cin>>arr[i][0];
        cin>>arr[i][1];
    } 

    double total=0.0;
    int k=0;

    while(judge(arr,n)!=0){
        

        double min=10000.0;
       
        double arr2[n-1]={0.0};
        
        for(int i=0;i<n-1;i++){
            if(arr[i+1][1]-arr[i][1]==-2){
                arr2[i]=arr[i+1][0]-arr[i][0];
                
                if(arr2[i]<min) {
                    min=arr2[i];
                }
            }
            
        }


        double time = min/2;
        total+= time;

        for(int i=0;i<n;i++){
            arr[i][0]+=arr[i][1]*time;
        }

        for(int i=0;i<n-1;i++){
            if(arr2[i]==min){
                 swap(arr[i][1],arr[i+1][1]);
                 k+=1;
                 
            }
        }

        if(k==k0) cout<<"Yes"<<endl<<fixed<<setprecision(6)<<total;

        // cout<<min<<" "<<p;
    }

    if(k<k0) cout<<"No";

// cout<<judge(arr,n);
}