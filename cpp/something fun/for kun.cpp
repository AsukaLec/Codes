#include <iostream>

using namespace std;

int main(){


    // string str="feather";
    // string secreat="abcbcdefghijklmnopqrstuvwxyz";

    cin>>str;
    cin>>secreat;

    int arr0[26];
    for(int i=0;i<26;i++){
        arr0[i]=0;
    }//用于最后检验一个字母是否在密钥前端

    int n=str.size();
    for(int i=0;i<n;i++){
        arr0[str[i]-97]=1;
    }//初始化上面的那个数组

    char arr[n];
    for(int i=0;i<n;i++){
        arr[i]=str[i];
    }//把输入的字符串转成数组

    int t=0;
    for(int i=n-1;i>=0;i--){
        for(int k=0;k<i;k++){
            if(arr[i]==arr[k]){
                arr[i]=96;
                t+=1;
            }
        }
    }//检验重复

    char arr1[26];//正式的密钥数组

    int k=0;
    for(int i=0;i<n;i++){
        
        if(arr[i]!=96){
            arr1[k]=arr[i];
            k+=1;
        }

        
    }
    int q=122;
    int p=25;
    for(int i=n-t;i<26;i++){
        while(arr0[p]==1){
            p-=1;
            q-=1;
        }
        arr1[i]=q;
        p-=1;
        q-=1;
    }

    int m=secreat.size();
    for(int i=0;i<m;i++){
        cout<<arr1[secreat[i]-97];
    }



    


}