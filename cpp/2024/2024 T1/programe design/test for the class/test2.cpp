#include<iostream>
using namespace std;
//先预设足够小的最大值及足够大的最小值，以及代表每次输入的数的变量a
long long a,b,maxnum=-92233720368547758,minnum=92233720368547758,n;

int main(){
    cin>>n;//确定循环次数
    
    for(b=0;b<n;++b){//运用for循环使每次输入数字都可以与预设的最大值最小值比较
        cin>>a;
        if(a>=maxnum){//将预设数字与输入值比较
            maxnum=a;//当输入数字大于预设值时，将输入值赋值给最大值
        }
        if(a<=minnum){//将预设数字与输入值比较
            minnum=a;//当输入数字小于预设值时，将输入值赋值给最小值
        }
    }
cout<<maxnum<<" "<<minnum;
}