#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a, path;
vector<bool> used;

void dfs(int pos) {
    if (pos == k) {                    // 已选满 k 个
        for (int i = 0; i < k; ++i) cout << path[i] << " \n"[i + 1 == k];
        return;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            used[i] = true;
            path[pos] = a[i];
            dfs(pos + 1);
            used[i] = false;           // 回溯
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.resize(n);
    for (int &x : a) cin >> x;

    path.resize(k);                   
    used.assign(n, false);

    dfs(0);
    return 0;
}