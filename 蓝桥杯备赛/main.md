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

---

## lq20526 数组翻转

**问题描述**

小明生成了一个长度为 $n$ 的正整数数组  
$a_1, a_2, \dots, a_n$。  
他可以选择连续的一段数  
$a_l, a_{l+1}, \dots, a_r$，  
如果其中所有数都相等，即  
$a_l = a_{l+1} = \dots = a_r$，  
那么他可以获得  
$(r - l + 1) \times a_l$  
的分数。

在选择之前，为了让分数尽可能大，他决定先选择数组中的一段区间，对其进行**左右翻转**。他想知道在对数组进行翻转之后，他能获得的最大分数是多少？

> 提示：当翻转 $a_l$ 到 $a_r$ 这段区间后，整个数组会变为  
> $a_1, a_2, \dots, a_{l-1}, a_r, a_{r-1}, \dots, a_{l+1}, a_l, a_{r+1}, \dots, a_n$。


**输入格式**
输入共两行。
第一行为一个正整数 $n$。  
第二行为 $n$ 个由空格分开的正整数 $a_1, a_2, \dots, a_n$。

**输出格式**
输出一个整数，表示翻转某段连续区间后，所能获得的最大分数。

**数据范围**
- $1 \le n \le 10^6$  
- $1 \le a_i \le 10^6$

> 翻转操作的唯一作用，是可以将原数组中相同值 $v$ 的两段**不相邻**的连续区间调换位置，使它们在翻转后**相邻**，从而合并为一段更长的相同值区间。
> - **不翻转**：对于值 $v$，只能获取它在原数组中某一段**最大连续长度** $L_{\max}$，得分为  $L_{\max} \times v$。
> - **允许一次翻转**：对于每个值 $v$，可以选择原数组中两段**连续且值都为 $v$** 的区间，其长度分别为 $L_1, L_2$，通过翻转把它们拼接到一起，获得长度 $L_1 + L_2$ 的区间，得分为  $(L_1 + L_2) \times v$。  
> 
> 最优情况下，对于每个 $v$，应选其**最长的两段**连续区间。

**算法实现**

只需一次从左到右的线性扫描。

定义  
`per[i]`：以位置 `i` 结尾的、值与 `a[i]` 相同的最长连续段长度。

递推规则  
  - 若 `a[i] == a[i-1]`，则 `per[i] = per[i-1] + 1`；  
  - 否则（段结束）  
    - 将刚结束段的长度 `per[i-1]` 记入哈希表 `mp[a[i-1]]`，并更新该值对应的「第一长」`f1` 与「第二长」`f2`；  
    -  重置 `per[i] = 1`。

扫描结束后，哈希表 `mp[v]` 中保存了值为 `v` 的所有连续段的「第一长」`f1` 和「第二长」`f2`。

对每个键值对 `(v, (f1, f2))` 计算得分 `v × (f1 + f2)`，取全局最大值即可。

** 复杂度 **
- 时间：O(n)  
- 空间：O(n)（`per` 数组 + 哈希表）

```cpp
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll N = 1e6 + 5;

void solve(){
    int n;
    cin >> n;
    vector<ll> a(n+5), per(n+5);
    map<int, pair<ll, ll>> mp;
  
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n + 1; i++) {
        if (a[i] == a[i - 1]) {
            per[i] = per[i - 1] + 1;
        } else {
            per[i] = 1;
            auto &[firs, seco] = mp[a[i - 1]];
            if (per[i - 1] > firs) {
                seco = firs;
                firs = per[i - 1];
            } else {
                seco = max(seco, per[i - 1]);
            }
        }
    }

    ll ans = 0;
    for (auto [x, pa] : mp) {
        auto [firs, seco] = pa;
        ans = max(ans, x * (firs + seco));
    }

    cout << ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
```