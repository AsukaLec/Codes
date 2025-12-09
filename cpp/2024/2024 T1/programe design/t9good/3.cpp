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

    char arr3[n];
    for (int i = 0; i < n; ++i) {
        arr3[i] =-1;
    }
    

    int q=0;//统计有没有str2
    for(int i=0;i<n;i++){
        if(arr1[i]==arr2[0]){
            int s=0;
            arr3[i]=s;
            s+=1;
            for(int k=1;k<m;k++){
                if(arr1[i+k]==arr2[k]){
                    arr3[i+k]=s;
                    s+=1;
                }
            }
            if(s==m){
                q+=1;
            }
        }
    }

    for(int i=n-1;i>=0;i--){
        if(arr3[i]==m-1){
            cout<<i-m+1;
            goto flag;
        }
    }

    if(q==0){
        cout<<-1;
    }

    



    flag: return 0;

}