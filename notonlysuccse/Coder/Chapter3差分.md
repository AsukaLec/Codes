[TOC]
# <center> 三、差分

## Lead In
<mark>快速处理区间加减</mark>
<mark>前缀和的逆运算</mark>
差分往往和前缀和同时出现

$$ 前缀和 \quad s_i =
\left \{
\begin{aligned}
&a_i, &i = 0\\
&a_i + a_{i - 1}, &i > 0
\end{aligned}
\right.
$$

$$ 差分 \quad d_i =
\left \{
\begin{aligned}
&a_i, &i = 0\\
&a_i - a_{i - 1}, &i > 0
\end{aligned}
\right.
$$

**实现方式**
``` cpp
for (int i = n - 1; i >= 0; i --) {
    if ( i == 0) d[i] = a[i];
    else d[i] = a[i] - a[i - 1];
}
//标准库
adjacent_difference(a.begin(), a.end(), d.begin());
```
**推论们**
**1. 前缀和 与 差分 互为逆运算**
```cpp 
1 1 1 1 1
//前缀和
1 2 3 4 5 
// 差分
1 1 1 1 1 //反之亦然
```
**2. $a[l,r] + k \Leftrightarrow d[l] + k, d[r+1] - k $**
``` cpp
 1  2  3  4  5    >> 差分  1   1   1   1   1  -5
+2 +2 +2 +2               +2          -2
 3  4  5  6  5             3   1   1   1  -1  -5  
   -6 -6 -6 -6                -6              +6
 3 -2 -1  0 -1    <<前置和  3  -5   1   1  -1   1  
时间复杂度 O(n * m)        时间复杂度 O(n + m)
```
**3. 二维差分**
``` cpp
//第一种 先对列进行差分 再对行进行差分
auto d = vector(n + 1, vector<int>(m + 1));
for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
        d[i][j] = a[i][j] - a[i - 1][j];
    }
    adjacent_difference(d[i].begin(), d[i].end(), d[i].begin());
}
```
```cpp
//第二种 d当前元素 减 左 减 上 加 左上
for (int i = m; i >= 1; i--) {
    for (int j = m; j >= 1l j--) {
        d[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1]; 
    }
}
```

快速区间加减 
<img src="photos\part 1 差分 1.png" width="100%" height="100%"> 

时间复杂度 $ O(n^2) \rightarrow O(1) $

**4.异或差分及乘法取模差分**
<img src="photos\part 1 差分 2.png" width="100%" height="100%"> 

**5. 有规律的累加 等价于 多重差分**
首先需要观察 两项之差的函数的最高次为几次：
朴素形式 $add_x = a + bx + cx^2 + dx^3 + ...$
经过 最高次 + 1 次差分 得到 一个 常数级的修改方案
<mark>注意 差分数组的项数 要多出差分次数个项</mark>
eg.
<img src="photos\part 1 差分 3.png" width="100%" height="100%"> 
<img src="photos\part 1 差分 4.png" width="100%" height="100%"> 
统一修改 $add_x = a $ 一次差分就够了
等差数列 $add_x = a + bx $ 两次差分
平方数列 $add_x = a + bx + cx^2 $ 三次差分
eg.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    
    vector <int> ans;

    for (int i = 1; i <= 6; ++i) {  
        ans.push_back(a * i * i * i + b * i * i + c * i + d);//更高此数也能实现， 系数问题
    }
    for (int i = 1; i <= 4; ++i) {  
        ans.push_back(0);
    }

    for (int i = 0; i < 10; i ++) {
            cout << ans[i] << ' ' ;    
    }
    cout << endl;

    while (true) {
        int k; 
        cin >> k;
        
        vector <int> ans1(10, 0);
        adjacent_difference(ans.begin(), ans.end(), ans1.begin());
        
        if (k >= 2) {
            while (k-- && k > 0) {
                adjacent_difference(ans1.begin(), ans1.end(), ans1.begin());
                }

            for (int i = 0; i < 10; i ++) {
                cout << ans1[i] << ' ' ;    
                }
            cout << endl;
        }
        else {
            for (int i = 0; i < 10; i ++) {
                cout << ans1[i] << ' ' ;    
                }
            cout << endl;
        }
        
    }
    return 0;
}

// 0 7 2 3
// 12 35 72 123 188 267 0 0 0 0
// 1
// 12 23 37 51 65 79 -267 0 0 0
// 2
// 12 11 14 14 14 14 -346 267 0 0
// 3
// 12 -1 3 0 0 0 -360 613 -267 0

// 1 3 2 5
// 11 29 65 125 215 341 0 0 0 0
// 1
// 11 18 36 60 90 126 -341 0 0 0
// 2
// 11 7 18 24 30 36 -467 341 0 0
// 3
// 11 -4 11 6 6 6 -503 808 -341 0
// 4
// 11 -15 15 -5 0 0 -509 1311 -1149 341
```
<mark>所以啊， 对于一组看似无规律的数据 对它使用差分吧 规律可能蕴含在高维空间中</mark>


**6. 差分数组的正负性可以反映原数组的增减性**
<img src="photos\part 1 差分 5.png" width="100%" height="100%"> 
eg.
给定一个数组和目标数组 对数组内任意区间进行加一或减一的操作 问需要多少次操作才能把原数组变为目标数组
<img src="photos\part 1 差分 6.png" width="50%" height="100%"> 
<img src="photos\part 1 差分 7.png" width="100%" height="100%"> 
答案是整数总和和负数总和的绝对值取两者最大值
***

## 3.1 P9094 差分模板
**题目描述**
Byteasar 正准备给栅栏涂漆。他已经准备了 $n$ 罐白色油漆，他把这些油漆排列成一排，从 $1$ 到 $n$ 编号。他想用这些油漆，但他不想把栅栏涂成白色。他委托了调色专家，调色专家有三种颜料：黄色、蓝色和红色。专家进行了 $m$ 次操作，其中第 $i$ 次操作是向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的所有罐子中加入某种颜料。

油漆的最终颜色取决于被添加到其中的颜料。添加的颜料按照下表和图示进行混合。

|        颜料        | 颜色 |
| :----------------: | :--: |
|         无         | 白色 |
|        黄色        | 黄色 |
|        蓝色        | 蓝色 |
|        红色        | 红色 |
|    黄色 + 蓝色     | 绿色 |
|    黄色 + 红色     | 橙色 |
|    蓝色 + 红色     | 紫色 |
| 黄色 + 蓝色 + 红色 | 棕色 |

![](https://cdn.luogu.com.cn/upload/image_hosting/zow92g6w.png)

Byteasar 想要给栅栏涂成一种颜色。思来想去，他选择了绿色，因为绿色代表了你常会在算法竞赛中看到的 Accepted。他想知道现在有多少罐油漆是绿色的，请帮他数数。

**输入格式**

第一行两个整数 $n,m$，分别表示油漆的罐数和专家进行的操作数。

接下来 $m$ 行，每行三个整数 $l_i,r_i,k_i$，表示在第 $i$ 次操作中向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的罐子中加入颜料。加入的颜料是黄色（$k_i=1$），蓝色（$k_i=2$）或红色（$k_i=3$）中的一种。

**输出格式**

输出一行一个整数，表示在所有操作之后绿色油漆的罐数。

**输入输出样例 #1**
**输入 #1**

```
9 5
2 8 1
4 5 2
6 7 3
5 6 2
1 2 2
```
**输出 #1**

```
3
```

**样例 1 解释**

操作结束后，这些油漆分别是蓝色、绿色、黄色、绿色、绿色、棕色、橙色、黄色和白色的。因此，只有三罐油漆是绿色。

**数据范围**
对于 $100\%$ 的数据，保证 $1\le n,m\le 10^6$，$1\le l_i\le r_i\le n$，$1\le k_i\le 3$。

!!! : 二编： 本体符合 “快速对一个区间内的数进行加减运算”的特征，故需用到差分 

!!! : 本题用到的是推论二，若按题意暴力枚举判断会导致时间复杂度过高， 用差分可把修改的过程改为 $O(1) $

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    auto colors = vector(3, vector<int>(n + 2));
    while(m -- ) {
        int l, r, c;
        cin >> l >> r >> c;
        colors[c - 1][l] ++;
        colors[c - 1][r + 1] --;
    }
    for (auto &color : colors ) {
        partial_sum(color.begin(), color.end(), color.begin());
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (colors[0][i] && colors[1][i] && !colors[2][i]) ans ++;
    }
    cout << ans;
}
```

---

## 3.2 lq 3533 棋盘 二维差分模板
**问题描述**
小蓝拥有 $ n×n $ 大小的棋盘，一开始棋盘上全都是白子。小蓝进行了$m$ 次操作，每次操作会将棋盘上某个范围内的所有棋子的颜色取反（也就是白色棋子变为黑色，黑色棋子变为白色）。请输出所有操作做完后棋盘上每个棋子的颜色。

**输入格式**
输入的第一行包含两个整数 n，m，用一个空格分隔，表示棋盘大小与操作数。
接下来 m 行每行包含四个整数 
$x_1, y_1, x_2, y_2$
 ，相邻整数之间使用一个空格分隔，表示将在
$x_1 $至 $x_2 $行,$ y_1 $至 $y_2$列中的棋子颜色取反。

**输出格式**
输出 n 行，每行 
n 个 0 或 1 表示该位置棋子的颜色。如果是白色则输出 0，否则输出 1。

**样例输入**
```
3 3
1 1 2 2
2 2 3 3
1 1 3 3
```
**样例输出**
```
001
010
100
```
**评测用例规模与约定**
对于 30% 的评测用例， $n,m \leqslant 50$
对于 所有评测用例， $1 \leqslant n,m \leqslant 2000, 1 \leqslant x_1 \leqslant x_2 \leqslant n, 1 \leqslant y_1 \leqslant y_2 \leqslant m $

!!! : <img src="photos\part 1 差分 1.png" width="100%" height="100%">每次翻转为原来的数组都加上1， 最后判断奇偶即可判断正反。

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    auto maze = vector(n + 2, vector(n + 2, 0));
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        maze[x1][y1]++;
        maze[x1][y2+1]--;
        maze[x2+1][y1]--;
        maze[x2+1][y2+1]++;
    }//见上图

    for (int i = 1; i <= n; i++ ) {
        partial_sum(maze[i].begin(), maze[i].end(), maze[i].begin());//形式一
        for (int j = 1; j <= n; j ++) {
            maze[i][j] += maze[i -1][j];//形式二
            cout << (maze[i][j] & 1);//快速判断奇偶性， 至于为什么是奇偶，前面每次操作加的都是一
        }
        cout << endl;
    }
}

