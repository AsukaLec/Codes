[TOC]

# <center>  二、前缀和

## Lead In
对于给定的一个数组 a[], 求任意区间 $sum(a, b) $ 的和。
单次访问也许可以暴力枚举得出，但是若要是访问量过大，便会导致算法耗时过大 $O(Qn)$

假设第一次访问时，从头到尾不断累加，把每一次的结果存进一个数组中：
``` c++
vector<int> prefix(n);
int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
    prefix[i] = sum;
}
```

c++ 系统库有一个函数可以替代上述for循环
``` c++
#include <numeric>
partial_sum(arr.begin(), arr.end(), prefix.begin());
```
示例
``` c++
#include <iostream>
#include <vector>
#include <numeric> // 包含 partial_sum

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5}; // 输入数组
    std::vector<int> prefix(arr.size());    // 用于存储前缀和的数组

    // 计算前缀和
    std::partial_sum(arr.begin(), arr.end(), prefix.begin());

    // 输出结果
    for (int i = 0; i < prefix.size(); ++i) {
        std::cout << "prefix[" << i << "] = " << prefix[i] << std::endl;
    }

    return 0;
}
```
输出结果：
```
prefix[0] = 1
prefix[1] = 3
prefix[2] = 6
prefix[3] = 10
prefix[4] = 15
```

这样的话 $sum(a, b) = p[b] - p[max(0, a - 1)]$  
时间复杂度 $O(n * 1) $

$a = 0$ 时，需要特判。
``` c++
//方法1
auto sum0f = [&](int l, int r) {
    if (l == 0) return prefix[r];
    return prefix[r] - prefix[l - 1];
};
//方法2 用上系统库函数
vector<int> arr(n + 1), prefix(n + 1);
for (int i = 1; i <= n; i++) cin >> arr[i];
partial_sum(arr.begin(), arr.end(), prefix.begin());
//方法3 改变存储位置
vector<int> arr(n), prefix(n + 1);
for (int i = 0; i < n; i++) cin >> arr[i];
//for (auto &x : arr) cin >> x; better one
partial_sum(arr.begin(), arr.end(), prefix.begin() + 1);
```

## 前缀和的变种
满足前缀和运算的数据都有以下特征：
满足结合律，有可逆的运算
***
**前缀积**
~~~ c++
// mul(L, R) = prefix[R] / prefix[L - 1]
prefix[i] = (prefix[i - 1] * arr[i]) % mod // 为了防止prefix中的数据过大
//取模后原来的公式就失效了
~~~
其逆运算也存在 <mark>乘法逆元</mark> 要用上费马小定理&快速幂
***

**异或和**
~~~ c++
xor(L, R) = prefix[R] ^ prefix[L - 1]
//另一种写法：
partial_sum(arr.begin(), arr.end(), xorsum.begin(), [](int prev, int cur) {
    return prev ^ cur
});
~~~
特征：
目标数组 ： 2 2 7 <mark>5 7 2</mark> 1 4 1 5
前缀数组 ： 2 0 <mark>7</mark> 2 5 <mark>7</mark> 6 2 3 6
可以得出 区间 $[L + 1, R]$ 中的异或和为0， 当 prefix[L] = prefix[R]时
***

**二维前缀**
给定原数组
| <mark>1 | <mark>2 | <mark>3 | <mark>4 | 5 |
| :---: | :---: | :---: | :---: | :---: |
| <mark>2 |<mark>3 | <mark>4 | <mark>5 | 6 |
| <mark>3 | <mark>4 | <mark>5 | <mark>6 | 7 |
| 4 | 5 | 6 | 7 | 8 |

有前缀和数组
| 1 | 3 | 6 | 10 | 15 |
| :---: | :---: | :---: | :---: | :---: |
| 3 | 8 | 15 | 24 | 35 |
| 6 | 15 | 27 | <mark>42</mark> | 60 |
| 10 | 24 | 42 | 64 | 90 |

prefix[a, b]即使这个区间内所有元素的和

要求子区间，运用容斥原理即可
```cpp
//第一种 先对行进行前缀和 再对列进行前缀和
for (int i = 1; i <= n; i++) {
    partial_sum(a[i].begin(), a[i].end(), s[i].begin());
    for (int j =1; j <= m; j++) {
        s[i][j] = s[i][j] + s[i - 1][j];
    }
}
```
```cpp
//第二种 当前元素加 左 加 上 减左上的 前缀和
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        s[i][j] = a[i][j] + s[i - 1][j] + s[i][j -1] - s[i -1][j - 1];
    }
}
```
***

