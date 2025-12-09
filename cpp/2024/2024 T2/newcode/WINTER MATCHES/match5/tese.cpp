#include <iostream>
#include <cmath>
using namespace std;

bool canTransform(int n, int m) {
    if (n == m) {
        return true;
    }
    if (n > m) {
        return false;
    }

    while (m > n) {
        // 如果 m 是偶数，尝试除以 2
        if (m % 2 == 0) {
            m /= 2;
        } else {
            // 如果 m 是奇数，尝试平方
            m = int(sqrt(m));
            // 如果平方后小于 n，无法回到 n
            if (m < n) {
                return false;
            }
        }
        // 如果 m 等于 n，返回 true
        if (m == n) {
            return true;
        }
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        if (canTransform(n, m)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}