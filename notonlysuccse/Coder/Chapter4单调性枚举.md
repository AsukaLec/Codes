[TOC]
# <center> 四、 单调性枚举
## Lead In
给定一个长度为10万的非负整数数组和一个目标值 target
求一段最小区间 使得区间内数字之和大于 target
1、 枚举左右端点 计算区间内的和 复杂度：$O(n^3)$
2、 用前缀和代替区间和的计算 复杂度： $O(n^2)$
有没有什么办法让 复杂度 降为 $O(n)$ 呢、

画图可知：
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\part 1 单调性枚举 1.png" width="400"/>
  </div>
  <div style="text-align:center;">
    <img src="photos\part 1 单调性枚举 2.png" width="600"/>
  </div>
</div>

绿色区域左侧是无论如何不符合要求的 右侧是一定符合要求的
<mark>并且 对于所有的绿色区域 恒有 $r_i \leqslant r_{i + 1}$</mark>

``` cpp
vector<int> rightIndex(n);
for (int l = 0; l < n; l ++) {
    int r = l == 0 ? 0 : rightIndex[l- 1];
    for (; r< n; r ++){
        if (getSum(l, r) >= target){
            ans = min(ans, r - l + 1)
            break;
        }
    }
    rightIndex[l]= r;
}
```
复杂度为 $O(n)$ 注意复杂与于程序嵌套层数没有直接关系

**公式化定义**
<img src = 'photos\part 1 单调性枚举 3.png' width = 60% height = 60%>

<img src = 'photos\part 1 单调性枚举 4.png' width = 60% height = 60%>

**单调性证明**
<img src = 'photos\part 1 单调性枚举 5.png' width = 60% height = 60%>

``` cpp
int sum = 0;
for (int l = 0, r = 0; l < n;) {
    if (r < n && sum < target) {
        sum += arr[r++];
    } else {
        if (sum >= target) {
            ans = min (ans, r - l);
        }
        sum -= arr[l ++];
    } 
}
```
**四步关键**
1. 判断是否满足条件
2. r后移
3. l后移
4. 找到满足条件的关键词如何更新答案
   
**模板函数**

``` cpp 
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1); //右指针越界了也找不到匹配的区间，那自然就是剩下的所有区间了。
    remove(l ++, r);
    }
}
//本函数在跳出while后， [l, r - 1] 才是符合条件的最小区间（因为while内r已自增）[l, r - 2]就是不符合条件的最大区间， 所以update的是[l, r - 2]。

int main() {
    int start, end;
    int sum;//匹配条件
    increaseEnumerate ( start, end,
        [&](int l, int r) { // match

        },
        [&](int l, int r) { // insert

        },
        [&](int l, int r) { // remove 

        },
        [&](int l, int r) { // update

        });
}
```

样例：
<img src = 'photos\part 1 单调性枚举 6.png' width = 100% height = 100%>

<img src = 'photos\part 1 单调性枚举 7.png' width = 100% height = 100%>

**有单调递增枚举 也会有单调递减枚举**
<img src = 'photos\part 1 单调性枚举 8.png' width = 100% height = 100%>

**单调性剪枝**
<mark>题面和上题相同 但是二者在判断策略上很不一样哦</mark>
<img src = 'photos\part 1 单调性枚举 9.png' width = 100% height = 100%>

**总结**
1. 单调递增枚举 ： 二元组满足条件的最小值， 单调递增
2. 四类求值 ： 最小满足， 最大不满足， 满足/不满足的方案数量
3. 公式化：关键值 条件 维护（移动） 更新
4. 单调递减枚举 ： 二元组满足条件的最小值， 单调递减
5. 单调性剪枝 ： 左边或者下面比现在的情况更差， 不用枚举（把二维矩阵的图画出来模拟一下即可）

***

## 4.1 lq179 日志统计
**题目描述**
小明维护着一个程序员论坛。现在他收集了一份“点赞”日志，日志共有 N 行。其中每一行的格式是 $\mathtt{ts\ id}$ 表示在 $\mathtt{ts}$ 时刻编号 $\mathtt{id}$ 的帖子收到一个“赞”。

现在小明想统计有哪些帖子曾经是“热帖”。如果一个帖子曾在任意一个长度为 D 的时间段内收到不少于$ K$ 个赞，小明就认为该帖子曾是“热帖”。

具体而言，如果存在某个时刻 T 满足该帖在 $[T,T+D)$ 这段时间内（注意是左闭右开区间）收到不少于 $K$ 个赞，该帖就曾是“热帖”。  

给定日志，请你帮助小明统计出所有曾是“热帖”的帖子编号。

**输入描述**
输入格式：

第一行包含三个整数 $N,D,K$。

以下 N 行每行一条日志，包含两个整数 $\mathtt{ts}$ 和 $\mathtt{id}$。  

其中 $1\le K\le N\le 10^5，0\le \mathtt{ts}\le 10^5，0\le \mathtt{id}\le 10^5$。

**输出描述**

按从小到大的顺序输出热帖 $\mathtt{id}$。每个 $\mathtt{id}$ 一行。

**输入输出样例** 
输入  
```
7 10 2
0 1
0 10
10 10
10 1
9 1
100 3
100 3
```  
输出  
```
1
3
```

!!! : 初见， 第二部分确定是否满足条件的很好判断。但第一部分数据处理不是很会，目前的想法是把每一组转换成一组键值对，然后排序，按每种情况进行独立判断。

!!! : 老师思路 : 更有滑动窗口的感觉，同时运用stl，代码很简洁。