**后缀和**
eg. 某个数组 [1, 2, 0, 3, 4, 1, 0, 5]包含非负整数。
统计从某个点开始， 一直到末尾 <mark>或者0的和</mark>
``` c++
//方法1
vector<int> suffix(n);
for (int i = n - 1; i >= 0; i --) {
    if (arr[i]) {
        if (i != n - 1) suffix[i] = suffix[i + 1];
        suffix[i] += arr[i];
    }
}
//方法2
partial_sum(arr.rbegin(), arr.rend(), suffix.rbegin(),
[](int prev, int cur) {
    if (cur) return prev + cur;
    return cur;
})//好简洁
```
结果 [3, 2, 0, 8, 5, 1, 0, 5 ]
***

## 2.1 lq17142 弹珠摆放 iota函数
>小蓝有 20230610 颗磁力弹珠，他对金字塔形状尤其感兴趣，如下图所示：<img src="photos\lq17142 part 1 2.1.png" width="50%" height="50%">
高度为 1 的金字塔需要 1 颗弹珠；
高度为 2 的金字塔需要 4 颗弹珠；
高度为 3 的金字塔需要 10 颗弹珠；
高度为 4 的金字塔需要 20 颗弹珠。
小蓝想要知道用他手里的弹珠可以摆出的最高的金字塔的高度是多少？

思路：
高度： [1, 2, 3, 4, 5, ···]
层中个数 [1, 3, 6, 10, 15, ···]
总数： [1, 4, 10, 20, 35, ···]
两次前缀和

!!! ! iota函数
```c++
#include <bits/stdc++.h>
using namespace std;
int main () {
    int n = 10000;
    int target = 20230610;//用来粗略确定范围
    vector<int> a(n + 1);
//     for (int i = 1; i <= n; i ++) {
//         a[i] = i;
//     }
    iota(a.begin(), a.end(), 0);//可替代上方函数
    partical_sum(a.begin(), a.end(), a.begin());
    partical_sum(a.begin(), a.end(), a.begin());

    for (int i = 0; i <= n; i ++) {
        if (a[i] > target) {
            cout << i - 1 << endl;
            break;
        }
    }
}
```
***

## 2.2 P5638 城市间寻路 
>小 K 打下的江山一共有 n 个城市，城市 i 和城市 i+1 有一条双向高速公路连接，走这条路要耗费时间 $a_i$。
小 K 为了关心人民生活，决定定期进行走访。他每一次会从 1 号城市到 n 号城市并在经过的城市进行访问。其中终点必须为城市 n。
不仅如此，他还有一个传送器，传送半径为 k，也就是可以传送到 i−k 和 i+k。如果目标城市编号小于 1 则为 1，大于 n 则为 n。
但是他的传送器电量不足，只能传送一次，况且由于一些原因，他想尽量快的完成访问，于是就想问交通部部长您最快的时间是多少。
注意：他可以不访问所有的城市，使用传送器不耗费时间。
输入格式
两行，第一行 n,k。
第二行 n−1 个整数，第 i 个表示 $a_i$。
输出格式
一个整数，表示答案。
输入输出样例
输入#1
4 0
1 2 3
输出#1
6
输入#2
4 1
1 2 3
输出#2
3

思路：找一个区间和最大的子区间，长度为 k, 再用总的和减去这个子区间的和

```c++
#include <bits/stdc++.h>
using namespace std;
int main () {
    int n, k;
    cin >> n >> k;
    n --;
    vector<long long> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        long long  x;
        cin >> x
        sum[i] = sum[i - 1] + x;
    }

    // long long total = sum[n];
    long long ans = 0;
    for (int i = k; i <= n; i++) { // 注意起始条件

        //区间端点 int r = i, l = i - k + 1;
        ans = max(ans, sum[i] - sum [i - k])
    }
    cout << sum[n] - ans;
}
```
***

## 2.3 p2004 领地选择 注意负数 注意二维vector的定义 处理边界问题
>作为在虚拟世界里统帅千军万马的领袖，小 Z 认为天时、地利、人和三者是缺一不可的，所以，谨慎地选择首都的位置对于小 Z 来说是非常重要的。
首都被认为是一个占地 C×C 的正方形。小 Z 希望你寻找到一个合适的位置，使得首都所占领的位置的土地价值和最高。
输入格式
第一行三个整数 N,M,C，表示地图的宽和长以及首都的边长。接下来 N 行每行 M 个整数，表示了地图上每个地块的价值。价值可能为负数。
输出格式
一行两个整数 X,Y，表示首都左上角的坐标。
输入输出样例
```
输入#1          输出#1
 3 4 2          1 2
 1 2 3 1
-1 9 0 2
 2 0 1 1
```
>说明/提示
对于 60% 的数据，N,M≤50。对于 90% 的数据，N,M≤300。
对于 100% 的数据，1≤N,M≤ $10^3$，1≤C≤min(N,M)。每块地价值的绝对值不超过 32767。