```
---

## 3.3 lq 2128 重新排序  关注如何对区间进行排序以及匹配
**问题描述**
给定一个数组 $A$ 和一些查询 $L_i, R_i$, 求数组中第$L_i$ 至第 $R_i$ 个元素之和。
小蓝觉得这个问题很无聊, 于是他想重新排列一下数组, 使得最终每个查 询结果的和尽可能地大。小蓝想知道相比原数组, 所有查询结果的总和最多可以增加多少?

**输入格式**
输入第一行包含一个整数 n 。
第二行包含 n 个整数 $A_1,A_2,⋯,A_n​$, 相邻两个整数之间用一个空格分隔。
第三行包含一个整数 m 表示查询的数目。
接下来 m 行, 每行包含两个整数 $L_i、R_i$, 相邻两个整数之间用一个空格分 隔。

**输出格式**
输出一行包含一个整数表示答案。

**样例输入**
```
5
1 2 3 4 5
2
1 3
2 5
```

**样例输出**
```
4
```

**样例说明**
原来的和为 6+14=20, 重新排列为 (1,4,5,2,3) 后和为 10+14=24, 增 加了 4。

!!! ： 初始思路：先对原数组进行排序。某个位置重复计算的次数越多，就给这个位置填上尽可能大的数(<mark>主要优化点</mark>)。 计算某个位置的重复计算次数， 先进行m次差分， 最后进行一次前缀和。
!!! : 正确思路 :前半部分相同， 填数字的地方， 对目标数组也进行排序，然后和排好序的原数组一一相乘即可 。 至于怎么求没排序前的和， 输入的时候顺手用前缀和运算即可。

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n;
    vector<long long > a(n);
    for (auto & x : a) cin >> x;
    vector<long long > sum (n + 1);
    partial_sum(a.begin(), a.end(), sum.begin() + 1);

    cin >> m;
    long long total = 0; //未排序前的区间和
    vector<long long> diff (n + 2);
    while (m--) {
        int l, r;
        cin >> l >> r;

        diff[l] ++;
        diff [r + 1]--;

        total += sum[r] - sum[l - 1];
    }
    partial_sum(diff.begin(), diff.end(), diff.begin());
    sort(diff.begin(), diff.end(), greater<long long>());
    //当传入greater<T>时，会按**降序（从大到小）**排列元素。
    //若未指定第三个参数，默认行为相当于传递了 less<T>()，结果为升序。
    sort(a.begin(), a.end(), greater<long long>());

    long long ans = 0;
    for (int i = 0; i < n; i ++) {
        ans += a[i] * diff[i];
    }
    cout << ans - total << endl;  
}
```
---

