#include<bits/stdc++.h>
using namespace std;
priority_queue<int, vector<int>, greater<int>> pq;
int N, M, X, W;
int leftWeight[1005];
int rightWeight[1005];
map<long long, int> visited;
int result = 0;

void solve() {
    queue<int> que[2];
    int current = 0;
    que[current].push(0);
    for (int i = 0; i < 2 * (N - 1); i++) {
        visited.clear();
        while (!que[current].empty()) {
            int front = que[current].front();
            que[current].pop();
            que[current ^ 1].push(front);
            if (front == W) {
                result = 1;
                return;
            }
            int diff = rightWeight[i] - leftWeight[i];
            if (front + diff <= W && !visited[front + diff]) {
                que[current ^ 1].push(front + diff);
                visited[front + diff] = 1;
            }
        }
        current ^= 1;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        result = 0;
        memset(leftWeight, 0, sizeof(leftWeight));
        memset(rightWeight, 0, sizeof(rightWeight));
        while (!pq.empty()) pq.pop();
        for (int i = 1; i <= N; i++) {
            cin >> X;
            pq.push(X);
        }
        cin >> M;
        int sumLeft = 0;
        for (int i = 0; i < N - 1; i++) {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();
            pq.push(a + b);
            leftWeight[i] = a;
            rightWeight[i] = b;
            sumLeft += leftWeight[i];
        }
        W = M - sumLeft;
        solve();
        if (result) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