思路：二维前缀和， 注意所有的数字可能都是负数
```c++
#include <bits/stdc++.h>
using namespace std;
int main () {
    int n, m, c;
    cin >> n >> m >> c;
    // auto maze = vector(n + 1, vector<int>(m + 1));//注意二维vector的定义
    // for (int i = 1; i < = n; i++) {
    //     for ( int j = 1; i <= m; j ++) {
    //         cin >> maze[i][j]；
    //     }
    // } // maze用不上，可以去掉
    auto sum = vector(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for ( int j = 1; i <= m; j ++) {
            //注意前缀和数组的生成
            int x;
            cin >> x;
            // sum[i][j] = maze[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            sum[i][j] = x + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }
    int x = 1, y = 1, maxV = INY_MIN;
    //画图处理边界条件！！！
    for (int i = 0; i <= n - c; i ++) {
        for (int j = 0; j <= m - c; j++) {
            int v = sum[i + c][j + c] - sum[i + c][j] - sum[i][j + c] + sum[i][j];
        }
        if (v > maxV) {
            maxV = v;
            x = i + 1;
            y = j + 1;
        }
    }

}
```
!!! ! 画图处理最后一个循环的边界条件！！！

## 2.4 接雨水 前置最大值及后缀最大值

<img src="photos\枚举 2.4.png" width="100%" height="100%">

!!! ! 思路：开两个数组， 记录某个点的向左的最高点以及向右的最高点，两者取较小的那个一个，再减去自身的高度，即是这个点能装的最多的雨水。当然，若是这个点本身就是最高点，减出来会有负数的情况，所以还要和0比较取个较大值。 
``` c++
#include <bits/stdc++.h>
using namespace std;
int trap(vector<int> & h) {
    vector <int> left_max(n), right_max(n);
    
    //
    for (int i = 0; i < n; i++) {
        if (i == 0) left_max[i] = h[i];
        else left_max[i] = max (left_max[i - 1], h[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        if (i == n - 1) right_max[i] = h[i];
        else right_max[i] = max (right_max[i - 1], h[i]);
    }
    //和下面的二选一

    //partial_sum 发力了
    pratial_sum(h.begin(), h.end(), left_max.begin(), [&](int prev, cur) {
        return max(prev, cur);
    });
    pratial_sum(h.rbegin(), h.rend(), right_max.rbegin(), [&](int prev, cur) {
        return max(prev, cur);
    });
    //上面有两块代码 二选一实现两个前缀和


    int sum = 0;
    for (int i = 1; i < n - 1; i++) { //注意边界条件 最左边和最右边都不用判断， 但是前面开数组的时候还是要用的，不然不能进行递归。

        // sum += max(0, min(left_max[i - 1], right_max[i + 1]) - h[i]);  等效下一个式子 但是下个式子就不会出现说出现负数的情况，我的第一直觉是写下面这个式子，多画图理解一下吧

        sum += min(left_max[i], right_max[i]) - h[i];
    }
    return sum
};

int main() [
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }//输入部分

]
```
***

## 2.5 lq19717 挖矿 枚举求子区间和的最大值 确定行走方式
>问题描述
小蓝正在数轴上挖矿，数轴上一共有n个矿洞，第之个矿洞的坐标为$a_i$。 小蓝从0出发，每次可以向左或向右移动 1的距离，当路过一个矿洞时，就会进行挖矿作业，获得1单位矿石，但一个矿洞不能被多次挖掘。小蓝想知道在移动距离不超过 m 的前提下，最多能获得多少单位矿石?
输入格式
输入的第一行包含两个正整数 n,m，用一个空格分隔。
第二行包含 n 个整数 a1,a2,…,an”，相邻整数之间使用一个空格分隔。
输出格式
输出一行包含一个整数表示答案.
样例输入
5 4
0 -3 -1 1 2 
样例输出
4 
!!! ! 行走策略：整个过程只进行一次转向。 <mark>所以能挖的最多的矿就是能走到最远的子区间的区间和。
!!! ! 同时注意有负数的情况， 这不利于计算前缀和，故先根据题目数据范围确定一个偏移量， 之后再进行计算。通过<mark>枚举</mark>确定左右端点。
``` c++
#include <bits/stdc++.h>
using namespace std;
int main() {
    int offset = 1e6 + 1;
    int n, m;
    cin >> n >> m;
    vector<int> sum (offset * 2);
    while(n--) {
        int x;
        cin >> x;
        sum[x + offset]++;
    }
    partial_sum(sum.begin(), sum.end(), sum.begin())//从最左边的点到逐步前缀和， 统计在这个点及之前的所有的有矿的点。
    
    int ans = 0;
    for (int step = 0; step * 2 <= m; step++) {//highlight!!!
        int l = offset - step, right = m + offset - 2 * step;
        ans = max(ans, sum[r] - sum[l- 1]); //先向左走和先向右走效果是不一样的 所有max里面会有个ans， 一方面防止出现负数（？） 另一方面两次比较
        int l = offset - (m - step * 2), right = offset + step;
        ans = max(ans, sum[r] - sum[l- 1]); 
    }
    cout << ans << endl;
}
```
***