## 3.4 lq 197716 商品库存管理 范围函数快速输入， 数字特征， partial_sum函数的花活

**问题描述**
在库存管理系统中，跟踪和调节商品库存量是关键任务之一。小蓝经营的仓库中存有多种商品，这些商品根据类别和规格被有序地分类并编号，编号范围从 \(\mathbf{1}\) 至 \(\mathbf{n}\) 。初始时，每种商品的库存量均为 \(\mathbf{0}\) 。
为了高效地监控和调整库存量，小蓝的管理团队设计了 \(\mathbf{m}\) 个操作，每个操作涉及到一个特定的商品区间，即一段连续的商品编号范围（例如区间 \(\mathbf{[L, R]}\) ）。执行这些操作时，区间内每种商品的库存量都将增加 \(\mathbf{1}\) 。然而，在某些情况下，管理团队可能会决定不执行某些操作，使得这些操作涉及的商品区间内的库存量不会发生改变，维持原有的状态。
现在，管理团队需要一个评估机制，来确定如果某个操作未被执行，那么最终会有多少种商品的库存量为 \(\mathbf{0}\) 。对此，请你为管理团队计算出，每个操作未执行时，库存量为 \(\mathbf{0}\) 的商品的种类数。

**输入格式**
第一行包含两个整数 \(\mathbf{n}\) 和 \(\mathbf{m}\) ，分别表示商品的种类数和操作的个数。
接下来的 \(\mathbf{m}\) 行，每行包含两个整数 \(\mathbf{L}\) 和 \(\mathbf{R}\) ，表示一个操作涉及的商品区间。

**输出格式**
输出共 \(\mathbf{m}\) 行，每行一个整数，第 \(\mathbf{i}\) 行的整数表示如果不执行第 \(\mathbf{i}\) 个操作，则最终库存量为 \(\mathbf{0}\) 的商品种类数。

**样例输入**
```
5 3
1 2
2 4
3 5
```
**样例输出**
```
1
0
1
```

**样例说明**
考虑不执行每个操作时，其余操作对商品库存的综合影响：
- 不执行操作 1：剩余的操作是操作 2（影响区间 \(\mathbf{[2, 4]}\)）和操作 3（影响区间 \(\mathbf{[3, 5]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[0, 1, 2, 2, 1]}\)。在这种情况下，只有编号为 \(\mathbf{1}\) 的商品的库存量为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{1}\)。
- 不执行操作 2：剩余的操作是操作 1（影响区间 \(\mathbf{[1, 2]}\)）和操作 3（影响区间 \(\mathbf{[3, 5]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[1, 1, 1, 1]}\)。在这种情况下，所有商品的库存量都不为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{0}\)。
- 不执行操作 3：剩余的操作是操作 1（影响区间 \(\mathbf{[1, 2]}\)）和操作 2（影响区间 \(\mathbf{[2, 4]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[1, 2, 1, 0]}\)。在这种情况下，只有编号为 \(\mathbf{5}\) 的商品的库存量为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{1}\)。

**评测用例规模与约定**
对于 \(\mathbf{20\%}\) 的评测用例，\(\mathbf{1 \leq n, m \leq 5 \times 10^3}\)，\(\mathbf{1 \leq L \leq R \leq n}\)。
对于所有评测用例，\(\mathbf{1 \leq n, m \leq 3 \times 10^5}\)，\(\mathbf{1 \leq L \leq R \leq n}\)。

!!! : 看到 “都加一” 明显差分。 关键在于，每个不执行操作如何实现。 假设所有操作次数为 $k$ ，得到相应的差分数组后，对于第 $i$ 次操作， 在对应的区间加上 -$1$ 即可。但这样时间复杂度为 $O(n*m)$, 需优化。

