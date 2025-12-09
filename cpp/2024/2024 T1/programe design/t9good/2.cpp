#include <iostream>
#include <string>
using namespace std;

int main() {
    string str1;
    string str2;
    getline(cin, str1); // 使用getline读取带空格的字符串
    getline(cin, str2); 
    int n=str1.size();
    int m=str2.size();
    char arr1[n];
    char arr2[m];
    for (int i = 0; i < n; ++i) {
        arr1[i] = str1[i];
    }
    for (int i = 0; i < m; ++i) {
        arr2[i] = str2[i];
    }
    
    int arr3[n];
    for(int i=0;i<n;i++){
        arr3[i]=1;
    }
    int t=0;
    for(int i=0;i<n;i++){
        for(int k=0;k<m;k++){
            if(arr1[i]==arr2[k]){
                arr3[i]=0;
                t+=1;
            }
        }
    }
    
    if(t==0){
        cout<<arr1;
    }
    else{
        for(int i=0;i<n;i++){
        if(arr3[i]==1){
            cout<<arr1[i];
        }
        }

    }

    
    



}