## 2.6 lq17110 抓娃娃  记得看数据要求
>小明拿了n几条线段练习抓娃娃。他将所有线段铺在数轴上，第i条线段的左端点在$l_i$，右端点在$r_i$;。小明用 m 个区间去框这些线段，第i个区间的范围是[$L_i$,$R_i$]。如果一个线段有 <mark>至少一半</mark> 的长度被包含在某个区间内，则将其视为被这个区间框住。请计算出每个区间框住了多少个线段?
输入格式 :
输入共几+m+1行。
第一行为两个正整数 n,m。
后面 n 行，每行两个整数 $l_i, r_i$。
后面 m 行，每行两个整数 $L_i, R_i$。
输出格式
输出共 m 行，每行一个整数。
对于 100% 的数据，保证 $n, m\leqslant 10^5, l_i < r_i, 0 < l_i, r_i, L_i, R_i \leqslant 10 ^6, $ <mark> $max\{r_i - l_i\} <= min\{R_i - L_i\}$ </mark>
``` 
输入    输出
3 2    3
1 2    2
1 3
3 4
1 4
2 4
```
!!! ! mlgb 这道题首先先不管的别的，题目要求至少一半，那么自然想到中点必须在给定的区间内。 <mark>给定区间的长度一定大于所有绳子的长度</mark> 所以大胆直接用区间和就好了md。下次题目卡住的时候多看看数据格式，也许会有所启发。
!!! ! 还有一个问题， 区间长度如果是奇数那就不太方便计算了， 0.5 是不在区间和数组中的。 <mark>所以把整个数轴 * 2 </mark> 就好了， 接下来就是普通的判断每个区间内有多少个点的前缀和问题了  
``` c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> sum( 2e6 + 1); //注意数组大小和数据限制
  while (n--) {
    int a, b;
    cin >> a >> b;
    sum[(a * 2 + b * 2) / 2]++; // 直接 a + b 就好了 具体自己细品
  }
  partial_sum(sum.begin(), sum.end(), sum.begin());
  while(m -- ) {
    int L, R;
    cin >> L >> R;
    cout << sum[R * 2] - sum[L * 2 - 1] << endl;
  }
  return 0;
}
```
红温了
***

## 2.7 P9533 区间翻转区间异或和 区间异或和 有结论 见“前缀和的变种” 组合数
>题目描述
符卡有一个长度为 $n$ 的整数数组 $a$，符卡认为一个区间 $[l,r]$ 是灵异区间当且仅当 $\bigoplus_{i=l}^ra_i=0$，或者说这个区间内所有数字异或起来刚好等于 $0$。
符卡有特殊的魔法，可以把**任意**一个灵异区间翻转。具体来说，如果 $[l,r]$ 区间是灵异区间，那么符卡就可以对这个区间使用魔法，整个数组就会变成 $a_1,a_2,\dots,a_{l-1},a_r,a_{r-1},\dots,a_l,a_{r+1},a_{r+2}\dots,a_n$。
现在符卡可以使用任意次数的魔法，符卡希望最后得到的数组的灵异区间数量能够尽可能多，你能告诉她最后最多有多少个灵异区间吗？

>输入格式
第一行一个正整数 $n$，表示数组长度。
第二行 $n$ 个非负整数 $a_1,a_2,\dots,a_n$ 表示整个数组。
输出格式
输出一行一个整数，表示符卡使用任意次魔法后灵异区间最多有多少个。
数据范围
对于前 $20\%$ 的数据，保证 $n\le 10$。
对于前 $40\%$ 的数据，保证 $n\le 2000$。
另有 $10\%$ 的数据，保证 $a_i$ 全部相等。
另有 $10\%$ 的数据，保证 $a_i$ 只有两种可能的取值。
另有 $10\%$ 的数据，保证 $0\le a_i<2^{10}$。
对于 $100\%$ 的数据，满足 $1\le n\le 10^5$，$0\le a_i< 2^{20}$。