不用模板
``` cpp
#include <bits/stdc++.h>
using namespace std;

// 条件 t[r] - t[l] >= d
// 不符合条件的区间， 是否有 >= k

int main() {
    int n, d, k;
    cin >> n >> d >>k;
    auto logs = vector<pair<int, int>>(n);
    for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
    sort(logs.begin(), logs.end());

    // for (int i = 0; i < n; i++) {
    //     cout << logs[i].first << ' ' << logs[i].second << endl;
    // }

    vector<int> cnt (100001);
    set<int> ans;
    for (int l = 0, r = 0; r < n; ) {
        while (r < n && logs[r].first - logs[l].first < d) {
            int id = logs[r++].second;
            cnt[id] ++;
            if (cnt[id] == k) ans.insert(id);
        }
        cnt[logs[l++].second]--;
    }
    for (auto x: ans) cout << x << endl;
}
```

使用模板
``` cpp
#include <bits/stdc++.h>
using namespace std;

// 条件 t[r] - t[l] >= d
// 不符合条件的区间， 是否有 >= k

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}


int main() {
    int n, d, k;
    cin >> n >> d >>k;
    auto logs = vector<pair<int, int>>(n);
    for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
    sort(logs.begin(), logs.end());

    // for (int i = 0; i < n; i++) {
    //     cout << logs[i].first << ' ' << logs[i].second << endl;
    // }
    vector<int> cnt (100001);
    set<int> ans;
    increaseEnumerate (0, n - 1,
        [&](int l, int r) { //match
            return logs[r].first - logs[r].first >= d;
        },
        [&](int l, int r) { //insert
            cnt[logs[r].second] ++;
        },
        [&](int l, int r) { //remove
            cnt[logs[l].second] --;
        },
        [&](int l, int r) { //update
            if (cnt[logs[l].second] >= k)  ans.insert(logs[l].second);
        });
    
    for (auto x: ans) cout << x << endl;
}
```

---

## 4.2 lq2109 统计子矩阵
**问题描述**
给定一个 $N \times M$ 的矩阵 $A$，请你统计有多少个子矩阵（最小 $1 \times 1$，最大 $N \times M$）满足子矩阵中所有数的和不超过给定的整数 $K$？

**输入格式**
第一行包含三个整数 $N,M,K$。
之后 $N$ 行，每行包含 $M$ 个整数，代表矩阵 $A$。

**输出格式**
一个整数代表答案。

**样例输入**
```cpp
3 4 10
1 2 3 4
5 6 7 8
9 10 11 12
```
**样例输出**
```
19
```

**评测用例规模与约定**
对于 $30\%$ 的数据，满足$ N, M \le 20$。
对于 $70\%$ 的数据，满足 $N, M \le 100$。
对于 $100\% $的数据，满足$1 \le N, M \le 500,\quad 0 \le A{i,j} \le 1000,\quad 1 \le K \le 250\,000\,000$.

!!! : 初见：<img src = 'photos\lq 2109 1.png' width = 50% height = 50%> 遍历策略如是说。

!!! : 单调性枚举仅在一维成立， 二维损失单调性。故本题需要先将二维转成一维。先枚举 [x1, x2] 再枚举每一列的和 $O(n^2) $[y1, y2] [l, r] <= k $O(n)$。

!!! : 500 的数据量 == $O(n^3)$

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }
    
    long long ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> sum(m);
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int y =0; y < m; y ++) sum[y] += maze[x2][y];

            int total = 0;
            for (int l = 0, r = 0; l < m; ) {
                while (r < m && total <= k) {
                    total += sum[r ++];
                }
                if (total > k) {
                    //[l, r - 2] 
                    ans += r - 2 - l + 1;
                } else {
                    //[l, r - 1]
                    ans += r - 1 - l + 1;
                }
                total -= sum[l ++];
            }
        }
    }
    cout << ans << endl;
}
```
模板
``` cpp
#include <bits/stdc++.h>
using namespace std;


