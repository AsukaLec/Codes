#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXN 105
#define MAXM 5000

struct Edge {
    int start, end;
    double weight;
} edges[MAXM];

int parent[MAXM];
double cityX[MAXN], cityY[MAXN];
int cityCount, edgeCount;
double totalWeight;

int findRoot(int x) {
    int root;
    for (root = x; parent[root] >= 0; root = parent[root])
        ;
    while (root != x) {
        int temp = parent[x];
        parent[x] = root;
        x = temp;
    }
    return root;
}

void mergeSets(int root1, int root2) {
    int r1 = findRoot(root1);
    int r2 = findRoot(root2);
    int temp = parent[r1] + parent[r2];
    if (parent[r1] > parent[r2]) {
        parent[r1] = r2;
        parent[r2] = temp;
    } else {
        parent[r2] = r1;
        parent[r1] = temp;
    }
}

int compareEdges(const struct Edge *a, const struct Edge *b) {
    if (a->weight > b->weight) return 1;
    else return -1;
}

void calculateMinimumSpanningTree() {
    int connectedEdges = 0;
    int i;
    memset(parent, -1, sizeof(parent));
    for (i = 0; i < edgeCount; i++) {
        int u = edges[i].start;
        int v = edges[i].end;
        if (findRoot(u) != findRoot(v)) {
            totalWeight += edges[i].weight;
            connectedEdges++;
            mergeSets(u, v);
        }
    }
}

int main() {
    int testCase = 1;
    while (scanf("%d", &cityCount), cityCount) {
        int i, j;
        double distance;
        for (i = 0; i < cityCount; i++) {
            scanf("%lf%lf", &cityX[i], &cityY[i]);
        }
        int edgeIndex = 0;
        for (i = 0; i < cityCount; i++) {
            for (j = i + 1; j < cityCount; j++) {
                distance = sqrt((cityX[i] - cityX[j]) * (cityX[i] - cityX[j]) + (cityY[i] - cityY[j]) * (cityY[i] - cityY[j]));
                edges[edgeIndex].start = i;
                edges[edgeIndex].end = j;
                edges[edgeIndex].weight = distance;
                edgeIndex++;
            }
        }
        edgeCount = edgeIndex;
        qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);
        totalWeight = 0.0;
        calculateMinimumSpanningTree();
        if (testCase > 1) printf("\n");
        printf("Case #%d:\n", testCase);
        printf("The minimal distance is: %.2lf\n", totalWeight);
        testCase++;
    }
    return 0;
}
