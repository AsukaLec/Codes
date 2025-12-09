#include <bits/stdc++.h>
using namespace std;
#include <iostream>
using namespace std;

int main(){
    long long a,b;
    cin>> a >> b;
    cout<< a * b - a - b;
    return 0;
}

// 原思路错误 eg 7，9
// #include <bits/stdc++.h>
// using namespace std;
// #include <iostream>
// using namespace std;

// // 函数：计算两个数的最大公约数（GCD），使用欧几里得算法
// long long gcd(long long a, long long b) {
//     while (b != 0) {
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }

// // 函数：计算两个数的最小公倍数（LCM）
// long long lcm(long long  a, long long b) {
//     return (a / gcd(a, b)) * b; // 为了避免溢出，先除以GCD再乘
// }


// int main(){
//     long long a,b;
//     cin>> a >> b;
//     if(a < b) cout<< lcm(a-1, b) - a;

//     else cout<< lcm(b-1, a) - b;
//     return 0;
// }