template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }
    
    long long ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> sum(m);
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int y =0; y < m; y ++) sum[y] += maze[x2][y];

            int total = 0;

            increaseEnumerate (0, m - 1,
            [&](int l, int r) {
                return total > k;
            },
            [&](int l, int r) {
                total += sum[r];
            },
            [&](int l, int r) {
                total -= sum[l];
            },
            [&](int l, int r) {
                ans += r - l + 1;
            });
        }
    }
    cout << ans << endl;
}
```
---

## 4.3 lq 2174 最大子矩阵
**问题描述**

小明有一个大小为 \(N \times M\) 的矩阵，可以理解为一个 \(N\) 行 \(M\) 列的二维数组。

我们定义一个矩阵 \(m\) 的稳定度 \(f(m)\) 为：
\[
f(m) = \text{max}(m) - \text{min}(m)
\]
其中 \(\text{max}(m)\) 表示矩阵 \(m\) 中的最大值，\(\text{min}(m)\) 表示矩阵 \(m\) 中的最小值。

现在小明希望从这个矩阵中找到一个稳定度不大于 \(limit\) 的子矩阵，同时他还希望这个子矩阵的面积越大越好（面积可以理解为矩阵中元素个数）。

子矩阵定义如下：从原矩阵中选择一组连续的行和一组连续的列，这些行列交点上的元素组成的矩阵即为一个子矩阵。

**输入格式**

第一行输入两个整数 \(N\)、\(M\)，表示矩阵的大小。

接下来 \(N\) 行，每行输入 \(M\) 个整数，表示这个矩阵。

最后一行输入一个整数 \(limit\)，表示限制。

**输出格式**

输出一个整数，表示小明选择的子矩阵的最大面积。

**样例输入**
``` cpp
3 4
2 0 7 9
0 6 9 7
8 4 6 4
8
```

**样例输出**
``` cpp
6
```

!!! : 遍历策略同上题， 更新条件改为 [l, r] > limit 。 寻找不满足条件的最大值， 用到 insert erase maximum minimum 数据结构用到一个multiset。

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n ,m ,limit;
    cin >> n >> m;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }

    cin >> limit;
    int ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> mmin(m, INT_MAX);
        vector<int> mmax(m, INT_MIN);
        // insert [x1, x2] max, min
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int i = 0; i < m; i++) {
                mmin[i] = min(mmin[i], maze[x2][i]);
                mmax[i] = max(mmax[i], maze[x2][i]);
            }
            multiset<int> s;
            for (int l = 0, r = 0; l < m; ) {
                while (r < m && (s.empty() || *s.rbegin() - *s.begin() <= limit)) {
                    s.insert(mmin[r]);
                    s.insert(mmax[r++]);
                }

                if (!(s.empty() || *s.rbegin() - *s.begin() <= limit)) {
                    ans = max(ans, (x2 - x1 + 1) * (r - l - 1));
                } else {
                    ans = max(ans, (x2 - x1 + 1) * (r - l));
                }
                s.erase(s.find(mmin[l]));
                s.erase(s.find(mmax[l++]));
            }
        }
    }
    cout << ans << endl;
}
```
模板
``` cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    int n ,m ,limit;
    cin >> n >> m;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }

    cin >> limit;
    int ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> mmin(m, INT_MAX);
        vector<int> mmax(m, INT_MIN);
        // insert [x1, x2] max, min
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int i = 0; i < m; i++) {
                mmin[i] = min(mmin[i], maze[x2][i]);
                mmax[i] = max(mmax[i], maze[x2][i]);
            }
            multiset<int> s;
            
            increaseEnumerate (0, m - 1,
            [&](int l, int r) {
                return !s.empty() && *s.rbegin() - *s.begin() > limit;
            },
            [&](int l, int r) {
                s.insert(mmin[r]);
                s.insert(mmax[r]);
            },
            [&](int l, int r) {
                s.erase(s.find(mmin[l]));
                s.erase(s.find(mmin[l]));
            },
            [&](int l, int r) {
                ans = max(ans, (x2 - x1 + 1) * (r - l + 1));
            });
        }
    }
    cout << ans << endl;
}
```

---


## 4.4 P10444 极差

**题目描述**

对于一个序列 $c$ ，定义 $c$ 的极差为 $c$ 中最大值与最小值之差。现在给定一个长度为 $n$ 的序列 $a$，问是否能将其分成至少两个长度大于 $1$ 的子序列，使得每个子序列的极差都相等（注意，所有元素都必须分配且每个元素仅能分配到一个子序列中）。

**输入格式**
**本题包含多组数据**。
第一行两个整数 $T,id$，表示数据组数和子任务编号。
对于每组数据，
第一行一个正整数 $n$，表示数组长度。
第二行 $n$ 个整数表示序列 $a$。

**输出格式**

对于每组数据，输出一行一个字符串 `Yes` 或 `No`。

**输入输出样例 1**
输入 1

```
2 1
6
1 1 4 5 1 4
7
1 9 1 9 8 1 0
```

输出 1

```
No
Yes
```

**说明/提示**

 样例 $\small\text{1}$ 解释

样例符合子任务 1 的约束，$id=1$。


询问一：

可以证明，没有任何方案满足条件。

询问二：

合法分配的一种子序列集合如下：
- $\{1,9\}$。
- $\{1,9\}$。
- $\{8,1,0\}$。

答案不唯一。

**数据规模与约定**

**本题采用捆绑测试**。
- Subtask 1（20 points）：$4\le \sum n\le 20,a_i\ge 0$。
- Subtask 2（20 points）：$4\le \sum n\le 100,a_i\ge 0$。
- Subtask 3（20 points）：$4\le \sum n\le 10^3,a_i\ge 0$。
- Subtask 4（10 points）：$a$ 数组中元素相等。
- Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$4\le \sum n\le 10^6,0\le |a_i|\le 10^9,1\le T\le 300$。

!!! : 本题说实话更多像是数字特征的找寻 刻意陷在单调递减就有点…… 可能我没悟透？
!!! : 首先观察题意可以很容易体会到本题需要的将数字划分为两个序列（一开始卡在多个序列也成立但不知能不能变为两个序列，下见证明）。经过挣扎后发现若能划为多个序列，则一定可以划为两个序列。那么此时，要找到的则是是否有两个数 l, r， 满足 $l - a_1 =  a_n - r$， 即 $l + r = a_1 + a_n$，同时要满足剩下的数都可以塞在这两个区间内（这个可以靠排序解决）。

>证明：
假设有一给定序列 $a$, 排序后为 $a_1, a_2, a_3, ..., a_n$， 若该序列内存在多段极差相等的子序列， 则最后一定会有 $a_{x_1} - a_1 = a_n - a_{x_n}$ ($x_{x_n}$ 代表第n段子序列的段首或段尾) 即所有的数都能放进这两个区间内而不越界。

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
// 1 1 4 5 1 4
// 1 1 1 4 4 5
// [1 max] [min 5]
// max - 1 = 5 - min
// max + min = 5 + 1
// a + b = target
    int T, id;
    cin >> T >> id;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        sort(a.begin(), a.end());


        int target = a[0] + a[n - 1];
        cout << [&](){
            for (int l = 1, r = n - 2; l < r;) {
                if (a[l] + a[r] > target) {
                    r--;
                } else if (a[l] + a[r] < target) {
                    l++;
                } else {
                    return "Yes";
                }
            }
            return "No";
        }() << endl;
    }
}

