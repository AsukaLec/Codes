#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr1[n][n];
    int i=1;

    for(int a=n-1;a>-1;a--){
        for(int b=0;b<n;b++){
            arr1[b][a]=i;
            i+=1;
        }
    }
    
    for(int a=0;a<n;a++){
        for(int b=0;b<n;b++){
            cout<<setw(4)<<arr1[a][b];
        }
        cout<<endl;
    }



}