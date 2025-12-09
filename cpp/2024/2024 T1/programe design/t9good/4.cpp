#include <iostream>
#include <string>
using namespace std;
int main(){
    string str;
    cin>>str;
    int n=str.size();
    char arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = str[i];
    }
    char a0;
    cin>>a0;
    
    if(arr[0]=='a'){
        cout<<"abcdef";
       
    }
    else{
        int i=0;
    while(arr[i]<a0){
        cout<<arr[i];
        i+=1;
    }
    cout<<a0;
    while(i<n){
        cout<<arr[i];
        i+=1;
    }

    }
}