```
---

## 4.5 lq2209 近似gcd 

**问题描述**

小蓝有一个长度为 \(n\) 的数组 \(A = (a_1, a_2, \cdots, a_n)\)，数组的子数组被定义为从原数组中选出连续的一个或多个元素组成的数组。数组的最大公约数指的是数组中所有元素的最大公约数。如果最多更改数组中的一个元素之后，数组的最大公约数为 \(g\)，那么称 \(g\) 为这个数组的近似GCD。一个数组的近似GCD可能有多种取值。

具体的，判断 \(g\) 是否为一个子数组的近似GCD如下：

1. 如果这个子数组的最大公约数就是 \(g\)，那么说明 \(g\) 是其近似GCD。
2. 在修改这个子数组中的一个元素之后（可以改成想要的任何值），子数组的最大公约数为 \(g\)，那么说明 \(g\) 是这个子数组的近似GCD。

小蓝想知道，数组 \(A\) 有多少个长度大于等于 2 的子数组满足近似 GCD 的值为 \(g\)。

**输入格式**

输入的第一行包含两个整数 \(n, g\)，用一个空格分隔，分别表示数组 \(A\) 的长度和 \(g\) 的值。

第二行包含 \(n\) 个整数 \(a_1, a_2, \cdots, a_n\)，相邻两个整数之间用一个空格分隔。

**输出格式**

输出一行包含一个整数表示数组 \(A\) 有多少个长度大于等于 2 的子数组的近似 GCD 的值为 \(g\)。

**样例输入**
```
5 3
1 3 6 4 10
```
**样例输出**
```
5
```

!!! : 分析可得， 在在某个窗口[l, r]内有两个不满足的值的话（最小的），那么[l. r - 1] 一定满足， 余下的内部的子数组也满足， 问题就变成了统计有几个 “2”的问题。

**初版 没过 怀疑是r越界的问题**
一拖四， 滑动窗口末尾的判定问题， 左端点的移动的高效的问题。
还是要把问题尽可能简化成一个条件和一个单向的数组
``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n , g ;
    cin >> n >> g;
    auto line = vector<int>(n);
    for (auto &x : line) cin >> x;
    
    long long ans = 0;

    if (g != 1) {
        for (int i = 0 ; i < n; i ++) line[i] = line[i] % g;

        int current = 0;
        for (int l = 0, r = 0; r < n; ) {
            if (!line[r] ) {
                ++ r;
            } else if (line[r] && !current) {
                current ++;
                r++;
            } else if (line[r] && current) {
                ans += r - l - 1;
                ++ l;
                r = l;
                current = 0;
            }
            
        }
    }

    if (g == 1) ans = n * (n - 1) / 2;
    
    cout << ans << endl;
}
```

**ac版 注意 l < n 改成 r < n 过不了 窗口边界越界的问题**
``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n , g ;
    cin >> n >> g;
    auto line = vector<int>(n);
    for (auto &x : line) cin >> x;
    
    long long ans = 0;

    for (int i = 0 ; i < n; i ++) {
            line[i] = line[i] % g;
            if (line[i] != 0) line[i] = 1;
    }
        
    int current = 0;
    for (int l = 0, r = 0; l < n; ) {
        while(r < n && current < 2) {
            current += line[r++];
        }
        
        if (current >= 2) {
            ans += (r - 2) - (l + 1) + 1;
        } else {
            ans += (r - 1) - (l + 1) + 1;
        }

        current -= line[l++];
    }
        

    cout << ans << endl;
}
```

---

## 4.6 lq2109 青蛙过河
**问题描述**

小青蛙住在一条河边，它想到河对岸的学校去学习。小青蛙打算经过河里的石头跳到对岸。

河里的石头排成了一条直线，小青蛙每次跳跃必须落在一块石头或者岸上。不过，每块石头有一个高度，每次小青蛙从一块石头起跳，这块石头的高度就会下降 \(1\)，当石头的高度下降到 \(0\) 时小青蛙不能再跳到这块石头上（某次跳跃后使石头高度下降到 \(0\) 是允许的）。

小青蛙一共需要去学校上 \(x\) 课，所以它需要往返 \(2x\) 次。当小青蛙具有一个跳跃能力 \(y\) 时，它能跳不超过 \(y\) 的距离。

请问小青蛙的跳跃能力至少是多少才能用这些石头上完 \(x\) 次课。

**输入格式**

输入的第一行包含两个整数 \(n, x\)，分别表示河的宽度和小青蛙需要去学校的天数。请注意 \(2x\) 是实际过河的次数。

第二行包含 \(n - 1\) 个非负整数 \(H_1, H_2, \cdots, H{n-1}\)，其中 \(H_i > 0\) 表示在河中与小青蛙的家相距 \(i\) 的地方有一块高度为 \(H_i\) 的石头，\(H_i = 0\) 表示这个位置没有石头。

**输出格式**

输出一行，包含一个整数，表示小青蛙需要的最低跳跃能力。

**样例输入**
```
5 1
1 0 1 0
```

**样例输出**
```
4
```


**样例说明**

由于只有两块高度为 1 的石头，所以往返只能各用一块。第 1 块石头和对岸的距离为 4，如果小青蛙的跳跃能力为 3 则无法满足要求。所以小青蛙最少需要 4 的跳跃能力。

**评测用例规模与约定**

对于 30\% 的评测用例, \(n \leq 100\);

对于 60\% 的评测用例, \(n \leq 1000\);

对于所有评测用例, \(1 \leq n \leq 10^5, 1 \leq x \leq 10^9, 1 \leq H_i \leq 10^4\)。

!!! : 初见：首先来回跳可以简化为2x只从一边往另一边跳。 忽略那些高度大于2x的点（即视其为与岸等价的点， 再统计两个可以视作为与岸等价的点之间的的总高度值与2x的大小的关系。若大于等于那么这个区间中所有点到左右两侧的最大值就是这个区间内需要的跳跃能力的最小值。（很复杂 而且估计是错的）

!!! : 老师： 从起点开始模拟思考。假设跳跃能力为y， 那么若要让所有青蛙都跳出第一步 [0, y] 之间的区间和必须>= 2x， 如此类推，[1, y + 1]... 反过来，就是要找相连的[l, r] 区间和内大于等于2x的区间 长度即为要更新的值。（tips：每只青蛙在区间内只能选一个点跳，即跳出一步）

``` cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main () {
    int n, x;
    cin >> n >> x;
    n--;
    vector<int> arr(n);
    for (auto & x : arr) cin >> x;

    x <<= 1;
    int sum = 0; 
    int ans = 0;

    increaseEnumerate (0, n - 1,
        [&](int l, int r) { //match
            return sum >= x;
        },
        [&](int l, int r) { //insert
            sum += arr[r];
        },
        [&](int l, int r) { //remove
            sum -= arr[l];
        },
        [&](int l, int r) { //update
            ans = max(ans, r - l + 1);
        });

    cout << ans + 1 << endl;
}
```

---

## 4.7 至少有K个重复字符的最长字串

**问题描述**
现有一个字符串 s 和一个整数 k， 请找出 s 中的最长字串， 要求该子串中每一个字符出现次数都不少于 k， 返回这一字串的长度。

若不存在，则直接返回0。

**示例 1:**

```
输入: s = aaabb, k = 3  


