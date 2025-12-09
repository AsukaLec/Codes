#include <bits/stdc++.h>
#include <algorithm> 
using namespace std;
int main(){
    int k;
    cin>>k;
    int arr[k];
    for(int i=0;i<k;i++){
        cin>>arr[i];
        
    }
    sort(arr,arr+k);
 
    cout<<arr[k/2]-1;
}