输入输出样例 #1
输入 #1
```
3
1 1 1
```
输出 #1
```
2
```
输入输出样例 #2
输入 #2
```
4
3 1 2 3
```
输出 #2
```
2
```
>说明/提示
样例 1 解释
无论符卡发动多少次魔法，数组都是 $1,1,1$，所以发不发动魔法都没有任何关系。灵异区间永远都是 $[1,2],[2,3]$ 两个。
样例 2 解释
这里给出可能的一种魔法发动方法。
选择灵异区间 $[1,3]$ 发动魔法，得到的新数组是 $2,1,3,3$，这个数组共有两个灵异区间，分别是 $[1,3]$ 和 $[3,4]$。
可以证明答案无法超过 $2$。
彩蛋
灵异区间的名字其实是“零异（或）区间”的谐音。

!!! ! 根据结论，前缀和相等的两个下标之间的区间异或和为 0 ，接下来就是考虑区间内反转的情况：<mark>1、 要反转的区间在灵异区间内 2、 一部分在灵异区间内 3、 全部在灵异区间外</mark> 
<img src="photos\P9533 part 1 2.7.png" width="50%" height="50%">

分段分块讨论

注意 ： 前缀和要从 0 开始
<img src="photos\P9533.2 part 1 2.7.png" width="50%" height="50%">

```C++
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n ;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }//第一位是0 后面异或和

    //统计数字出现的个数
    unordered_map<int, int> cnt;
    for (auto &x : a) cnt[x] ++;// auto &x 把 x当作迭代器
    long long ans = 0;
    for (auto &[_, c] : cnt) {// 字典 所以有两个位置uto &[_, c] 
        ans += (long long)c * (c - 1) / 2;
    }
    cout << ans << endl;
}
```
***

## 2.8 lq97 K倍区间 取模 组合数 
>给定一个长度为 $N$ 的数列， $A_1,A_2,\cdots A_N,$ 如果其中一段连续子序列 $A_i,A_{i+1},\cdots A_j(i \leqslant j),$ 之和是 $K$ 的倍数， 我们就称这个区间 $[i,j]$ 是 $K$ 倍区间。
求总共有多少个这样的区间
输入：
第一行包含两个整数 $N,K,(1 \leqslant N,K \leqslant 10^5)$
以下 $N$ 行每行包含一个整数 $A_i (1 \leqslant A_i \leqslant 10 ^ 5)$ 
输出一个整数 表示目标的数列

```
样例
input:
5 2 
1
2
3
4
5
output:
6
```
```c++
#include <bits/stdc++.h>
using namespace std;
int main()
{
  int N, K;
  cin >> N >> K;
  long long cnt = 0;
  vector<long long> a (N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
  }

  vector<long long> sum (N);
  partial_sum(a.begin(), a.end(), sum.begin());

  for (int k = 0 ; k < N; k ++) {
      long long current ;
      current = a[k] ;
      if (current % K == 0) {
        cnt += 1;
      }
    }

  
    for (int k = 0 ; k < N; k ++) {
        long long current ;
        current = sum[k] ;
        if (current % K == 0) {
        cnt += 1;
        }
    }
  

  for (int i = 1; i < N - 1; i++) {
    for (int k = i + 1; k < N; k ++) {
      long long current ;
      current = sum[k] - sum[max(i - 1, 0)];
      if (current % K == 0) {
        cnt += 1;
      }
    }
  }
  cout << cnt;
  return 0;
}
```
!!! ! 第一版 超时：复杂度大于n^2了 故需要根据数字特征进行优化
!!! ! 第二版 1、处理补0的问题 2、 整除 $\rightarrow$ 取模为 0 $\rightarrow$ 对前缀和数组中的数字进行取模， 数字相同的两个数字的区间内即为 K倍区间<img src="photos\lq97 part 1 2. 8.png" width="50%" height="50%">

```c++

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) cin >> a[i];

    vector<int> s (n + 1);
    for (int i = 1; i <= n; i++) {
        s[i] = (s[i] + a[i - 1]) % k;//前缀和 和取模可以同时进行
    }
    //统计个数
    vector<int> cnt(k);//选用k的原因： 一个数模 k 可能的结果是 0 到 k - 1， 这里用来统计每个结果出现的次数。
    for (auto &x :s) cnt[x] ++;

    long long ans = 0;
    for (auto &c : cnt) ans += (long long )c * (c - 1) / 2;
    cout << ans << endl; 
}
```
***