输出: 3

解释: 最长子串为 aaa，其中 'a' 重复了 3 次。
```
**示例 2:**
```
输入: s = ababbc, k = 2

输出: 5

解释: 最长子串为 ababb，其中 'a' 重复了 2 次，'b' 重复了 3 次。
```
**提示:**

- \(1 \leqslant \text{s.length} \leqslant 10^4\)
- \(s\) 仅由小写英文字母组成
- \(1 \leqslant k \leqslant 10^5\)

!!! : 首先题目条件不符合单调性的前提（可增加一个已知序列中不存在的字母）
!!! : 若是给定不同字母的总数 则可以规避这个问题（循环26次真的没问题吗）
!!! : 维护两个值， 一个记录字母种类 一个记录字母重复次数满足条件的个数

``` cpp

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;

    int ans = 0;
    for (int x = 1; x <= 26; x ++) {
        int cnt[128] = {};
        int typecnt = 0;
        int matchcnt = 0;
        for (int l = 0, r = 0; l < s.size();) {
            while (r < s.size() && typecnt <= x) {
                char c = s[r++];
                if (cnt[c] == 0) typecnt ++;
                cnt[c]++;
                if (cnt[c] == k) matchcnt ++;
            }
            //[l, r - 1] 最大匹配情况
            if (matchcnt == x) {
                if (typecnt > x) {
                    //[l, r - 1] 满足
                    //[l, r - 2] 不满足
                    ans = max(ans, r - 2 -l + 1);
                } else {
                    ans = max(ans, r - 1 - l + 1);
                }
            }
            char c = s[l ++];
            if (cnt[c]-- == k ) matchcnt--;
            if (cnt[c] == 0) typecnt --;
        }
    }
    cout << ans << endl;
}
```
模板
```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;

    int ans = 0;
    for (int x = 1; x <= 26; x ++) {
        int cnt[128] = {};
        int typecnt = 0;
        int matchcnt = 0;
    increaseEnumerate (0, s.size() - 1,
        [&](int l, int r) { //match
            return typecnt > x;
        },
        [&](int l, int r) { //insert
            char c = s[r];
            if (cnt[c]++ == 0) typecnt++;
            if (cnt[c] == k) matchcnt++;
        },
        [&](int l, int r) { //remove
            char c = s[l];
            if (cnt[c]-- == k) matchcnt--;
            if (cnt[c] == 0) typecnt--;
        },
        [&](int l, int r) { //update
            if (matchcnt == x) {
                ans = max(ans, r - l + 1);
            }
        });
    }
    cout << ans << endl;
}
```

## 4.8 盛最多水的容器
**问题描述**

给定一个长度为 \(n\) 的整数数组 \(\text{height}\)。有 \(n\) 条垂线，第 \(i\) 条线的两个端点是 \((i, 0)\) 和 \((i, \text{height}[i])\)。

找出其中的两条线，使得它们与 \(x\) 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。

**示例1**
<img src = 'photos\part 1 4.8.png' width = 60% height = 60%>

输入: [1,8,6,2,5,4,8,3,7]
输出: 49
解释: 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

**示例 2:**

输入: height = [1,1]
输出: 1

!!! : 要计算装的水， 其实就是找到一个让 min(h[l], h[r]) * dis(l, r) 最大的区间。若采用传统的l， r同起点开始遍历， 那么dis部分是单调的， 但是乘上前面的部分就不单调了。
!!! : 要找到单调的， 实际上就是找到什么高度在什么情况下和长度的增减性是一样的。并利用单调性排除掉不合理的情况。假设有一区间[l, r] h[l] < h[r]。那么，r左移的话，整体取值是单调减的（这与题目要求最大值相悖），所以这种情况可以都排除掉。即只能是l右移才有更新答案的可能性。 至于说l左移和r右移，要从中间开始遍历，比较反直觉，可能也可以？ 至于说大于的情况，反过来便是。
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector <int> height (n);
    for (auto &x : height) cin >> x;

   int ans = 0;
    for (int l = 0, r = height.size() - 1; l < r;) {
        ans = max(ans, min(height[l], height[r]) * (r - l));
        if (height[l] < height[r]) l++;
        else r--;
    }
    cout << ans << endl;
}
```

