[TOC]
# <center>刷过的题

## lq20534 爆破

**问题描述**
小明正在参加一场爆破工作。人们在地面上放置了 n 个爆炸魔法阵，第 i 个魔法阵的圆心坐标为 \( (x_i, y_i) \)，半径为 \( r_i \)。如果两个魔法阵相交，则它们可以一起引爆；如果两个魔法阵不相交，则可以再使用一条魔法回路将它们的边缘连接起来。小明想知道最少需要布置总长度多长的魔法回路才能使得所有的魔法阵可以一起引爆？

**输入格式**
输入共 \( n + 1 \) 行。
- 第一行为一个正整数 \( n \)。
- 后面 \( n \) 行，每行三个整数表示 \( x_i, y_i, r_i \)。

**输出格式**
输出共 1 行，一个浮点数表示答案（四舍五入保留两位小数）。

样例输入
```
4
0 0 1
2 0 2
-3 0 1
4 4 1
```
样例输出
```
2.47
```

**样例说明**
使用魔法回路连接第 1、3 个魔法阵，长度为 1。
使用魔法回路连接第 2、4 个魔法阵，长度为 \( 2\sqrt{5} - 3 = 1.47 \)。
总长度 2.47。

**评测用例规模与约定**
对于 40% 的评测用例，\( n \leq 500 \)。
对于 100% 的评测用例，\( 1 \leq n \leq 5000 \)，\( |x_i|, |y_i| \leq 2000 \)，\( 0 < r_i \leq 20 \)。

**Answer** 
该算法用kruskal写的 最小生成树
超时了哦 改用prime？
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
int n, f[N];
struct Node {
    double x, y, r;
} a[N];
struct Edge {
    int u, v;
    double w;
    bool operator<(const Edge &t) const {
        return w < t.w;
    }
};
vector<Edge> edges;
int find(int x) {
    if (f[x] != x) f[x] = find(f[x]);
    return f[x];
}
double dist(Node &a, Node &b) {
    double d = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    if (d <= a.r + b.r) return 0.0;
    return d - a.r - b.r;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].r;
        f[i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double d = dist(a[i], a[j]);
            edges.push_back({i, j, d});
        }
    }
    sort(edges.begin(), edges.end());
    double res = 0.0;
    for (auto e : edges) {
        int fu = find(e.u), fv = find(e.v);
        if (fu != fv) {
            f[fu] = fv;
            res += e.w;
        }
    }
    cout << fixed << setprecision(2) << res << "\n";
    return 0;
}
```

**Right Answer**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=5005;
const double INF=1e18;
struct node{
  int x,y,r;
}a[N];
double dis[N];
int vis[N],n;
double ans=0;

double solve(node a,node b){
   double x=a.x-b.x;
   double y=a.y-b.y;
   double d=sqrt(x*x+y*y);
   return max(0.0,d-a.r-b.r);
}
void prime(){
  // memset(vis,0,sizeof(vis));
   //memset(dis,INF,sizeof(dis));
   for(int i=1;i<=n;i++){
     dis[i]=INF;
     vis[i]=0;
   }
  dis[1]=0;
  for(int i=1;i<=n;i++){
      int u=-1;
      double mmin=INF;
      for(int j=1;j<=n;j++){
        if(!vis[j]&&dis[j]<mmin){
           u=j;
           mmin=dis[j];
        }
      }
      ans+=mmin;
      vis[u]=1;
      //更新
      for(int j=1;j<=n;j++){
           if(!vis[j]){
             dis[j]=min(dis[j],solve(a[j],a[u]));
           }
      }
  }
   return;
}

signed main(){
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i].x>>a[i].y>>a[i].r;
  }
  prime();
  printf("%.2lf",ans);
  return 0;
}
```