## 2.9 P8865 种花  好题 分析何处用前缀和 可以先用暴力的方式写 然后拆分出来
>小 C 决定在他的花园里种出 $\texttt{CCF}$ 字样的图案，因此他想知道 $\texttt C$ 和 $\texttt F$ 两个字母各自有多少种种花的方案；不幸的是，花园中有一些土坑，这些位置无法种花，因此他希望你能帮助他解决这个问题。
花园可以看作有 $n\times m$ 个位置的网格图，从上到下分别为第 $1$ 到第 $n$ 行，从左到右分别为第 $1$ 列到第 $m$ 列，其中每个位置有可能是土坑，也有可能不是，可以用 $a_{i,j} = 1$ 表示第 $i$ 行第 $j$ 列这个位置有土坑，否则用 $a_{i,j} = 0$ 表示这个位置没土坑。
一种种花方案被称为 $\texttt{C-}$ **形**的，如果存在 $x_1, x_2 \in [1, n]$，以及 $y_0, y_1, y_2 \in [1, m]$，满足 $x_1 + 1 < x_2$，并且 $y_0 < y_1, y_2 \leq m$，使得第 $x_1$ **行**的第 $y_0$ 到第 $y_1$ **列**、第 $x_2$ **行**的第 $y_0$ 到第 $y_2$ **列**以及第 $y_0$ **列**的第 $x_1$ 到第 $x_2$ **行**都**不为土坑**，且只在上述这些位置上种花。
一种种花方案被称为 $\texttt{F-}$ **形**的，如果存在 $x_1, x_2, x_3 \in [1, n]$，以及 $y_0, y_1, y_2 \in [1, m]$，满足 $x_1 + 1 < x_2 < x_3$，并且 $y_0 < y_1, y_2 \leq m$，使得第 $x_1$ **行**的第 $y_0$ 到第 $y_1$ **列**、第 $x_2$ **行**的第 $y_0$ 到第 $y_2$ **列**以及第 $y_0$ **列**的第 $x_1$ 到第 $x_3$ **行**都**不为土坑**，且只在上述这些位置上种花。
样例一解释中给出了 $\texttt{C-}$ 形和 $\texttt{F-}$ 形种花方案的图案示例。
现在小 C 想知道，给定 $n, m$ 以及表示每个位置是否为土坑的值 $\{a_{i,j}\}$，$\texttt{C-}$ 形和 $\texttt{F-}$ 形种花方案分别有多少种可能？由于答案可能非常之大，你只需要输出其对 $998244353$ 取模的结果即可，具体输出结果请看输出格式部分。
第一行包含两个整数 $T, id$，分别表示数据组数和测试点编号。如果数据为样例则保证 $id = 0$。
接下来一共 $T$ 组数据，在每组数据中：
第一行包含四个整数 $n, m, c, f$，其中 $n, m$ 分别表示花园的行数、列数，对于 $c, f$ 的含义见输出格式部分。
接下来 $n$ 行，每行包含一个长度为 $m$ 且仅包含 $0$ 和 $1$ 的字符串，其中第 $i$ 个串的第 $j$ 个字符表示 $a_{i,j}$，即花园里的第 $i$ 行第 $j$ 列是不是一个土坑。
设花园中 $\texttt{C-}$ 形和 $\texttt{F-}$ 形的种花方案分别有 $V_C$ 和 $V_F$ 种，则你需要对每一组数据输出一行用一个空格隔开的两个非负整数，分别表示 $(c \times V_C) \bmod 998244353$，$(f \times V_F ) \bmod 998244353$ ，其中 $a \bmod P$ 表示 $a$ 对 $P$ 取模后的结果。
```
输入 #1
1 0
4 3 1 1
001
010
000
000
输出 #1
4 2
```

**【样例 1 解释】**

四个 $\texttt{C-}$ 形种花方案为：

```plain
**1 **1 **1 **1
*10 *10 *10 *10
**0 *** *00 *00
000 000 **0 ***
```

其中 $\texttt*$ 表示在这个位置种花。注意 $\texttt C$ 的两横可以不一样长。

类似的，两个 $\texttt{F-}$ 形种花方案为：

```plain
**1 **1
*10 *10
**0 ***
*00 *00
```

**【样例 2】**

见附件下的 $\texttt{plant/plant2.in}$ 与 $\texttt{plant/plant2.ans}$。

