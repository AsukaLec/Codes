#include <bits/stdc++.h>

using namespace std;

#define inf 0x7f7f7f7f
#define maxn 500005
#define mod 1000000007
#define N 200005
#define P 2
typedef long long ll;

int n, m;
struct Bean {
    int j, f;
    double avg;
} b[1005];


bool cmp(Bean a, Bean b) {
    return a.j * b.f > b.j * a.f;
}
int main() {
    while (scanf("%d%d", &m, &n) != EOF &&(n!= -1&&m!=-1)) {
        for (int i = 1; i <= n; i++) {
            cin >> b[i].j >> b[i].f;
            b[i].avg = 1.0 * b[i].j / b[i].f;
        }
        sort(b + 1, b + 1 + n, cmp);
        double res = 0;
        for (int i = 1; i <= n && m > 0; i ++) {

            if(m <= b[i].f){
                res += m * b[i].avg;
                m -= m;
            }else{
                res += b[i].j;
                m -= b[i].f;
            }
        }
        printf("%.3lf\n", res);
    }
}
