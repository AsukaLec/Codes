#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 10;

struct Node {
    double x, y;
};

struct Distance {
    int n1, n2;
    double dis;
};

struct Road {
    int from, to;
};

bool cmp(const Distance &a, const Distance &b) {
    return a.dis < b.dis;
}

bool cmpp(const Road &a, const Road &b) {
    if (a.from != b.from) return a.from < b.from;
    return a.to < b.to;
}

int fa[maxn], height[maxn];

int find(int x) {
    while (fa[x] != x) {
        x = fa[x];
    }
    return x;
}

bool judge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx == fy) return true;
    if (height[fx] > height[fy]) {
        fa[fy] = fx;
    } else if (height[fx] == height[fy]) {
        fa[fy] = fx;
        height[fx]++;
    } else {
        fa[fx] = fy;
    }
    return false;
}

int main() {
    int T, N, M;
    cin >> T;
    while (T--) {
        cin >> N;
        vector<Node> cities(N);
        for (int i = 0; i < N; i++) {
            cin >> cities[i].x >> cities[i].y;
        }

        cin >> M;
        vector<pair<int, int>> existingRoads(M);
        for (int i = 0; i < M; i++) {
            cin >> existingRoads[i].first >> existingRoads[i].second;
            existingRoads[i].first--;
            existingRoads[i].second--;
        }

        vector<Distance> distances;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                double dis = sqrt(pow(cities[i].x - cities[j].x, 2) + pow(cities[i].y - cities[j].y, 2));
                distances.push_back({i, j, dis});
            }
        }

        sort(distances.begin(), distances.end(), cmp);

        for (int i = 0; i < N; i++) {
            fa[i] = i;
            height[i] = 1;
        }

        for (const auto &road : existingRoads) {
            judge(road.first, road.second);
        }

        vector<Road> newRoads;
        for (const auto &d : distances) {
            if (!judge(d.n1, d.n2)) {
                newRoads.push_back({d.n1, d.n2});
            }
        }

        sort(newRoads.begin(), newRoads.end(), cmpp);

        for (const auto &road : newRoads) {
            cout << road.from + 1 << " " << road.to + 1 << endl;
        }

        if (T) cout << endl;
    }
    return 0;
}