!!! : 观察数字特征。 对于任意操作过的区间， 其前缀和之后的值一定是大于0的。若要不操作某个区间使得某个位置的库存变为0， 那么该位置的值在进行全部操作后必定为1。 所以只需要在目标区间统计值为 1 的个数即可。同时， 不能排除剩余区间有 0 存在的情况， 故须在进行过所有操作的数组中先统计一遍 0 的个数。 又因为若某个区间经历了操作， 其不可能为0，所以可以放心不会出现重复。

!!! : partial_sum函数的用法关注一下
``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> range (m);
    vector<long long> cnt(n + 2);
    for (auto &[f, s] : range ) {
        cin >> f >> s;
        cnt[f] ++;
        cnt[s + 1] --;
    }//范围循环快速输入
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    vector<int> ones(n + 2);
    int zero = 0;
    partial_sum(cnt.begin(), cnt.end() - 1, ones.begin(), [&](int prev, int cur) {
        if (cur == 0) zero ++;
        if (cur == 1) return prev + 1;
        return prev;
    });// cnt.end() - 1: 最后一个位置不需要计数。
    //这个函数用for 循环也是能写的。
    // prev cur 都是partial_sum这个函数下的一个参数位置， 分别代表前一次累加返回的值以及当前要处理的值。
    //return 的即是要存到 ones这个前缀和数组特定位置的值
    for (auto &[f, s] : range) {
        cout << ones[s] - ones[f - 1] + zero << endl;
    }
}
```

---

## 3.5 经典题
<img src="photos\part 1 3.5 题目.png" width="100%" height="100%">

!!! : 初始想法： 先不管矩阵 0 1的分布， 暴力往上放尽可能多的邮票，然后从中抽取任意张邮票直至满足条件。 这个就有点像 3.4 只不过一次 的 不操作改成了任意次的不操作
!!! : 优化： 优化放邮票的策略。 先对原矩阵进行一次二维前缀和， 然后放邮票之前， 先判断该区间内有无 被占据的格子， 顺便差分 把可以放的格子加一， 最后再来一次前缀和统计是不是所有空格子都被占据了。
``` cpp
#include <bitsa/stdc++.h>
using namespace std;
int main() {
    int h, w;
    int grid[n][m];
    auto sum = vector (n + 2, vector(m + 2, 0));
    for (int i = 0; i <   n; i++) {
        partial_sum(grid[i].begin(), grid.end(), sum[i + 1].begin() + 1);
        for (int j = 1; j <= m; j ++) {
            sum[i + 1][j] += sum[i][j];

        }
    }
    // 注意坐标偏移
    
    auto diff = vector (n + 2, vector(m + 2, 0));
    for (int i = 0; i + h <= n; i ++) {
        for (int j = 0; j + w <= m; j ++ ) {
            int v = sum [i + h][j + w] - sum[i + h][j] - sum[i][j + w] + sum[i][j];
            if (v == 0) {
                diff [i + 1][j + 1] ++;
                diff [i + 1][j + w + 1] --;
                diff [i + h + 1][j + 1] --;
                diff [i + h + 1][j + w + 1] ++;

            }
        }
    }
    for (int i =0; i < diff.size(); i ++ ) {
        partial_sum(diff[i].begin(), diff[i].end(), diff[i].begin());
        for(int j = 0; j < diff[i].size(); j ++) { 
            if (i) diff[i][j] += diff [i - 1][j];
        }
    }//处理

    //判断是否成立
    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < m; j ++ ) {
            if (grid[i][j] == 0 && diff[i + 1][j + 1] == 0) return false;
        }
    }
    return true;
}
```
---

## 3.6 P4231 三步必杀 推论5 有规律的累加
**题目描述**
$N$ 个柱子排成一排，一开始每个柱子损伤度为 $0$。
接下来勇仪会进行 $M$ 次攻击，每次攻击可以用 $4$ 个参数 $l,r,s,e$ 来描述：
表示这次攻击作用范围为第 $l$ 个到第 $r$ 个之间所有的柱子(包含 $l,r$)，对第一个柱子的伤害为 $s$，对最后一个柱子的伤害为 $e$。
攻击产生的伤害值是一个等差数列。若 $l=1,r=5,s=2,e=10$，则对第 $1 \sim 5$ 个柱子分别产生 $2,4,6,8,10$ 的伤害。
鬼族们需要的是所有攻击完成之后每个柱子的损伤度。

**输入格式**
第一行 $2$ 个整数 $N,M$，用空格隔开，下同。
接下来 $M$ 行，每行4个整数 $l,r,s,e$，含义见题目描述。
数据保证对每个柱子产生的每次伤害值都是整数。

**输出格式**
由于输出数据可能过大无法全部输出，为了确保你真的能维护所有柱子的损伤度，只要输出它们的异或和与最大值即可。
（异或和就是所有数字按位异或起来的值。）
（异或运算符在 c++ 里为 `^`。）

**输入输出样例 #1**

**输入 #1**

```
5 2
1 5 2 10
2 4 1 1
```
**输出 #1**

```
3 10
```

** 输入输出样例 #2**

** 输入 #2**

```
6 2
1 5 2 10
2 4 1 1
```

**输出 #2**

```
3 10
```

**说明/提示**

**样例解释：**

样例 $1$：

第一次攻击产生的伤害：$2,4,6,8,10$。

第二次攻击产生的伤害：$0,1,1,1,0$。

所有攻击结束后每个柱子的损伤程度：$2,5,7,9,10$。

输出异或和与最大值，就是 $3,10$。

样例 $2$：

没有打到第六根柱子，答案不变

**数据范围：**

本题满分为 $100$ 分，下面是 $4$ 个子任务。(x/y)表示(得分/测试点数量)。

妖精级(18/3)：$1 \  n,m \le 1000$。这种工作即使像妖精一样玩玩闹闹也能完成吧？

河童级(10/1)：$s=e$，这可以代替我工作吗？

天狗级(20/4)：$1 \le n,m \le 10^5$。小打小闹不再可行了呢。

鬼神级(52/2)：没有特殊限制。要真正开始思考了。

以上四部分数据不相交。

对于全部的数据：$1\le n\le 10^7$，$1\le m\le 3\times 10^5$，$1\le l < r \le n$.

所有输入输出数据以及柱子受损伤程度始终在 $[0,9 \times 10^{18}]$ 范围内。

**提示：**

由于种种原因，时间限制可能会比较紧，c++ 选手请不要使用 `cin` 读入数据。

by orangebird。

!!! : 等差数列很容易联想到推论五， 至于题目中的异或和和最大值用系统库函数即可。
``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> diff(n + 3);
    while (m --) {
        int l, r, s, e;
        cin >> l >> r >> s >> e;
        int d = (e - s) / (r - l);
        diff[l] += s;
        diff[l + 1] += d - s;
        diff[r + 1] -= e + d;
        diff[r +2] += e;
    }
    partial_sum(diff.begin(), diff.end(), diff.begin());
    partial_sum(diff.begin(), diff.end(), diff.begin());

    cout << accumulate(diff.begin(), diff.end(), 0ll, [](long long prev, long long cur) {return prev ^ cur; });
    //求和函数 匿名函数
    cout << ' ' << *max_element(diff.begin(), diff.end());

}
```
---

