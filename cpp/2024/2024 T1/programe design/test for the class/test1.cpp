#include <iostream>
using namespace std;

int main() {

    int a;
    cin>>a; //按要求将已知的整数个数输入到程序中
    
    long long arr[a]; //利用已知的整数个数，定义一个数组

//先提取数组中的第一个数，与下一个数的大小进行比较。
 
    for(int i = 0; i < a; ++i) {//
        cin >> arr[i];
    }
    int k=1;//求最大值，初始化最大值为数组中的第一个数
    int t=1;//求最小值，初始化最小值为数组中的第一个数
    
    for(int i=0;i<a;++i){//代表总共的比较次数为已知整数个数-1
        if(arr[k]<=arr[i]){//比较数组的两个数，将较大的数赋值给最大值
            k=i;
        }
    }

    for(int i=0;i<a;++i){//代表总共的比较次数为已知整数个数-1
        if(arr[t]>=arr[i]){//比较数组的两个数，将较小的数赋值给最小值
            t=i;
        }
    }
    
    cout<<arr[k]<<" "<<arr[t];//输出结果

    return 0;
}