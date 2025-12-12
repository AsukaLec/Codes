#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b;
    cin >> a >> b;
    // 交换a和b的值
    a ^= b;
    b ^= a;
    a ^= b;
    cout << a << " " << b << endl;

    return 0;
}