## 3.7 P10266 高效清理 有规律累加 三次差分 二维矩阵分对角线处理 样例题
 
**题目描述**
真寻的房间太大了，但是作为家里蹲，她又懒得打扫，于是美波里发明了一款清理炸弹给真寻使用。

真寻的房间由 $n$ 行 $m$ 列的方砖组成，第 $i$ 行第 $j$ 列的方砖上的灰尘数量为 $a_{i,j}$。

真寻将会使用 $k$ 次清理炸弹，第 $i$ 次她会在第 $x_i$ 行第 $y_i$ 列的方砖上使用能量值为 $p_i$ 的清理炸弹，这将会使 $(x_i,y_i)$ 的灰尘数量减少 ${p_i}^2$，$(x_i,y_i)$ 外围第一圈的方砖上的灰尘数量减少 $(p_i-1)^2$，外围第二圈的方砖上的灰尘数量减少 $(p_i-2)^2$ $\cdots$ 外围第 $(p_i-1)$ 圈的方砖上的灰尘数量减少 $1$。

当然，灰尘数量不能为负数，所以若某次操作前，某块方砖上的灰尘数量小于它将要减少的灰尘数量，那么它的灰尘数量将变为 $0$。

请你输出真寻使用完 $k$ 次清理炸弹后，每块方砖上的灰尘数量。

**输入格式**
第一行三个整数 $n,m,k$，分别表示方砖行数、列数及操作次数；

接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示 $a_{i,j}$，描述每一块方砖上的灰尘数量；

接下来 $k$ 行，第 $i$ 行三个整数 $x_i,y_i,p_i$，描述一次操作。

**输出格式**
共 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示方砖 $(i,j)$ 上最终的灰尘数量。


**输入输出样例 #1**

**输入 #1**
```
4 5 2
7 5 4 6 5
2 4 7 9 5
6 4 5 3 5
1 2 3 0 7
2 4 2
3 3 2
```

**输出 #1**
```
7 5 3 5 4
2 3 5 4 4
6 3 0 1 4
1 1 2 0 7
```

**输入输出样例 #2**
**输入 #2**
```
6 7 3
6 4 7 8 4 6 1
4 5 4 6 7 5 9
1 4 3 0 7 1 3
4 6 0 7 9 0 0
1 2 3 4 4 5 8
4 7 6 8 7 4 9
5 5 3
2 3 4
3 6 2
```

**输出 #2**

```
2 0 0 0 0 5 1 
0 0 0 0 2 3 8 
0 0 0 0 1 0 1 
0 2 0 0 0 0 0 
0 1 1 0 0 0 7 
4 7 5 4 3 0 8
```

**说明/提示**

**样例** $\mathbf{1}$ **解释**

第一次操作在方砖 $(2,4)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(2,4)$ 的灰尘数量减少 $4$，$(1,3),(1,4),(1,5),(2,3),(2,5),(3,3),(3,4),(3,5)$ 的灰尘数量减少 $1$；

第二次操作在方砖 $(3,3)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(3,3)$ 的灰尘数量减少 $4$，$(2,2),(2,3),(2,4),(3,2),(3,4),(4,2),(4,3),(4,4)$ 的灰尘数量减少 $1$。

**数据范围**

对于所有数据，$1\leq n,m,p_i\leq 10^3$，$1\leq k\leq 10^6$，$0\leq a_{i,j}\leq 10^{12}$，$1\leq x_i\leq n$，$1\leq y_i\leq m$。

本题共 $11$ 个数据点，**采用捆绑测试**，子任务及数据点分配如下：

