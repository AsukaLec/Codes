#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int id;
    int start;
    int end;
};

bool cmp(const Node &a, const Node &b) {
    return a.end < b.end;
}

int main() {
    int n;

    while (cin >> n && n) {
        vector<Node> gene(n);
        for (int i = 0; i < n; i++) {
            cin >> gene[i].start >> gene[i].end;
            gene[i].id = i + 1;
        }

        sort(gene.begin(), gene.end(), cmp);
        int temp = gene[0].end;
        cout << gene[0].id;

        for (int i = 1; i < n; i++) {
            if (gene[i].start > temp) {
                temp = gene[i].end;
                cout << " " << gene[i].id;
            }
        }

        cout << "\n";
    }

    return 0;
}