---

## 4.9 P10710 School Photo
**题目描述**

Zane 是 NOI 学校的校长。NOI 学校有 $n$ 个班，每个班有 $s$ 名同学。第 $i$ 个班中的第 $j$ 名同学的身高是 $a_{i,j}$。

现在 Zane 想从每个班上选出一名同学拍照，使得这 $n$ 名同学中最高的同学和最低的同学的身高差最小。

请你输出这个最小值。

**输入格式**

第一行，两个整数 $n,s$；

接下来 $n$ 行，每行 $s$ 个整数，表示 $a$。

**输出格式**

一行一个整数表示答案。

输入输出样例 1
输入 1

```
2 3
2 1 8
5 4 7
```

输出 1

```
1
```

输入输出样例 2

输入 2

```
3 3
3 1 4
2 7 18
9 8 10
```
输出 2

```
4
```

说明/提示

【样例 2 解释】

选择 $a_{1,3},a_{2,2},a_{3,2}$，答案为 $8-4=4$。

** **

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$11$|$n=2$|
|$2$|$22$|$n,s\le100$|
|$3$|$9$|$n,s\le250$|
|$4$|$33$|$n,s\le500$|
|$5$|$25$|无|

对于 $100\%$ 的数据，$1\le n,s \le 1000,1\le a_{i,j} \le 10^9$。

!!! : 初见， 每一行单独排序，然后逐一枚举
!!! : 换个角度想，不考虑班级，只考虑高度，就是在给定的身高中选两个最接近的。但是要满足选出n个人的条件，所以还要维护一个变量来存放当前序列中不同班级的数量。遍历方式见下

