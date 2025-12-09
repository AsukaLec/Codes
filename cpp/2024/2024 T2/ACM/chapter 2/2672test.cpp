#include <iostream>
#include <unordered_map>
using namespace std;

#define N 3010

int dp[N][N];
int n;
unordered_map<int, int> mp;

// Input	Output

// 10
// 1 1 3 -1 2 0 5 -1 -1 8


// 5
// 1 -1 0 -1 -1

int main() {
    int test = 0;
    n = 10;

        
        if (test != 0)
            cout << endl;
        test++;

        int a[] = {0, 1, 1, 3, -1, 2, 0, 5, -1, -1, 8};

        for (int i = 1; i <= n; i++)
            for (int j = i + 1; j <= n; j++)
                dp[i][j] = 1;
        mp.clear();

        int m = 0, x, y;
        x = a[1];

        for (int i = n; i >= 1; i--) {
            for (int j = 1; j < i; j++) {
                int k = a[i] + a[j];
                auto it = mp.find(k);
                if (it != mp.end()) {
                    dp[j][i] = dp[i][it->second] + 1;
                    if (dp[j][i] > m) {
                        m = dp[j][i];
                        x = j;
                        y = i;
                    }
                }
            }
            mp[a[i]] = i;
        }
        if (n == 1) {
            cout << "1" << endl << a[1] << endl;
            
        }
        if (n == 2) {
            cout << "2" << endl << a[1] << " " << a[2] << endl;
            
        }
        if (m == 0) {
            cout << "2" << endl << a[1] << " " << a[2] << endl;
        } else {
            cout << m + 1 << endl;
            x = a[x], y = a[y];
            cout << x;
            for (int i = 1; i <= m; i++) {
                cout << " " << y;
                int z = x + y;
                x = y;
                y = z;
            }
            cout << endl;
        }
    
    return 0;
}