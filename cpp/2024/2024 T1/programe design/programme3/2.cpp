#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include <sstream>
#include <cmath>
using namespace std;
int main (){
    int x,y;
    cin>>x>>y;
    int arr[y-x];//素数集合
    int m=0;
    int b=0;
    int arr2[y-x];//反转素数为素数的集合
    int c=0;
    for(int i=x;i<=y;i++){
        for(int b=1;b<=i;b++){
           if(i%b==0){
            m=m+1;
           }
         }
        if(m==2){
        arr[b]=i;
        b=b+1;  
           }
        m=m-m;
    }//求解出素数集合
   
   for(int i=0;arr[i]!=0;i++){
        
        string a=to_string(arr[i]);
        reverse(a.begin(),a.end());
        istringstream ss(a);
        ss>>arr[i];
        
    }//反转素数

   

    for(int i=0;arr[i]!=0;i++){
        for(int b=1;b<=arr[i];b++){
           if(arr[i]%b==0){
            m=m+1;
           }
         }
        
        if(m==2){
        arr2[c]=arr[i];
        c=c+1;  
           }
        m=m-m;
    }//判断反转函数是否为素数 如果是 就输出相反的数字

    for(int i=0;arr2[i]>=2;i++){

        string a=to_string(arr2[i]);
        reverse(a.begin(),a.end());
        istringstream ss(a);
        ss>>arr2[i];
        cout<<arr2[i]<<endl;
    }
}