| 子任务编号 | 数据点编号 | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $0$ | $1\sim 4$ | $n,m,k\leq 300$ | $10$ |
| $1$ | $5$ | $p_i\leq 3$ | $10$ |
| $2$ | $6\sim 7$ | $k\leq 10^3$ | $20$ |
| $3$ | $8\sim 9$ | $n,m\leq 300$ | $20$ |
| $4$ | $10\sim 11$ | 无特殊限制 | $40$ |

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios :: sync_with_stdio(false);
    //解绑 scanf 缩短时间
    cin.tie(0);

    const int N = 3000 + 10;
    int offset = 1000 +5;

    int n, m, k;
    cin >> n >> m >> k;

    auto origin = vector(n, vector<long long> (m));
    for (auto & row : origin) {
        for (auto & x : row) cin >> x;
    }//输入   

    //对角线分割
    auto diag = vector(N, vector<long long> (N));
    auto back_diag = vector(N, vector<long long> (N));

    while (k --) {
        int x, y, p;
        cin >> x >> y >>p;
        x += offset;
        y += offset;

        diag[x+1][y+1] -= 2;
        diag[x+2][y+2] -= 2;
        diag[x-p+1][y-p+1] += 1;
        diag[x-p+2][y-p+2] += 1;
        diag[x+p+1][y+p+1] += 1;
        diag[x+p+2] [y+p+2]+= 1;

        back_diag[x+1][y] += 2;
        back_diag[x+2][y - 1] += 2;
        back_diag[x+1+p][y-p] -= 1;
        back_diag[x+2+p][y-p-1] -= 1;
        back_diag[x+1-p][y+p] -= 1;
        back_diag[x+2-p][y+p-1] -= 1;
        // 0 0 0 0 0 0 0 0 0 
        // 0 1 1 1 1 1 1 1 0
        // 0 1 4 4 4 4 4 1 0
        // 0 1 4 9 9 9 4 1 0
        // 0 1 4 9 16 9 4 1 0 **y
        // 0 1 4 9 9 9 4 1 0
        // 0 1 4 4 4 4 4 1 0
        // 0 1 1 1 1 1 1 1 0
        // 0 0 0 0 0 0 0 0 0
        //         *x
        // 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0
        // 0 0 3 0 0 0 0 0 0
        // 0 0 0 5 0 0 0 0 0
        // 0 0 0 0 7 0 0 0 0 **y
        // 0 0 0 0 0 7 0 0 0
        // 0 0 0 0 0 0 5 0 0
        // 0 0 0 0 0 0 0 3 0
        // 0 0 0 0 0 0 0 0 1
        //         *x
        // 0 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0 0
        // 0 0 2 0 0 0 0 0 0 0
        // 0 0 0 2 0 0 0 0 0 0
        // 0 0 0 0 2 0 0 0 0 0**y
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 -2 0 0 0
        // 0 0 0 0 0 0 0 -2 0 0
        // 0 0 0 0 0 0 0 0 -2 0
        // 0 0 0 0 0 0 0 0 0 -1
        //         *x
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0 0 0
        // 0 0 1 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0**y
        // 0 0 0 0 0 -2 0 0 0 0 0
        // 0 0 0 0 0 0 -2 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 1 0
        // 0 0 0 0 0 0 0 0 0 0 1
        //         *x
    }

    //两个差分函数 特例化
    auto diag_sum = [&](auto &diag) {
        for (int i = 1; i < diag.size(); i ++) {
            for (int j = 1; j < diag.size(); j ++) {
                diag[i][j] += diag[i - 1][j - 1];
            }
        }
    };

    auto back_diag_sum = [&](auto &diback_diagag) {
        for (int i = 1; i < back_diag.size(); i ++) {
            for (int j = back_diag.size() - 1; j > 0; j --) {
                back_diag[i][j] += back_diag[i - 1][j + 1];
            }
        }
    };

    //平方数列 两次调用
    diag_sum(diag);
    diag_sum(diag);
    back_diag_sum(back_diag);
    back_diag_sum(back_diag);

    auto total = vector(N, vector(N, 0ll));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            total[i][j] = diag[i][j] + back_diag[i][j];
        }
    }

    for (int i = 0; i < N; i ++) {
        partial_sum(total[i].begin(),total[i].end(), total[i].begin());
        for (int j = 0; j < N; j ++) {
            total[i][j] = total[i - 1][j];
        }
    }

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            origin[i][j] -= total[i + 1 + offset][j + 1 + offset];
            if (origin[i][j] < 0) origin[i][j] = 0;
            cout << origin[i][j] << ' ';
        }
        cout << endl;
    }
}
```

## 3.8 P4552 [Poetize6] IncDec Sequence 经典题 推论六

**题目描述**

给定一个长度为 $n$ 的数列 ${a_1,a_2,\cdots,a_n}$，每次可以选择一个区间$[l,r]$，使这个区间内的数都加 $1$ 或者都减 $1$。 
  
请问至少需要多少次操作才能使数列中的所有数都一样，并求出在保证最少次数的前提下，最终得到的数列有多少种。

**输入格式**

第一行一个正整数 $n$   
接下来 $n$ 行,每行一个整数,第 $i+1 $行的整数表示 $a_i$。

**输出格式**

第一行输出最少操作次数   
第二行输出最终能得到多少种结果

**输入输出样例 #1**

**输入 #1**

```
4
1
1
2
2
```

**输出 #1**

```
1
2
```

**说明/提示**

对于 $100\%$ 的数据，$n\le 100000, 0 \le a_i \le 2^{31}$。

!!! : 第一版： 前半部分是对的， 第二部分错误

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int k;
    cin >> k;
    vector <int> maze;
    for (int i = 0; i < k; i ++) {
        long long a;
        cin >> a;
        maze.push_back(a);
    }

    auto max_val = *max_element(maze.begin() + 1, maze.end());
    auto min_val = *min_element(maze.begin() + 1, maze.end());


    adjacent_difference(maze.begin(), maze.end(), maze.begin());

    long long pos = 0, neg = 0;

    for (int i = 1; i < k; i ++) {
        if (maze[i] > 0) pos += maze[i];
        else neg  += - maze[i];
    }


    long long op = max(pos, neg);
    long long posible =  (min_val + op) - (max_val - op) + 1;

    cout << op << endl;
    cout << posible << endl;
}
```