**【样例 3】**

见附件下的 $\texttt{plant/plant3.in}$ 与 $\texttt{plant/plant3.ans}$。

**【数据范围】**

对于所有数据，保证：$1 \leq T \leq 5$，$1 \leq n, m \leq 10^3$，$0 \leq c, f \leq 1$，$a_{i,j} \in \{0, 1\}$。

| 测试点编号 | $n$ | $m$ | $c=$ | $f=$ | 特殊性质 | 测试点分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $\leq 1000$ | $\leq 1000$ | $0$ | $0$ | 无 | $1$ |
| $2$ | $=3$ | $=2$ | $1$ | $1$ | 无 | $2$ |
| $3$ | $=4$ | $=2$ | $1$ | $1$ | 无 | $3$ |
| $4$ | $\leq 1000$ | $=2$ | $1$ | $1$ | 无 | $4$ |
| $5$ | $\leq 1000$ | $\leq 1000$ | $1$ | $1$ | A | $4$ |
| $6$ | $\leq 1000$ | $\leq 1000$ | $1$ | $1$ | B | $6$ |
| $7$ | $\leq 10$ | $\leq 10$ | $1$ | $1$ | 无 | $10$ |
| $8$ | $\leq 20$ | $\leq 20$ | $1$ | $1$ | 无 | $6$ |
| $9$ | $\leq 30$ | $\leq 30$ | $1$ | $1$ | 无 | $6$ |
| $10$ | $\leq 50$ | $\leq 50$ | $1$ | $1$ | 无 | $8$ |
| $11$ | $\leq 100$ | $\leq 100$ | $1$ | $1$ | 无 | $10$ |
| $12$ | $\leq 200$ | $\leq 200$ | $1$ | $1$ | 无 | $6$ |
| $13$ | $\leq 300$ | $\leq 300$ | $1$ | $1$ | 无 | $6$ |
| $14$ | $\leq 500$ | $\leq 500$ | $1$ | $1$ | 无 | $8$ |
| $15$ | $\leq 1000$ | $\leq 1000$ | $1$ | $0$ | 无 | $6$ |
| $16$ | $\leq 1000$ | $\leq 1000$ | $1$ | $1$ | 无 | $14$ |

特殊性质 A：$\forall 1 \leq i \leq n, 1 \leq j \leq \left\lfloor \frac{m}{3} \right\rfloor$，$a_{i, 3 j} = 1$；

特殊性质 B：$\forall 1 \leq i \leq \left\lfloor \frac{n}{4} \right\rfloor, 1 \leq j \leq m$，$a_{4 i, j} = 1$；

<img src="photos\p8865 part 1 2.9 01.png" width="50%" height="50%">
<img src="photos\p8865 part 1 2.9 02.png" width="50%" height="50%">
<img src="photos\p8865 part 1 2.9 03.png" width="50%" height="50%">
<img src="photos\p8865 part 1 2.9 04.png" width="50%" height="50%">
<img src="photos\p8865 part 1 2.9 05.png" width="50%" height="50%">

``` c++
#include <bits/stdc++.h>
using namespace std;
const  int mod = 998244353; 
int main(){
    int T, id;
    cin >> T >> id;
    while (T--) {
        int n, m, c, f;
        cin >> n >> m >> c >> f;
        //初始化题目
        vector<string> maze(n);
        for (auto &x : maze) cin >> x;

        // r u d 前缀和
        auto sum_right = vector(n, vector(m, 0));
        for (int i = 0; i < n; i ++) {
            for (int j = m - 1; j >= 0; j --) {
                if (maze[i][j] == '0') {
                    sum_right[i][j] = sum_right[i][j + 1] + 1;
                }
            }
        }

        auto sum_up = vector(n, vector(m, 0));
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < m; j ++) {
                if (maze[i][j] == '0') {
                    if (i) sum_up[i][j] =sum_up[i -1][j];

                    sum_up[i][j] =sum_right[i][j] -1;
                }
            }
        }

        auto sum_down = vector(n + 1, vector(m, 0));
        for (int i = n - 1; i >= 0; i --) {
            for (int j = 0; j < m; j ++) {
                if (maze[i][j] == '0') {
                    sum_down[i][j] = sum_down[i + 1][j] + 1
                }
            }
        }
        //预处理完成

        long long cntc = 0, cntf = 0;
        for (int x = 2; x < n; x++) {
            for (int y = 0; y < m - 1; y++) {
                if (maze[x][y] == '1' || maze[x-1][y] == '1') continue;
                cntc += sum_up[x - 2][y] * (sum_right[x][y] - 1);
                cntf += 1ll * sum_up[x - 2][y] * (sum_right[x][y] - 1) * (sum_down[x][y] - 1);//数值范围避免溢出
                cntc %= mod;
                cntf %= mod;
            }
        }

        cout << cntc * c <<' ' << cntf * f << endl;
    }
}
```
***