eg
```
3 3
3 1 4
2 7 18
9 8 10
```
||1|2|3|4|5|6|7|8|9|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|height|1|2|3|4|7|8|9|10|18|
|class|1|2|1|1|2|3|3|3|2|

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> arr;
    arr.reserve(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            arr.push_back({h, i});
        }
    }

    sort(arr.begin(), arr.end());

    vector<int> cnt(n);
    int classCnt = 0;
    int ans = INT_MAX;

    increaseEnumerate(0, n * m - 1,
        [&](int l, int r) {
            return classCnt == n;
        },
        [&](int l, int r) {
            if (cnt[arr[r++].second]++ == 0) classCnt++;
        },
        [&](int l, int r) {
            if (--cnt[arr[l++].second] == 0) classCnt--;
        },
        [&](int l, int r) {
            // [l, r+1]
            if (r + 1 == n * m) return;
            ans = min(ans, arr[r + 1].first - arr[l].first);
        });
    cout << ans << endl;
}
```

---

## 4.10 P8708 [蓝桥杯 2020 省 A1] 整数小拼接

**题目描述**

给定一个长度为 $n$ 的数组 $A_1,A_2,\cdots,A_n$。你可以从中选出两个数 $A_i$ 和 $A_j$($i\neq j$)，然后将 $A_i$ 和 $A_j$ 一前一后拼成一个新的整数。例如 `12` 和 `345` 可以拼成 `12345` 或 `34512`。注意交换 $A_i$ 和 $A_j$ 的顺序总是被视为 $2$ 种拼法，即便是 $A_i=A_j$ 时。

请你计算有多少种拼法满足拼出的整数小于等于 $K$。

**输入格式**

第一行包含 $2$ 个整数 $n$ 和 $K$。

第二行包含 $n$ 个整数 $A_1,A_2,\cdots,A_n$。

**输出格式**

一个整数代表答案。

输入输出样例 1
输入 1

```
4 33
1 2 3 4
```

输出 1

```
8
```

**说明/提示
**
对于 $30\%$ 的评测用例 $1\le n\le1000$，$1\le k\le10^8$，$1\le A_i\le10^4$。

对于所有评测用例，$1\le n\le10^5$，$1\le k\le10^{10}$，$1\le A_i\le10^9$。

!!! : 显而易见，题目本身没啥好说的，两个数拼接起来的时候，字符串开销比较大，所以单开一个数组用来计算进位

``` cpp

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end());
    // 12 & 345 >> 12 * 1000 + 345 
    //拼接后前一个数要偏移的大小
    vector<long long> exp(n, 1);
    for (int i = 0; i < a.size(); i++) {
        for (int x = a[i]; x; x /= 10, exp[i] *= 10);
    }

    long long ans = 0;
    for (int l = 0, r = n - 1; r >= 0 && l < n;) {
        if (a[l] * exp[r] + a[r] <= k) {
            ans += r - l;
            l++;
        } else {
            r--;
        }
    }

}
```
---

## 4.11 P8472 [Aya Round 1 G] 咕噜论坛（post） link to 4.2 二维矩阵下的枚举方式


**题目描述**

「咕噜论坛」的一篇帖子下，有若干个不同的人对其进行了回复，这些评论形成了一个 $n\times m$ 的矩阵。

论坛管理员 prAB 发现这些评论者的名字颜色只有灰名、紫名和棕名三种，他决定「动用神权」来增加这些评论的整齐度。但是论坛站长超氧化铯（CsO2）可能会因为他「滥用神权」导致论坛「臭名昭著」而踢掉他的管理身份。所以 prAB **最多**只能动用 $k$ 次神权。已知他的神权有两种：

- 「暴政警告」：送一个灰名进陶片使他变成棕名。
- 「放人一马」：将一个棕名解封使他变成灰名。

由于「咕噜论坛」的管理员是至高无上的，对于评论中的紫名他无能为力。

prAB 认为在这些评论者的名字颜色中，最大的颜色相同的子矩阵的大小能代表这篇帖子评论的整齐度。所以他想知道，他动用完神权后评论的整齐度的最大值。

**输入格式**

- 第一行输入三个整数 $n,m,k$。
- 接下来 $n$ 行，每行输入一个长度为 $m$ 的字符串，代表评论矩阵中每个人名字的颜色。其中 `B` 代表棕名，`G` 代表灰名，`P` 代表紫名。

**输出格式**

- 第一行输出一个整数，表示整齐度的最大值。
- 下面 $n$ 行，每行输出一个长度为 $m$ 的字符串，格式同「输入格式」。代表修改完后每个人名字的颜色。如有多种方案输出则任意一种即可。

 输入输出样例 1

 输入 1

```
3 4 2
BBGB
GBBB
PGPP
```

 输出 1

```
8
BBBB
BBBB
PGPP
```

**说明/提示**

**数据范围及约定**

对于 $100\%$ 的数据，$1 \le n,m\le 500$，$0 \le k \le nm$。字符矩阵中只会出现大写字母 `B`、`G` 和 `P`。

!!! : 易得P是没有讨论的必要的，所以分成两种情况， B，G来进行讨论。 将不需要修改的位置设成0， 要的位置设成1， 实际上就是要求最大的一个子矩阵，包含尽可能少的修改次数。P只需要修改为k+1（必越界）不参与讨论即可。
!!! : 详见4.2

``` cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> maze(n);
    for (auto &row : maze) cin >> row;
    int ans = 0;
    tuple<char, int, int, int, int> res;

    auto func = [&](int B, int G, int P) {
        vector<int> v(128);
        v['B'] = B;
        v['G'] = G;
        v['P'] = P;

        for (int x1 = 0; x1 < n; x1++) {
            vector<int> sum(m);
            for (int x2 = x1; x2 < n; x2++) {
                for (int i = 0; i < m; i++) {
                    sum[i] += v[maze[x2][i]];
                }
           

            int total = 0;
            increaseEnumerate(0, m - 1,
                [&](int l, int r) {
                    return total > k;
                },
                [&](int l, int r) {
                    total += sum[r];
                },
                [&](int l, int r) {
                    total -= sum[l];
                },
                [&](int l, int r) {
                    int temp = (x2 - x1 + 1) * (r - l + 1);
                    if (temp > ans) {
                        ans = temp;
                        char c = 'p';
                        if (B == 0) c = 'B';
                        else if (B == 1) c = 'G';
                        res = {c, x1, x2, l, r};
                    }
                });
            } 
        }
    };

    func(0, 1, k + 1);
    func(1, 0, k + 1);
    func(k + 1, k + 1, 0);

    auto [c, x1, x2, y1, y2] = res;
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            maze[x][y] = c;
        }
    }

    cout << ans << endl;
    for (auto row : maze) cout << row << endl;

}
```

## 4.12 接雨水
<img src="photos\枚举 2.4.png" width="100%" height="100%">

!!! : 和前缀和做法一样，对于每个点还是需要知道左右的最高高度。
```cpp
int trap(vector<int>& h) {
    int ans = 0;
    int n = h.size();
    for (int l = 1, r = n - 2, leftMax = h[0], rightMax = h[n - 1]; l <= r;) {
        leftMax = max(leftMax, h[l]);
        rightMax = max(rightMax, h[r]);
        if (leftMax < rightMax) ans += (leftMax - h[l++]);
        else ans += (rightMax - h[r--]);
    }
    return ans;
}

