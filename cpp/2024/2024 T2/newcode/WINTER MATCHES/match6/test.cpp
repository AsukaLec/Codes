#include <bits/stdc++.h>

using namespace std;

int main() {
    int arr[]={1,5,2,4,3};
    sort(arr+1,arr+3);
    for(int i=0;i<5;i++){
        cout<<arr[i]<<" ";
    }
}