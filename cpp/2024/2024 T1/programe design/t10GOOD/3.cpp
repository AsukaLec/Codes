#include <iostream>
#include <string>
#include <algorithm>
using namespace std;



int judge(const string& a, const string& b) {
    
    for (size_t i = 0; i < a.length(); i++){
            if (a[i] > b[i])
                return 1;
    else
    return 0;
    }
}//用于判断输入的两个整数谁大谁小，主要用在位数相同的时候

int main(){
    string str1;
    string str2;
    cin>>str1>>str2;
    int m=str1.size();
    int n=str2.size();
    int arr1[80];
    int arr2[80];
    int arr3[80];//他说的最多80位 把输入的数字输入进数组中
    for(int i=0;i<80;i++){
        arr1[i]=0;
        arr2[i]=0;
        arr3[i]=0; //先把所有数组预设成0 arr1和arr2记录输入的数，arr3记录两个数相减的结果
    }//
    for(int i=m-1;i>=0;i--){
        arr1[m-1-i]=str1[i];
    }//把输入的数字的最后一位放到新数组的第一位，方便之后运算。相当于把输入的数字倒叙输入进新建的数组中
    for(int i=n-1;i>=0;i--){
        arr2[n-1-i]=str2[i];
    }//同上
    

    if(m<n){
        for(int i=0;i<m;i++){
            arr3[i]+=arr2[i]-arr1[i];
            if(arr3[i]<0){
                arr3[i]+=10;
                arr3[i+1]-=1;
            }
        }
        for(int i=m;i<n;i++){
            arr3[i]=arr2[i]+arr3[i]-48;//减48是因为原来数字是当作字符输入进int类型的数组里的，输入的是arcii码，如果是相减的话结果没事，但如果是顺位下来的话就要减去0的arcii码
            if(arr3[i]<0){
                arr3[i]+=10;
                arr3[i+1]-=1;
            }
        }
        arr3[n-1]=arr3[n-1]*(-1);
        int t;
        for(int i=79;i>=0;i--){//用来记录第一个不是0的位，进而确定开始输出数组的位置
            if(arr3[i]==0){
                t=i;
            }
            else{
                goto flag;
            }
            if(t==0){
                cout<<0;
            }
        }
        flag: t-=1;
        if(arr3[t]==9)
        arr3[t]*=-1;
        for(int i=t;i>=0;i--){
            cout<<arr3[i];
        }
        
        
    }
    

    
    if(m>n){//逻辑同上
        for(int i=0;i<n;i++){
            arr3[i]+=arr1[i]-arr2[i];
            if(arr3[i]<0){
                arr3[i]+=10;
                arr3[i+1]-=1;
            }
        }
        for(int i=n;i<m;i++){
            arr3[i]=arr1[i]+arr3[i]-48;
            if(arr3[i]<0){
                arr3[i]+=10;
                arr3[i+1]-=1;
            }
        }
        int t;
        for(int i=79;i>=0;i--){
            if(arr3[i]==0){
                t=i;
            }
            else{
                goto flag1;
            }
            if(t==0){
                cout<<0;
            }
        }
        flag1: t-=1;
        
        for(int i=t;i>=0;i--){
            cout<<arr3[i];
        }
        
         
    }
    
    if(m==n){//一坨，自己看
        if(judge(str1,str2)){
            for(int i=0;i<m;i++){
                arr3[i]=arr1[i]-arr2[i];
                if(arr3[i]<0){
                    arr3[i]+=10;
                    arr3[i+1]-=1;
                }
            }
            int t;
            for(int i=79;i>=0;i--){
                if(arr3[i]==0){
                    t=i;
                }
                else{
                    goto flag2;
                }
                if(t==0){
                cout<<0;
                }
            }
            flag2:t-=1;
            for(int i=t;i>=0;i--){
                cout<<arr3[i];
            }
            
        }
        
        else{
            for(int i=0;i<m;i++){
                arr3[i]=arr2[i]-arr1[i];
                if(arr3[i]<0){
                    arr3[i]+=10;
                    arr3[i+1]-=1;
                }
            }
            int t;
            for(int i=79;i>=0;i--){
                if(arr3[i]==0){
                    t=i;
                }
                else{
                    goto flag3;
                }
                if(t==0){
                cout<<0;
                }
            }
            
            flag3:t-=1;
            
            arr3[t]*=-1;
            for(int i=t;i>=0;i--){
                cout<<arr3[i];
            }
            
        }
        
    }
}

// #include <iostream>
// #include <string>
// #include <cstring> // 用于 strlen 函数

// int c[100];

// int judge(const string& a, const string& b) {
//     if (a.length() > b.length())
//         return 1;
//     else if (a.length() < b.length())
//         return 0;
//     else {
//         for (size_t i = 0; i < a.length(); i++)
//             if (a[i] > b[i])
//                 return 1;
//     }
//     return 0;
// }

// void minus(const string& a, const string& b) {
//     string t = a;
//     for (size_t i = 0; i < t.length() / 2; i++) {
//         swap(t[i], t[t.length() - 1 - i]);
//     }
//     for (size_t i = 0; i < b.length() / 2; i++) {
//         swap(t[i], t[b.length() - 1 - i]);
//     }
//     for (size_t i = 0; i < t.length(); i++) {
//         if (i < b.length())
//             c[i] = t[i] - b[i];
//         else
//             c[i] = t[i] - '0';
//     }
//     for (size_t i = 0; i < t.length() - 1; i++) {
//         if (c[i] < 0) {
//             c[i] += 10;
//             c[i + 1] -= 1;
//         }
//     }
// }

// void deletechar(string& a) {
//     size_t t = 0;
//     while (t < a.length() && a[t] == '0')
//         t++;
//     a.erase(0, t);
// }

// using namespace std;

// int main() {
//     string a, b;
//     cin >> a;
//     cin >> b;
//     deletechar(a);
//     deletechar(b);
//     if (judge(a, b))
//         minus(a, b);
//     else {
//         cout << "-";
//         minus(b, a);
//     }
//     for (int i = 99; i >= 0; i--) {
//         if (c[i] != 0 || i == 0)
//             cout << c[i];
//     }
//     return 0;
// }