!!! :第二部分实际上要处理的应该是差分数组除去第一位， 正数之和减去负数之和的绝对值再加 1， 原理见下, 所有的差分数组通过加减都能化为以下的形式“1”。

``` cpp
[1, 1, 2, 2]
[x, 0, 1, 0, x]
[1,   -1]
      [1    -1]

```
!!! : AC版

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int k;
    cin >> k;
    vector <int> maze;
    // for (int i = 0; i < k; i ++) {
    //     long long a;
    //     cin >> a;
    //     maze.push_back(a);
    // }
    for (auto & x : maze) cin >> x;

    adjacent_difference(maze.begin(), maze.end(), maze.begin());

    long long pos = 0, neg = 0;

    for (auto & x : maze) {
        if (x > 0) pos += x;
        else neg  += - x;
    }

    long long posible =  abs(pos + neg) + 1;

    cout << max(pos, neg) << endl;
    cout << posible << endl;
}
```
---

## 3.9 P6070 『MdOI R1』Decrease 推论 6 二维化

**题目描述**

给定一个 $n \times n$ 的矩阵，你可以进行若干次操作。

每次操作，你可以将一个 $k \times k$ 的 **连续** 子矩阵里的所有数全都加上 $1$ 或者全都减去 $1$。

初始时，矩阵中有 $m$ 个位置上的数不为 $0$，其它位置上的数均为 $0$。

请你求出至少需要多少次操作，可以将矩形中所有数都变为 $0$。

**输入格式**

第一行三个整数 $n,m,k$，分别表示矩阵大小，非 $0$ 格数和每次修改的连续子矩阵大小。

接下来 $m$ 行，每行三个整数 $x,y,z$，表示初始时矩阵的第 $x$ 行第 $y$ 列上的数为 $z$。

**输出格式**

一行一个整数，表示最少操作次数。

特别地，如果无法使矩阵中所有数都变为 $0$，输出 `-1`。

**输入输出样例 1**

**输入 1**

```
4 14 3
1 1 1
1 2 1
1 3 1
2 1 1
2 2 3
2 3 3
2 4 2
3 1 1
3 2 3
3 3 3
3 4 2
4 2 2
4 3 2
4 4 2
```

**输出 1**

```
3
```

**输入输出样例 2**

**输入 2**

```
3 1 2
1 1 1
```

**输出 2**

```
-1
```

**输入输出样例 3**

**输入 3**

```
4 5 1
1 1 5
2 2 -3
2 3 -4
3 3 1
4 4 2
```
**输出 3**

```
15
```

**说明/提示**

【样例 1 解释】:  

给出的矩阵为：  

```plain
1 1 1 0
1 3 3 2
1 3 3 2
0 2 2 2
```

具体步骤：  

先将以第一行第一列为左上角的连续子矩阵执行 **减 1 操作** 一次；

再将以第二行第二列为左上角的连续子矩阵执行 **减 1 操作** 两次。

总共三次。

```plain
1 1 1 0  0 0 0 0  0 0 0 0  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
0 2 2 2  0 2 2 2  0 1 1 1  0 0 0 0
```

【样例 2 解释】：  

给出的矩阵为：  

```plain
1 0 0
0 0 0
0 0 0
```

只通过 $2\times 2$ 的连续子矩阵操作不可能使得所有格子上的数都变为 $0$。

【数据范围】   

**本题采用捆绑测试。**

| 子任务编号 |    $n\leq$     | $k\leq$ | 分值 |
| :--------: | :------------: | :-----: | :--: |
|     1      |     $10^3$     |   $1$   |  11  |
|     2      |      $20$      |  $20$   |  14  |
|     3      |     $100$      |  $100$  |  17  |
|     4      |     $10^3$     | $10^3$  |  34  |
|     5      | $5\times 10^3$ | $10^3$  |  24  |

对于所有数据，$1\leq n\leq 5\times 10^3$，$1\leq m\leq \min(n^2,5\times 10^5)$，$1\leq k\leq \min(n,10^3)$，$1\leq x,y\leq n$，每对 $(x,y)$ 至多出现一次，$1 \le |z| \leq 10^9$。

数据保证如果有解，答案不超过 $2^{63}-1$。

---

【提示】

本题读入量较大，建议使用较快的读入方式。

!!! : 第一版AC :思路比较复杂。先用一个符合条件的数组画图检验， 发现逆推的话符合条件的矩阵应该是用大小为 k 的矩阵一个个累加起来的。 而矩阵的累加刚好在差分数组里有性质。 因此只需要遍历整个差分数组（画图注意边界）， 发现有不等于 0 的位置就把其在差分数组中的相应的 四个格点 变为 0 (这里不能直接变为0， 要自增或者自减， 因为下一步的判断会用到每个位置的数值)， 同时把数值记录下来，最后再遍历一次数组， 如果是符合要求的数组的话最后用一定是全为0的， 判断即可。

下为 样例1的差分数组
``` plain
0 0 0 0 0 0
0 1 0 0 -1 0
0 0 2 0 0 -2
0 0 0 0 0 0
0 -1 0 0 1 0
0 0 -2 0 0 2
```

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, t;
    cin >> n >> m >> t;
    auto maze = vector(n + 2, vector<long long> (n + 2, 0));
    auto ans = vector(n + 2, vector<long long> (n + 2, 0));
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        maze[x ][y] += z;
    }
    
    for (int i = 1; i <= n + 1; i ++) {
        for (int k = 1; k <= n + 1 ; k ++) {
            ans[i][k] += maze[i][k] + maze[i - 1][k - 1] - maze[i - 1][k] - maze[i][k - 1];
        }
    }

    // for (int i = 0; i <= n + 1; i ++) {
    //     for (int k = 0; k <= n + 1; k ++) {
    //         cout << ans[i][k] << ' ';
            
    //     }
    //     cout << endl;
    // }

    long long total = 0;
    for (int i = 0; i <= n + 1 - t; i ++) {
        for (int k = 0; k <= n + 1 -t ; k ++) {
            if (ans[i][k] != 0) {
                total += abs(ans[i][k]);
                
                ans[i][k + t] += ans[i][k];
                ans[i + t][k] += ans[i][k];
                ans[i + t][k + t] -= ans[i][k];
                ans[i][k] -= ans[i][k];
            }
            
        }
    }

    for (int i = 0; i <= n + 1; i ++) {
        for (int k = 0; k <= n + 1 ; k ++) {
            if (ans[i][k] != 0) {
                cout << -1 << endl;
                return 0;
            }
            
        }
    }
    cout << total << endl;
    return 0;
}

```