```

---

## 4.13 P11243 繁花

**题目背景**

我已经知道，在设置好循环播放时就已经知道，我是在麻痹自己，在逃避问题。

我承认如此，可捞起那些沉于水底的细节时，却一瞬间突然和所有所有真实的心跳共鸣。

那时总想的太少，现在常想得太多，不知所措似荒塘里的绿藻蔓延着。

然而这世间情感太多，小 R 也只能体会更开心和更难过。

**题目描述**

小 R 想对上面的问题进行探究，她想先做一些统计，于是她抽象了这个问题。

小 R 有 $n$ 个未知量 $a_1\dots a_n$，对每个 $1 \leq i < n$，她都比较了 $a_i$ 和 $a_{i+1}$ 并写下了一个字符 $c_i \in \{\texttt <, \texttt >, \texttt =\}$，表示两个未知量之间的比较结果。具体地：

- 若 $c_i = \texttt >$，则 $a_i > a_{i+1}$；
- 若 $c_i = \texttt <$，则 $a_i < a_{i+1}$；
- 否则（$c_i = \texttt =$），表示 $a_i = a_{i+1}$。

小 R 称 $\bm{a_i}$ **比** $\bm{a_j}$ **更开心**，当且仅当对任何 **满足上述 $\bm{n - 1}$ 条约束的** $[a_1, \dots, a_n] \in \mathbb R^n$，都有 $a_i < a_j$。请你帮她数出 $1 \leq i, j \leq n$ 且 $a_i$ 比 $a_j$ 更开心的整数数对 $(i, j)$ 个数。

因为要循环播放，所以有多组数据。

**输入格式**

**本题有多组数据。**

第一行，一个整数 $T$，表示数据组数。对于每组数据：

- 第一行一个整数 $n$。
- 接下来一行，一个长度为 $n - 1$ 的字符串 $c_1c_2\dots c_{n-1}$。

 输出格式

对于每组数据，输出仅一行一个整数，表示符合条件的整数数对个数。

 输入输出样例 1

 输入 1

```
5
5
<<<<
7
<=><=<
9
=<<><==<
11
>=<<=>>>=>
13
=><<=<=>=><>
```

 输出 1

```
10
9
13
29
25
```

**说明/提示**

**样例解释**

- 对于第一组数据，$a_i$ 比 $a_j$ 开心当且仅当 $1 \leq i < j \leq n$，故共有 $\frac{5\times 4}{2} = 10$ 对合法的 $(i, j)$。
- 对于第二组数据，合法的 $(i, j)$ 分别为：$(1, 2), (1, 3), (4, 2), (4, 3), (4, 5), (4, 6), (4, 7), (5, 7), (6, 7)$，共 $9$ 对。
- 对于其他几组数据，聪明的读者可以自行验证。

**数据规模与约定**

**本题采用捆绑测试和子任务依赖。**

- Subtask 0（0 pts）：样例。
- Subtask 1（10 pts）：$n \leq 8$，$T \leq 8$。
- Subtask 2（20 pts）：$n \leq 5000$，$T \leq 8$。依赖于子任务 $0, 1$。
- Subtask 3（20 pts）：$c_i \neq \texttt =$。
- Subtask 4（50 pts）：无特殊限制。依赖于子任务 $0 \sim 3$。

对于所有数据，保证 $2 \leq n \leq 2\times 10^5$，$1 \leq T \leq 10^4$，$c_i \in \{\texttt <, \texttt >, \texttt =\}$，$\sum n \leq 5\times 10^5$。


!!! : 本题在符号的处理上和先前的咕噜论坛很像，写好一个统一的函数，用数值来进行区分
!!! : 本题可以很容易发现单调性是围绕着大于号和小于号进行的。至于等于号则是重点要特判的地方。相比于一开始模拟倍数的想法，设满足单调增的序列数量为a， 满足单调减的区间数量为b， 中间有等号（即无论大于号还是小于号都跳出条件）的序列数量为c， a + b - 2 * c 即为答案（如何推?）

```cpp
#include <bits/stdc++.h>
using namespace std;

template < typename M, typename I, typename R, typename U>
void increaseEnumerate(int s, int e,
                      const M& match,
                      const I& insert,
                      const R& remove,
                      const U& update) {
for (int l = s, r = s; l <= e; ) {
    while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
    if (match(l, r - 1)) update(l, r - 2);
    else update(l, r - 1);
    remove(l ++, r);
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string str;
        cin >> str;
        auto func = [&](int v1, int v2) {
            vector<int> v(128);
            v['<'] = v1;
            v['>'] = v2;
            int sum = 0;
            long long total = 0;
            increaseEnumerate(0, n - 1,
                [&](int l, int r) { return sum < 0; },
                [&](int l, int r) { sum += v[str[r]]; },
                [&](int l, int r) { sum -= v[str[l]]; },
                [&](int l, int r) { total += r - l + 1; });
            return total;
        };
        cout << func(0, -1) + func(-1, 0) - func(-1, -1) * 2 << endl;
    }
    return 0;
}
```

## 4.14 First One
**题目描述**

soda 有一个整数数组 \( a_1, a_2, \ldots, a_n \)。令 \( S(i, j) \) 为 \( a_i, a{i+1}, \ldots, a_j \) 的和。现在 soda 想知道下面的值：

$\sum_{i=1}^{n} \sum_{j=i}^{n} \left( \lfloor \log_2 S(i, j) \rfloor + 1 \right) \times (i + j)$
注意：在这个问题中，你可以认为 \( \log_2 0 \) 为 0。

**输入**

有多个测试用例。输入的第一行包含一个整数 \( T \)，表示测试用例的数量。对于每个测试用例：

- 第一行包含一个整数 \( n \) \( (1 \leq n \leq 10^5) \)，表示数组中的整数数量。
- 第二行包含 \( n \) 个整数 \( a_1, a_2, \ldots, a_n \) \( (0 \leq a_i \leq 10^5) \)。

**输出**

对于每个测试用例，输出该值。

**示例输入**

```
1
2
1 1
```

**示例输出**

```
12
```

!!! : 对 S(i, j) 求 log 又取整数， 实际上会压缩数据的范围 (2, 4, 8, 16, 32 .....) 且越往后，间隔越大。 条件就是判断有无超出这些个点即可。

!!! : 朴素来说，我们希望的是让 (i + j) 乘上的始终是同一个数字，这样我们就可以直接用等差数列的公式求出来每个区段的答案。 同时， 又要对log有一定的数字敏感度， 知道其会压缩整个区间。

!!! : 两层循环， 实际上这是一个二维平面上的枚举， 想成一维上的滑动窗口你就会浪费一个小时 😦 所以说应该按照如下方式去枚举

!!! : md 数组里全是正数， 枚举过一次就好了 草

``` cpp
for i in [1, n]
    for k in [L, R]
    ( i * (R - L + 1) + (L + R) * (R - L + 1) / 2) * lg 
```
公式记得自己推哦