## 2.10 P10429
>小明是学校里的一名老师，他带的班级共有 $n$ 名同学，第 $i$ 名同学力量值为 $a_i$。在闲暇之余，小明决定在班级里组织一场拔河比赛。
为了保证比赛的双方实力尽可能相近，需要在这 $n$ 名同学中挑选出两个队伍，队伍内的同学编号连续 ***$\{{a_{l_1}}, a_{l_1 + 1}, \dots, a_{r_1 - 1}, a_{r_1}\}$ 和 $\{{a_{l_2}}, a_{l_2 + 1}, \dots, a_{r_2 - 1}, a_{r_2}\}$，其中 $l_1 \le r_1<l_2 \le r_2$***。

!!! : 和可以用前缀和运算，可这里枚举的话需要四个坐标， 时间复杂度为 $O(n^4) $ 题目数据范围为 1000， 只能接受 $O(n^2logn)$， 需优化

>两个队伍的人数不必相同，但是需要让队伍内的同学们的力量值之和尽可能相近。请计算出力量值之和差距最小的挑选队伍的方式。

>输入输出格式
输入共两行。
第一行为一个 正整数 $n$。  
第二行为 $n$ 个正整数 $a_1, a_2, \dots a_n$。
输出共一行，一个非负整数，表示两个队伍力量值之和的最小差距。

```
输入 #1
5
10 9 8 12 14

输出 #1
1
```  

>说明/提示
样例 1 解释
其中一种最优选择方式：
队伍 1：$\{a_1, a_2, a_3\}$，队伍 2：$\{a_4, a_5\}$，力量值和分别为 $10 + 9 + 8 = 27$，$12 + 14 = 26$，差距为 $|27 − 26| = 1$。

>数据规模与约定
对 $20\%$ 的数据，$n \leq 50$。
对全部的测试数据，保证 $1 \leq n \leq 10^3$，$1 \leq a_i \leq 10^9$。

!!! : <img src="photos\P10429 part 1 2. 10.png" width="100%" height="100%">

```cpp  
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;

    vector<long long> a (n);
    for (auto &x : a) cin >> x;

    vector<long long> sum(n + 1);
    partial_sum(a.begin(), a.end(), sum.begin() + 1);

    auto ans = LLONG_MAX;

    set<long long> s; //分析得出这个数据结构的过程十分关键
    
    for (int l2 = n - 1; l2 >= 1 ; l2--) {
        for (int r2 = l2 + 1; r2 <= n; r2++) {
            s.insert(sum[r2] - sum[l2]);
        }// 枚举右区间 注意枚举方式 打断点看看 枚举的是前缀和数组

        for (int l1 = 1; l1 <= l2; l1 ++) {
            auto target = sum[l2] - sum[l1 - 1]; // 枚举方式 同上 打断点看看 实际上只枚举了中间的那个点

            auto iter = s.lower_bound(target); //对于set或map,lower_bound的功能是返回一个迭代器，指向集合中第一个 大于或等于 指定值（ target ）的元素。
            //此处判断

            //iter != s.end() 说明可以找到这样的一个数
            if (iter != s.end()) ans = min(ans, *iter - target);

            
            if (iter != s.begin()) {
                -- iter;
                ans = min(ans, target - * iter);
            }
            //一头一尾 两处的取值 例如： s[0] = 1, target = 2, s[1] = 114514

            //如果iter不等于s.begin(),说明iter当前指向的元素不是集合中的第一个元素。此时， iter  可以安全地进行自减操作（ --iter ），因为集合中至少还有一个元素位于  iter  之前。
            //如果iter等于  s.begin(),说明iter指向集合的第一个元素。此时，如果再对  iter  进行自减操作，会导致迭代器越界（undefined behavior），因此需要避免。
        }
    }
    cout << ans << endl;
}
```

<mark>补充set及map相关： end() & begin() 的具体位置， iter 是 迭代器， auto的数据类型在此处应为 set<int>::iterator 。iter 的 值 需要用 * 调用。</mark>

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    set <int> s = {1, 2, 3, 4, 5};
    auto iter = s.end();
    --iter;
    cout << *iter << endl;
    iter = s.begin();
    cout << *iter;

}
5
1
```
***