!!! : 老师的思路：简单点~ 注意逆序差分

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    auto maze = vector(n + 1, vector<long long> (n + 1, 0));

    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        maze[x - 1][y - 1] += z;
    }
    
    for (int i = n; i >= 0; i --) {
        for (int k = n; k >= 0 ; k --) {
            if  (i) maze[i][j] -= maze[i - 1][j];
        }
    }
    adjacent_difference(maze[i].begin(), maze[i].end(), maze[i].begin());

    long long total = 0;

    for (int i = 0; i < n; i ++) {
        for (int k = 0; k < n; k ++) {
            if (ans[i][k]) {
                if(i + k > n || j + k > n) {
                    cout << - 1 << endl;
                    return 0;
                }
                
                total += abs(ans[i][k]);
                
                ans[i][k + t] += ans[i][k];
                ans[i + t][k] += ans[i][k];
                ans[i + t][k + t] -= ans[i][k];
                ans[i][k] -= ans[i][k];
            }
            
        }
    }

    cout << total << endl;
    return 0;
}

```
---


## 3.10  P7404 [JOI 2021 Final] 有趣的家庭菜园 4 / Growing Vegetables is Fun 4

**题目描述**
给定一个长为 $ N $的序列$ A_i $，你可以进行若干次操作：
- 选定一个区间$ [L,R] $，让这个区间里的数加$1$。
设经过这若干次操作后的序列为$ B_i $，那么你需要让$ B_i $满足下面这个要求：
- 存在一个整数$ k\in[1,N] $，满足对于子序列 $A_1= \{ B_1,B_2, \cdots,B_k \} $ 为严格递增序列，对于子序列 $ A_2 =\{ B_k,B_{k+1},\cdots,B_N\}$ 为严格递减序列。

你想知道最少需要多少次操作才能满足上面这个要求。

**输入格式**
第一行一个整数 $ N $ 代表序列长度。
第二行 $ N $ 个整数 $ A_i $ 代表序列。

**输出格式**
一行一个整数代表最小操作次数。
**输入输出样例1**
**输入1**
```
5
3 2 2 3 1
```
**输出1**
```
3
```
**输入输出样例2**
**输入2**
```
5
9 7 5 3 1
```
**输出2**
```
0
```
**输入输出样例3**
**输入3**
```
2
2021 2021
```
**输出3**
```
1
```
**输入输出样例4**
**输入4**
```
8
12 2 34 85 4 91 29 85
```
**输出4**
```
93
```
**说明/提示**
**样例1解释**
- 对$[2,5]$进行操作，序列变为 $\{3,3,3,4,2\}$ 。
- 对$[2,3]$进行操作，序列变为 $\{3,4,4,4,2\}$ 。
- 对$[3,3]$进行操作，序列变为 $\{3,4,5,4,2\}$ 。
**样例2解释**
序列已经满足要求，不需要操作。
**样例3解释**
对区间$[1,1]$或$[2,2]$进行操作都可。
**数据规模与约定**
**本题采用捆绑测试。**
- Subtask1（40pts）：$ N \le 2000 $。
- Subtask2（60pts）：无特殊限制。
对于 $ 100 \% $ 的数据，$ 1 \le N \le 2 \times 10^5 $，$ 1 \le A_i \le 10^9$。

!!! :  min(max([1 - k] neg , [k - n - 1]pos))
```
8
12 2 34 85 4 91 29 85 0
12 -10 32 51 -81 87 -62 56
x 12 -10 32 51 -81 87 -62 56 x
共 11 + 82 = 93次 
```

``` cpp

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto & x: a) cin >> x;
    vector <long long > diff (n + 2);
    adjacent_difference (a.begin(), a.end(), diff.begin() + 1);
    vector <long long> leftsum (n + 2), rightsum (n + 2);

    partial_sum(diff.begin(), diff.end(), leftsum.begin(), [](long long prev, long long cur) {
        if (cur > 0) return prev;
        return prev + (1 - cur);
    });
    //后缀和 .rbegin()
    partial_sum(diff.rbegin(), diff.rend(), rightsum.rbegin(), [](long long prev, long long cur) {
        if (cur < 0) return prev;
        return prev + (1 + cur);
    });

    long long ans = LLONG_MAX;
    for (int i = 1; i <= n; i ++) {
        ans = min (ans, max(leftsum[i], rightsum[i + 1]));
    }
    cout << ans << endl;

}
```
---



