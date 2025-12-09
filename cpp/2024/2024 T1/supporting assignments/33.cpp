#include <iostream>
#include <string>
#include <algorithm> // 用于 std::reverse
using namespace std;
int reverseInteger(int x) {
    string str = to_string(x); // 将整数转换为字符串
    reverse(str.begin(), str.end()); // 反转字符串
    return stoi(str); // 将反转后的字符串转换回整数
}

int judge(int x){
    int x0=x;
    int t=2;
    int d=0;
    while(t<=x0){
        if(x%t==0){
            d+=1;
        }
        t+=1;
    }
    if(d==1) return 1;
    else return 0;
}

int main(){
    int m;
    cin>>m;
    if(judge(m)==1){
        if(judge(reverseInteger(m))==1)
        cout<<"yes";
        else cout<<"no";
    }
    else cout<<"no";

}