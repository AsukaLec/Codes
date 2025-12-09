#include <iostream>
#include <fstream>
using namespace std;

int main(){
    ifstream input("card.in");
    ofstream output("card.out");

    int n;
    input>>n;

    int arr[n];
    int t=0;
    int k;
    int sum=0;
    for(int i=0;i<n;i++){
        input>>arr[i];
        sum+=arr[i];
    }
    k=sum/n;
    
    if(n%2==1){
        for(int i=0;i<n/2;i++){
        if(arr[i]!=k){
            int x=k-arr[i];
            arr[i+1]+=x;
            t+=1;
        }
        if(arr[n-1-i]!=k){
            int x=k-arr[n-1-i];
            arr[n-2-i]+=x;
            t+=1;
        }
        }
    }

    if(n%2==1){
        for(int i=0;i<=(n-1)/2;i++){
        if(arr[i]!=k){
            int x=k-arr[i];
            arr[i+1]+=x;
            t+=1;
        }
        if(arr[n-1-i]!=k){
            int x=k=arr[n-1-i];
            arr[n-2-i]+=x;
            t+=1;
        }
        }
    }
    

    output<<t;

    input.close();
    output.close();
}