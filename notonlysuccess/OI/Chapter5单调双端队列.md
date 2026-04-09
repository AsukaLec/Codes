[TOC]
> tips：
> 算法竞赛时间复杂度指南
> 在常见的算法竞赛（如Codeforces、LeetCode、AtCoder）中，时间限制通常为1-2秒，C++环境下约可执行10^8-10^9次基本操作（取决于机器和常数因子）。以下是不同输入规模n下，常见时间复杂度是否安全的粗略估计（假设n为主要变量）：
> - O(n): n ≤ 10^7-10^8，通常安全。
> - O(n log n): n ≤ 10^6-10^7，通常安全（排序等）。
> - O(n^2): n ≤ 10^3-10^4，可能安全；n=10^5时易超时。
> - O(n^3): n ≤ 100-300，可能安全；更大时超时。
> - O(2^n) 或指数级: n ≤ 20-25，可能安全；更大时超时。
> - O(n!): n ≤ 10-12，可能安全；更大时超时。
> 
> 实际取决于常数因子、数据结构和具体问题。优化I/O（如使用ios::sync_with_stdio(false)）可提升性能。测试时用最大n验证。
> 比如用以下方法关闭io同步：
> ```cpp
> ios::sync_with_stdio(false);
> cin.tie(NULL);
> cout.tie(NULL);
> ```
# <center> 单调双端队列 </center>

## Lead in

### Intro
> Q：一堆人排成一列，现在需要找出每个人朝前看时第一个比自己高的人

**朴素的做法是**：对于每个人 $i$，从他前面开始往前找，直到找到一个比他高的人 $j$，记录下 $j$ 的位置即可，这个算法的复杂度是 $O(n^2)$ 。

**如何优化？** 
在朴素的算法中，每一个人在向前的比较的过程中，实际上进行了很多次没有必要的比较，比如对于一个人 $k$，如果他比 $i$ 矮，那么在找 $i$ 的第一个比他高的人时，$k$ 肯定不会被考虑到，因为 $i$ 前面的第一个比他高的人一定也比 $k$ 高。
```
1 9 `4 6` 7     8
```
比如这里，4和6都不会被考虑到。
**因此**，只需要一个栈来维护一个单调递减的序列即可。每当遇到一个新的人 $x$ 时，就把栈顶比 $x$ 矮的人都弹出，直到栈顶比 $x$ 高或者栈空为止。此时栈顶元素就是 $x$ 朝前看的第一个比他高的人。

### 以上过程可以抽象成如下模板函数：
```cpp
template <template <typename> typename Cmp = greater, typename T>
//false 用于找后一个，true用于找前一个
vector<int> get_next_prev(vector<T> &arr, bool prev = false) {
    int n = arr.size();
    vector<int> res(n);
    stack<int> st;
    for (int i = prev ? 0 : n - 1; prev ? i < n : i >= 0; prev ? ++i : --i) {
        while (!st.empty() && !Cmp<T>()(arr[st.top()], arr[i])) st.pop();
        res[i] = st.empty() ? (prev ? -1 : n) : st.top();
        st.push(i);
    }
    return res;
}
```
- 其中 `Cmp` 是一个比较模板参数，表示栈中元素的单调性，默认为 `greater`，即单调递减；`prev` 表示是找前一个还是后一个。
- 如果 `prev` 为 `true`，则表示找前一个比自己大的元素，遍历方向为从左到右；
- 如果 `prev` 为 `false`，则表示找后一个比自己大的元素，遍历方向为从右到左。
- `res[i]` 记录的就是第 `i` 个元素的前/后一个比自己大的元素的位置，如果不存在则为 -1 或 n。
- 时间复杂度为 $O(n)$。

可以转换成以下八种情况
``` cpp
auto next_greater = get_next_prev<greater>(arr, false);      // 下一个更大
auto next_grater_equal = get_next_prev<greater_equal>(arr, false); // 下一个更大或相等
auto next_less = get_next_prev<less>(arr, false);            // 下一个更小
auto next_less_equal = get_next_prev<less_equal>(arr, false);   // 下一个更小或相等

auto prev_greater = get_next_prev<greater>(arr, true);       // 上一个更大
auto prev_greater_equal = get_next_prev<greater_equal>(arr, true); // 上一个更大或相等
auto prev_less = get_next_prev<less>(arr, true);             // 上一个更小
auto prev_less_equal = get_next_prev<less_equal>(arr, true);    // 上一个更小或相等
``` 

### 问题的变种 引入双端队列
> Q: 由于每个人视力有限，现在需要求出每个人前面 $k$ 个人中身高最高的那个人。

使用单调双端队列即可解决该问题。可视为维护一个 $k$ 长度的窗口，从左往右移动，求窗口内的最大值。每一次窗口向右移动，若容器内最前面的元素超出了窗口的范围，就把第一个元素弹出窗口，此时窗口内新的第一个元素就是所要的答案。

```cpp
vector<int> window_max(n);
deque<int> deq; //双端队列，在两端的插入删除都很高效，但是内存开销大。
// deque中存储的是元素的下标
for (int i = 0; i < n; i ++) {
    while (!deq.empty() && arr[deque.back()] <= arr[i]) {
        deq.pop_back();
    }
    while (!deq.empty() && deq.front() <= i - k) {
        deq.pop_front();
    }

    deq.push_back(i);
    window_max[i] = arr[deq.front()];
}
```
抽象成如下模板
```cpp
template <typename T, template <typename> typename Cmp = greater>
class mono_deque : public deque<pair<int, T>>{ // Monotonic 单调
    // int 表示元素的下标，T表示元素的值

    public:
    //将元素保存到末尾并自动保持单调性
    mono_deque & push(int idx, const T &x) {
        while (!this->empty() && !Cmp<T>()(this->back().second, x))this->pop_back(); //Cmp greater下 第一个元素比第二个元素大 返回true

        this->push_back({idx, x});
        return *this
    }
    //将队列中坐标小于等于 idx 的元素删除
    mono_deque & shrink_to(int idx) {
        while (!this_>empty() && this->front().first <= idx) this->pop_front();
        return *this;
    }
    //获取当前队列中的极值
    T get_extremum() {return this->front().second;}
};
```
刚才的问题就可以转化为
```cpp
mono_deque<int> int_q;
for (int i = 0; i < n; i ++>) {
    //朴素写法
    int_q.push(i, arr[i]);
    int_q.shrink_to(i - k);
    window_max[i] = int_q.get_extremum();

    //链式写法
    window_max[i] = int_q.push(i, arr[i]).shrink_to(i - k).get_extremum();
}
```
### 总结
只要问题可以抽象成
- 所有元素往前或往后 第一个大于或小于的元素
- 所有元素往前或往后 单调递增区间内的极值

---

## 5.1 P5788 【模板】单调栈

### 题目描述

给出项数为 $n$ 的整数数列 $a_{1 \dots n}$

定义函数 $f(i)$ 代表数列中第 $i$ 个元素之后第一个大于 $a_i$ 的元素的**下标**，即 $f(i)=\min_{i<j\leq n, a_j > a_i} \{j\}$。若不存在，则 $f(i)=0$。

试求出 $f(1\dots n)$

### 输入格式

第一行一个正整数 $n$。

第二行 $n$ 个正整数 $a_{1\dots n}$。

### 输出格式 

一行 $n$ 个整数表示 $f(1), f(2), \dots, f(n)$ 的值。

#### 输入输出样例 #1

#### 输入 #1

```
5
1 4 2 3 5

```

#### 输出 #1

```
2 5 4 5 0

```

### 说明/提示 

> 【数据规模与约定】
> 对于 $30\%$ 的数据，$n\leq 100$；
> 对于 $60\%$ 的数据，$n\leq 5 \times 10^3$ ；
> 对于 $100\%$ 的数据，$1 \le n\leq 3\times 10^6$，$1\leq a_i\leq 10^9$。

### 题解

!!! : 模板题


```cpp
//不用模板
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int > arr(n);
    for(auto &x: arr) cin >> x;
    stack<int> st;
    vector<int> next_g(n);

    for(int i = n - 1; i >= 0; i --){
        while(!st.empty() && arr[st.top()] <= arr[i]) st.pop();
        if (st.empty()) next_g[i] = -1;
        else next_g[i] = st.top();
        st.push(i);
    }

    for(int i = 0; i < n;i ++){
        cout << next_g[i] + 1 << ' ';
    }
}
```

```cpp
//模板写法
#include <bits/stdc++.h>
using namespace std;

template <template<typename> typename Cmp = greater, typename T>
vector<int> get_next_prev(vector<T> &arr, bool prev = false) {
    int n = arr.size();
    vector<int> res(n);
    stack<int> st;
    for (int i = prev ? 0 : n - 1; prev ? i < n : i >= 0; prev ? ++i : --i) {
        while (!st.empty() && !Cmp<T>()(arr[st.top()], arr[i])) st.pop();
        res[i] = st.empty() ? (prev ? -1 : n) : st.top();
        st.push(i);
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int > arr(n);
    for(auto &x: arr) cin >> x;

    auto next_g = get_next_prev<greater>(arr);

    for(int i = 0; i < n;i ++){
        if (next_g[i] == n) cout << 0 << ' ';
        else cout << next_g[i] + 1 << ' ';
    }
}
```

---

## 5.2 P1886 【模板】单调队列 / 滑动窗口

### 题目描述

有一个长为 $n$ 的序列 $a$，以及一个大小为 $k$ 的窗口。现在这个窗口从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最小值和最大值。

例如，对于序列 $[1,3,-1,-3,5,3,6,7]$ 以及 $k = 3$，有如下过程：

$$\def\arraystretch{1.2}
\begin{array}{|c|c|c|}\hline
\textsf{窗口位置} & \textsf{最小值} & \textsf{最大值} \\ \hline
\verb![1   3  -1] -3   5   3   6   7 ! & -1 & 3 \\ \hline
\verb! 1  [3  -1  -3]  5   3   6   7 ! & -3 & 3 \\ \hline
\verb! 1   3 [-1  -3   5]  3   6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1 [-3   5   3]  6   7 ! & -3 & 5 \\ \hline
\verb! 1   3  -1  -3  [5   3   6]  7 ! & 3 & 6 \\ \hline
\verb! 1   3  -1  -3   5  [3   6   7]! & 3 & 7 \\ \hline
\end{array}
$$

### 输入格式

输入一共有两行，第一行有两个正整数 $n,k$；\
第二行有 $n$ 个整数，表示序列 $a$。

### 输出格式

输出共两行，第一行为每次窗口滑动的最小值；   
第二行为每次窗口滑动的最大值。

### 输入输出样例 #1

#### 输入 #1

```
8 3
1 3 -1 -3 5 3 6 7
```

#### 输出 #1

```
-1 -3 -3 -3 3 3
3 3 5 5 6 7
```

### 说明/提示

> 【数据范围】
> 对于 $50\%$ 的数据，$1 \le n \le 10^5$；  
> 对于 $100\%$ 的数据，$1\le k \le n \le 10^6$，$a_i \in [-2^{31},2^{31})$。

### 题解
无模板，注意区间的头和尾

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    vector<int > arr(n);
    for(auto &x: arr) cin >> x;

    deque<int> next_g(n);
    deque<int> next_s(n);

    vector<int> res_g(n);
    vector<int> res_s(n);

    for(int i = 0; i < n; i++){
        while(!next_g.empty() && arr[next_g.back()] <= arr[i]) next_g.pop_back();
        while(!next_s.empty() && arr[next_s.back()] >= arr[i]) next_s.pop_back();
        
        while(!next_s.empty() && next_s.front() <= i - k) next_s.pop_front();
        while(!next_g.empty() && next_g.front() <= i - k) next_g.pop_front();

        next_g.push_back(i);
        next_s.push_back(i);

        res_g[i] = arr[next_g.front()];
        res_s[i] = arr[next_s.front()];
    }

    for (int i = 2; i < n; i ++) {
        cout << res_s[i] << ' ';
    }
    cout << "\n";
    for(int i = 2; i < n; i ++) {
        cout << res_g[i] << ' ';
    }
}
```
模板

```cpp
//模板写法
int main() {
    int n, k;
    cin >> n >> k;
    vector<int > arr(n);
    for(auto &x: arr) cin >> x;

    vector<int> res_g(n);
    vector<int> res_s(n);

    mono_deque<int, greater> next_g;
    mono_deque<int, less> next_s;

    for(int i = 0; i < n; i ++) {
        res_g[i] = next_g.push(i, arr[i]).shrink_to(i - k).get_extremum();
        res_s[i] = next_s.push(i, arr[i]).shrink_to(i - k).get_extremum();
    }

    for (int i = 2; i < n; i ++) {
        cout << res_s[i] << ' ';
    }
    cout << "\n";
    for(int i = 2; i < n; i ++) {
        cout << res_g[i] << ' ';
    }
}
```
---

## 5.3 P1901 发射站

### 题目描述

某地有 $N$ 个能量发射站排成一行，每个发射站 $i$ 都有不相同的高度 $H_i$，并能向两边（两端的发射站只能向一边）同时发射能量值为 $V_i$ 的能量，发出的能量只被两边**最近的且比它高**的发射站接收。显然，每个发射站发来的能量有可能被 $0$ 或 $1$ 或 $2$ 个其他发射站所接受。

请计算出接收最多能量的发射站接收的能量是多少。

### 输入格式

第 $1$ 行一个整数 $N$。

第 $2$ 到 $N+1$ 行，第 $i+1$ 行有两个整数 $H_i$ 和 $V_i$，表示第 $i$ 个发射站的高度和发射的能量值。

### 输出格式

输出仅一行，表示接收最多能量的发射站接收到的能量值。答案不超过 32 位带符号整数的表示范围。

### 输入输出样例 #1

#### 输入 #1

```
3
4 2 
3 5 
6 10

```

#### 输出 #1

```
7
```

### 说明/提示
> 对于 $40\%$ 的数据，$1\le N\le 5000,1\le H_i\le 10^5,1\le V_i\le 10^4$。
> 对于 $70\%$ 的数据，$1\le N\le 10^5,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。
> 对于 $100\%$ 的数据，$1\le N\le 10^6,1\le H_i\le 2\times 10^9,1\le V_i\le 10^4$。

### 题解
算是模板题
```cpp
int main() {
    int n;
    cin >> n;
    vector<int> H(n);
    vector<int> power(n);
    for(int i = 0; i < n; i++) cin >> H[i] >> power[i];

    //记录最左边最高的信号塔，若没有比自身高的，则返回-1
    auto left_idx = get_next_prev<greater>(H, true);
    //记录最右边最高的信号塔，若没有比自身高的，则返回n
    auto right_idx = get_next_prev<greater>(H, false);

    //统计每个信号塔接收到的能量
    int max = -1;
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        if(left_idx[i] >= 0) ans[left_idx[i]] += power[i];
        if(right_idx[i] < n) ans[right_idx[i]] += power[i];
    }

    for (auto &x : ans) if(x > max) max = x;

    cout << max << endl;
}
```

---

## 5.4 Lq6251 游戏

### 题目描述
熊大和熊二在玩游戏。他们将 n 个正整数 a1,a2,...,an 排成一行，然后各用一个长度为 k 的框在这个数组中各自随机框选出一段长度为 k 的连续子序列（“随机框选”指在合法的 n−k+1 个连续子序列中均匀随机）。熊大记录了他框出的 k 个数中的最大值 P，熊二记录了他框出的 k 个数的最小值 Q，他们想知道：P−Q 的期望是多少？


### 输入描述：
输入共 2 行。

- 第一行为两个正整数 n, k。
- 第二行为 n 个由空格隔开的正整数 a1,a2,...,an。

### 输出描述：
输出共 1 行，一个浮点数（请保留两位小数）。

### 样例输入：
```
3 2
1 2 3
```

### 样例输出：
```
1.00
```

### 样例说明：
一共有四种情况（熊大框选与熊二框选的组合）：
- 熊大框出 [1,2], P=2；熊二框出 [1,2], Q=1，P−Q=1。
- 熊大框出 [1,2], P=2；熊二框出 [2,3], Q=2，P−Q=0。
- 熊大框出 [2,3], P=3；熊二框出 [1,2], Q=1，P−Q=2。
- 熊大框出 [2,3], P=3；熊二框出 [2,3], Q=2，P−Q=1。
因此 P−Q 的期望为 (1+0+2+1)/4 = 1.00。

### 评测用例规模：
- 对于 20% 的数据，保证 n ≤ 10^2。
- 对于 40% 的数据，保证 n ≤ 10^3。
- 对于 100% 的数据，保证 n ≤ 10^5，0 < ai ≤ 10^9，0 < k ≤ n。

### 题解

本题的关键点在于如何将期望值的计算转换。
很显然，如果对于每一个最大值和最小值都进行计算，时间复杂度是 $O(n^2)$ 的，无法接受。

朴素来说，我们希望计算的是：

$$
\begin{aligned}
&(P_1 - Q_1 + P_1 - Q_2 + ... + P_1 - Q_{n-k+1}) + \\
&(P_2 - Q_1 + P_2 - Q_2 + ... + P_2 - Q_{n-k+1}) + \\
&... \\
&(P_{n-k+1} - Q_1 + P_{n-k+1} - Q_2 + ... + P_{n-k+1} - Q_{n-k+1})
\end{aligned}
$$

可以观察到
$$
\begin{aligned}
&= (P_1 + P_2 + ... + P_{n-k+1}) \times (n-k+1) - (Q_1 + Q_2 + ... + Q_{n-k+1}) \times (n-k+1) \\
&= ( \sum_{i=1}^{n-k+1} P_i - \sum_{i=1}^{n-k+1} Q_i ) \times (n-k+1)
\end{aligned}
$$

所以只需要用单调双端队列计算出每个区间的最大值和最小值，求和，做差并除以区间个数即可。

```cpp
int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for(auto &x: arr) cin >> x;

    int k_n  = n - k + 1;

    mono_deque<int, greater> max_dq;
    mono_deque<int, less> min_dq;

    vector<int> res_max(n);
    vector<int> res_min(n);

    for (int i = 0; i < n; i ++) {
        res_max[i] = max_dq.push(i, arr[i]).shrink_to(i - k).get_extremum();
        res_min[i] = min_dq.push(i, arr[i]).shrink_to(i - k).get_extremum();
    }

    double max_total = 0.0;
    double min_total = 0.0;
    for (int i = k - 1; i < n; i ++) {
        max_total += res_max[i];
        min_total += res_min[i];
    }

    double ans = (max_total - min_total) / (k_n);

    cout << fixed << setprecision(2) << ans << endl;

}
```

---



## 5.5 Lq17152 最大区间

### 题目描述
给定一个长度为 n 的序列 A_i，求 L, R 使
$$
(R - L + 1) \cdot \min(A_L, A_{L+1}, \dots, A_R)
$$
尽可能大，其中 $\min$ 表示区间内的最小值。你只需要输出最大的值即可，不需要输出具体的 $L, R$。

### 输入格式
输入的第一行包含一个整数 $n$。

第二行包含 $n$ 个整数，分别表示 $A_1, A_2, \dots, A_n$，相邻两个整数之间使用一个空格分隔。

### 输出格式
输出一行包含一个整数表示答案。

### 样例输入
```
5
1 1 3 3 1
```

### 样例输出
```
6
```

### 评测用例规模与约定
- 对于 40% 的评测用例，$1 \le n \le 5000$，$1 \le A_i \le 5000$；
- 对于所有评测用例，$1 \le n \le 3\times 10^5$，$1 \le A_i \le 10^9$。

### 题解
根据已经学了的知识，求一个区间内的最小值对于我们来说是很容易的，所以这部分其实可以pass掉。
我们实际上要解决的问题是：
给定一个序列 $$ A_1, A_2, \dots, A_n $$
存在一个区间 $(L, R)$, 使得 $Max((R - L + 1) * min(A_l, A_{L+1} , ..., A_R))$
求出这个 $Max$ 值

这两坨东西都在变，如何解决呢？
#### 尝试1
依旧暴力算法，前面的 $R- L+1$  实际上即是区间的长度，区间的长度范围为从 1 到 n， 那么只需要用到单调双端队列，对于每一个长度 $len$，计算出所有长度为 $len$ 的区间的最小值，然后计算 $(len) * min$ 的最大值即可。
```cpp
int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &x: arr) cin >> x;

    mono_deque<int, less> min_dq;

    vector<int> res_min(n);

    int cur_min = INT_MIN;
    int cur_ans = 0;
    
    for (int k = 1; k < n; k ++) {
        for(int i = 0; i < n; i ++) {
            res_min[i] = min_dq.push(i, arr[i]).shrink_to(i - k).get_extremum();
        }

        for (int i = k - 1; i < n; i++) {
            if (res_min[i] > cur_min) cur_min = res_min[i];
        }

        cur_ans = max(cur_ans, cur_min * k);
        cur_min = INT_MIN;
    }
    cout << cur_ans << endl;

}
```
很明显，这个算法的时间复杂度是 $O(n^2)$ 的，无法接受。
#### 尝试2
既然固定区间的长度是不行的，那么尝试固定区间内的最小值呢？
对于每一个元素 $A_i$，假设它是区间内的最小值，那么我们需要找到以 $A_i$ 为最小值的区间的最大长度是多少。
这就变成了求每一个元素是最小值的区间对应的起始元素和结束元素即可
```cpp
#include <bits/stdc++.h>
using namespace std;
template < typename T>
vector<int> find_left (vector<T> &arr) {
    int n = arr.size();
    vector<int> res(n);

    for (int i = 0; i < n; i ++) {
        int left_pos = i;
        for (int k = i - 1; k >= 0; k --) {
            if (arr[k] >= arr[i]) left_pos-- ;
            else break;
        }
        res[i] = left_pos;
    }
    return res;
}

template < typename T>
vector<int> find_right (vector<T> &arr) {
    int n = arr.size();
    vector<int> res(n);


    for(int i = n - 1; i >= 0; i --) {
        int right_pos = i;
        for (int k = i + 1; k < n; k ++) {
            if (arr[k] >= arr[i]) right_pos++ ;
            else break;
        }
        res[i] = right_pos;
    }
    return res;
}


int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for(auto &x: arr) cin >> x;

    auto left_pos = find_left(arr);
    auto right_pos = find_right(arr);

    // for (auto &x : left_pos) cout << x << ' ';
    // cout << endl;
    // for (auto &x : right_pos) cout << x << ' ';
    // cout << endl;

    long long max = LONG_LONG_MIN;
    for (int i = 0; i < n; i ++) {
        max = arr[i] * (right_pos[i] - left_pos[i] + 1) >  max ? arr[i] * (right_pos[i] - left_pos[i] + 1) : max;
    }
    
    cout << max << endl;
}
```

很可惜，这个算法的时间复杂度也是 $O(n^2)$ 的，无法接受。
为什么呢，因为每一个元素都要向左和向右遍历一遍，最坏情况下是 $O(n)$ 的。

那么如何优化呢？

**我们在最前面的假设其实可以优化成**
寻找每一个元素，在它左边第一个比它小的元素的索引 $x$ 以及右边第一个比他小的元素的索引 $y$
区间长度的计算修改成 $y - x - 1$
然后你看这个是不是就变成了前面单调栈实现的内容

AC代码如下，力竭了
```cpp
template <template <typename> typename Cmp = greater, typename T>
vector<int> get_next_prev(vector<T> &arr, bool prev = false) {
    int n = arr.size();
    vector<int> res(n);
    stack<int> st;
    for (int i = prev ? 0 : n - 1; prev ? i < n : i >= 0; prev ? ++i : --i) {
        while (!st.empty() && !Cmp<T>()(arr[st.top()], arr[i])) st.pop();
        res[i] = st.empty() ? (prev ? -1 : n) : st.top();
        st.push(i);
    }
    return res;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    auto prev_l = get_next_prev<less>(a, true);
    auto next_l = get_next_prev<less>(a);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, (next_l[i] - prev_l[i] - 1LL) * a[i]);
    }
    cout << ans << endl;
}
```
---

## 5.6 最大矩形
### 题目描述
给定一个只包含 `0` 和 `1` ， 大小 `row x cols` 的二维二进制矩阵，找出只包含 `1` 的最大矩形，并返回其面积。

### 示例
$$\def\arraystretch{1.5}
\begin{array}{|c|c|c|c|c|}\hline
\textsf{1} & \textsf{0} & \textsf{1} & \textsf{0} & \textsf{0} \\ \hline
1 & 0 & 1 & 1 & 1 \\ \hline
1 & 1 & 1 & 1 & 1  \\ \hline
1 & 0 & 0 & 1 & 0  \\ \hline
\end{array}
$$

输出 6

### 题解
其实这道题和上面那道题挺像的，算是一种几何上的直观。
比如我们现在只看这个矩阵的前三行，把每一列的高度以前缀和的形式放回原数组中
``` 
 1 0 1 0 0
 2 0 2 1 1
 3 1 3 2 2
```     
然后对于每一行，我们都计算出以**该行为底**的最大矩形面积即可
至于怎么算，看上一题，还是用到了单调栈的内容


**需要特别注意到是，每一行的底不能为 0**
为什么不能有0？
参考以下例子
```
0 1 1 0
1 1 1 1
1 1 1 1
0 0 0 1
```
如果只是单纯的前缀和，**那么只需要在最底下那一行往上进行统计**，就会得到错误的12的结果
要达成这一点，可以通过特殊的前缀和来处理

代码如下
```cpp
int main() {
    int n, m;
    vector<vector<int>> maze;
    cin >> n >> m;
    maze.resize(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }

    auto height = vector(n, vector<int>(m));

    //前缀和 
    //有个很关键的点，每一个纵列最底下的元素的值不能为0，否则高度无法计算
    //这里前缀和的计算很巧妙地解决了这个问题
    for (int i = 0; i < n; i ++) {
        for (int j =0; j < m; j ++) {
            if (maze[i][j] == 0) continue;
            height[i][j] = 1;
            if(i) height[i][j] += height[i - 1][j];
        }
    }

    // cout << endl;
    // for (auto &row :height){
    //     for (auto &x : row) cout << x << ' ';
    //     cout << endl;
    // }

    int ans = 0;
    for (int x = 0; x < n; x ++) {
        auto left_idx = get_next_prev<less>(height[x], true);
        auto right_idx = get_next_prev<less>(height[x]);

        for (int i = 0; i< m; i++) {
            ans = max(ans, (right_idx[i] - left_idx[i] - 1) * height[x][i]);
        }
    }

    cout << ans << endl;
}
```

---

## 5.7 Lq3521 子矩阵 二维单调双端队列模板题

### 题目描述
给定一个 $n×m$（$n$ 行 $m$ 列）的矩阵。设一个矩阵的价值为其所有数中的最大值和最小值的乘积。求给定矩阵的所有大小为 $a×b$（$a$ 行 $b$ 列）的子矩阵的价值的和。

答案可能很大，你只需要输出答案对 998244353 取模后的结果。

### 输入格式
输入的第一行包含四个整数，分别表示 $n, m, a, b$，相邻整数之间使用一个空格分隔。接下来 $n$ 行每行包含 $m$ 个整数，相邻整数之间使用一个空格分隔，表示矩阵中的每个数 $A_{i,j}$。

### 输出格式
输出一行包含一个整数表示答案（模 998244353）。

### 样例输入
```
2 3 1 2
1 2 3
4 5 6
```

### 样例输出
```
58
```

### 样例说明
所有 1×2 的子矩阵的价值之和为：
1×2 + 2×3 + 4×5 + 5×6 = 58。

### 评测用例规模与约定
- 对于 40% 的评测用例，1 ≤ n, m ≤ 100；
- 对于 70% 的评测用例，1 ≤ n, m ≤ 500；
- 对于所有评测用例，1 ≤ a ≤ n ≤ 1000，1 ≤ b ≤ m ≤ 1000，1 ≤ A_{i,j} ≤ 10^9。

### 题解
这道题可以看作是单调双端队列的二维模板题目
跟前面那个滑动窗口是一样的，都是计算一定区间内的最大值或者最小值
对于二维的情况，只需要先计算每一列每个区间内的最大值和最小值，在计算每一行每个区间内的最大值和最小值即可

```cpp
int main(){
    int n, m , a ,b;
    cin >> n >> m >> a >> b;
    auto maze = vector(n, vector<int>(m));
    auto max_maze = vector(n, vector<int>(m));
    auto min_maze = vector(n, vector<int>(m));

    for (auto &row : maze) for (auto &x : row) cin >> x;

    for (int i = 0; i < n; i ++) {
        mono_deque<int, greater> max_dq;
        mono_deque<int, less> min_dq;
        for (int j = 0; j < m; j ++) {
            max_maze[i][j] = max_dq.push(j, maze[i][j]).shrink_to(j - b).get_extremum();
            min_maze[i][j] = min_dq.push(j, maze[i][j]).shrink_to(j - b).get_extremum();
        }    
    }

    for( int j = 0; j < m; j ++) {
        mono_deque<int, greater> max_dq;
        mono_deque<int, less> min_dq;
        for (int i = 0; i < n; i ++) {
            max_maze[i][j] =  max_dq.push(i, max_maze[i][j]).shrink_to(i - a).get_extremum();
            min_maze[i][j] =  min_dq.push(i, min_maze[i][j]).shrink_to(i - a).get_extremum();
        }
    }

    long long ans = 0;
    for (int i = a - 1; i < n; i ++) {
        for (int j = b - 1; j < m; j ++) {
            ans += max_maze[i][j] * min_maze[i][j];
            ans %= 998244353;
        }
    }

    cout << ans << endl;
}
```

--- 

## 5.8 又双叒叕是接雨水
### 题目描述
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\枚举 2.4.png " width="600"/>
  </div>
</div>

### 题解
好麻烦 看视频去吧 主要是递归的一个过程

---


## 5.9 P9290 Decryption 

### 题目描述

研究表明，汉字的顺序并不一定能影响阅读。科学家们对数列进行了类似的研究。

给一个正整数数列，若数列首项为数列中所有数的最小值，末项为数列中的最大值，则我们称这是个正确的数列。例如，序列 $[1, 3, 2, 4]$ 和 $[1, 2, 1, 2]$ 是正确的，但序列 
$[1, 3, 2]$ 不是。

给出长度为 $n$ 的序列 $[a_1, a_2, \ldots, a_n]$。对于该序列的某个片段 $[a_l, a_{l+1}, \ldots, a_r]$, 若该片段的首项为该片段中的最小值，末项为该片段中的最大值，则我们称这是个正确的片段。

对于给定的序列，请求出该序列至少需要被分成多少段，才能使得每个片段均为正确的片段。序列 $[2, 3, 1, 1, 5, 1]$ 可以分为三个正确的段：$[2, 3]$ 和 $[1, 1, 5]$ 和 $[1]$。

需要编写一个程序，该程序按给定的顺序确定可以划分的最小正确段数。

### 输入格式

第一行一个整数 $n$。

接下来一行 $n$ 个数，分别为 $a_1,a_2,\ldots,a_n$。

### 输出格式

输出可以划分的最小正确段数。

### 输入输出样例 #1

#### 输入 #1

```
5
5 4 3 2 1
```

#### 输出 #1

```
5
```

### 输入输出样例 #2

#### 输入 #2

```
4
1 3 2 4
```

#### 输出 #2

```
1
```

### 输入输出样例 #3

#### 输入 #3

```
6
2 3 1 1 5 1
```

#### 输出 #3

```
3
```

### 说明/提示

- 子任务 1（30 分），$1 \leq n \leq 500$。
- 子任务 2（30 分），$1 \leq n \leq 5000$。
- 子任务 3（40 分），$1 \leq n \leq3 \times 10^5$。

对于所有数据，$1 \leq n \leq3 \times 10^5$，$1\leq a_i \leq 10^9$。

### 题解

#### 1. Nice Try BUT TLE
根据题意可以知道：
- 一个数如果是一个区间的左端点，那么这个数是这个区间内的最小值
- 一个数如果是一个区间的右端点，那么这个数是这个区间内的最大值

那么我们接下来考虑一下一个数可能存在的区间范围
先计算出如下数据：
- next_l ：每一个数右边第一个比它小的数的索引 - 1
- prev_g : 每一个数左边第一个比它大的数的索引 + 1

**如果一个数 $a_i$ 是一个区间的左端点，那么以它为区间左端点的最大区间是 $[i, next_l[i]]$**
**如果一个数 $a_j$ 是一个区间的右端点，那么以它为区间右端点的最大的区间是 $[prev_g[j], j]$**

那么我们只需要从左向右遍历这个数组，使用左指针`left_idx`和右指针`right_idx`记录当前的区间
先把右指针的值设为`next_l[left_idx]`,表示最大的可能的表示范围，然后再将`prev_[right_idx]`和`left_idx`进行比较，如果`prev_g[right_idx] <= left_idx`，说明当前的右端点可以和左端点匹配，该区间的长度已经尽可能地长；否则，就左移 `right_idx`,直到可以匹配为止(当 `left_idx == right_idx` 时一定可以匹配 )。

根据以上思想，代码如下：
```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    auto next_l = get_next_prev<less>(a);
    auto prev_g = get_next_prev<greater>(a, true);

    for (int i = 0; i < n; i ++) {cout << i << "," << --next_l[i] << "; ";}
    cout << endl;
    for (int i = 0; i < n; i ++) {cout << ++prev_g[i]  << "," << i << "; ";}
    cout << endl;
    
    // for (int i= 0; i < n; i++) {next_l[i]--; prev_g[i]++;}

    int ans = 0;
    for(int left_idx = 0, right_idx = next_l[left_idx]; left_idx < n;) {

        for (; right_idx >= left_idx; right_idx --) {
            if (prev_g[right_idx] <= left_idx) {
                ans += 1;
                left_idx = ++ right_idx;
                right_idx = next_l[left_idx];
                break;
            }
        }
    }
    cout << ans;
}
```

**Why TLE?**
在最好的情况下，`right_idx` 每次都能直接找到匹配的右端点，那么时间复杂度就是 $O(n)$ 的；
但在最坏情况下，`right_idx` 每次都只能左移一位，那么时间复杂度就是 $O(n^2)$ 的，无法接受。

#### 2. AC
目前我们已经发现了导致最差时间复杂度为 $O(n^2)$ 的原因是 `right_idx` 重复进行了左移，那么如何优化呢？

考虑这样一个序列
$$ a_1, a_2, ... , a_n$$
假设我们已经找到了一个区间的左端点 $a_l$ (这是很显然的), 那么哪些值可能成为 $a_l$ 所在的区间的右端点呢？
我们还是跟上面一样定义两个数组：
- next_l ：每一个数右边第一个比它小的数的索引
- next_g : 每一个数右边第一个比它大的数的索引

那么，这个可能成为右端点的数 $a_i$ 就必须满足如下条件：
$$
\begin{aligned}
& n_1 = next_g[l] \\
& n_2 = next_g[n_1] \\
& ... \\
& i = next_g[n_{i-1}] \\
& 且 \\
& i < next_l[l]
\end{aligned}
$$ 

这样，我们就可以直接**跳跃地**找到所有可能的右端点，而不需要一个一个地左移 `right_idx` 了。
因为跳跃的次数最多为 $O(n)$ 次，所以最坏情况下的时间复杂度为 $O(n)$，满足题目给定的数据的要求。

代码如下，力竭了
```cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;
    auto next_l = get_next_prev<less>(a);
    auto next_g = get_next_prev<greater_equal>(a);

    int ans = 0;
    for (int left_idx = 0, right_idx = 0; left_idx < n; ) {
        for(; next_g[right_idx] < next_l[left_idx]; right_idx = next_g[right_idx]);
        left_idx = right_idx = right_idx  + 1;
        ans ++;
    }

    cout << ans;
}
```
T_T

---

## 5.10 P2698 [USACO12MAR] Flowerpot S 关联 4.3 Lq2174 最大子矩阵

### 题目描述

![](https://cdn.luogu.com.cn/upload/pic/9174.png) 

老板需要你帮忙浇花。给出 $N$ 滴水的坐标，$(x,y)$ 表示水滴最初的坐标。

每滴水均以每秒 $1$ 个单位长度的速度下落。你需要把花盆放在 $x$ 轴上的某个位置，使得花盆接到第 $1$ 滴水与最后 $1$ 滴水之间的时间差至少为 $D$。

如果水滴落在 $x$ 轴上的位置与花盆的边沿对齐，也认为被接住。

给出 $N$ 滴水的坐标和时间差 $D$ ，请算出最小的花盆宽度 $W$。

### 输入格式

第一行 $2$ 个整数 $N$ 和 $D$。

接下来 $N$ 行，每行 $2$ 个整数，表示水滴的坐标 $(x,y)$。

### 输出格式

一行 $1$ 个整数，表示最小的花盆宽度。如果无法构造出满足题意的花盆，则输出 $-1$。

### 输入输出样例 #1

#### 输入 #1

```
4 5
6 3
2 4
4 10
12 15
```

#### 输出 #1

```
2
```

### 说明/提示

**【样例解释】**

有 $4$ 滴水，初始位置分别在 $(6,3)$，$(2,4)$，$(4,10)$，$(12,15)$。水滴至少用 $5$ 秒时间先后落入花盆。花盆的宽度为 $2$ 是必须且足够的，此时把花盆放在 $x=4\dots6$ 的位置，它可以接到水滴 $1$ 和 $3$ ，之间的时间差为 $10-3=7$，满足条件。

**【数据范围】**

$40\%$ 的数据：$1 \le N \le 1000$ ，$1 \le D \le 2000$。

$100\%$ 的数据：$1 \le N \le 10 ^ 5$，$1 \le D \le 10 ^ 6$，$0\le x,y\le10^6$。

### 题解

这个吧，其实可以用单调性枚举的思想来做
输入的时候二维数组是无序的，我们先排个序，然后从第一列向右边开始遍历

每一次新加入一列，题目中要求的最小区间的长度只可能变长而不会变短
每一次删除左边的一列，题目中要求的最小区间的长度只可能变短而不会变长
综上 符合单调性的要求
所以可以直接套单调性枚举的模板
重点其实还是要看一下是怎么维护这个区间的，在第四章的时候我们用的是multiset来维护区间的最大值和最小值
在这里我们可以用单调双端队列来维护区间的最大值和最小值
代码如下，我的评价是有时间再看看第四章。
自己想的时候可以想到要维护最大值和最小值的区间，可惜不会写，麻了。

```cpp


template <typename T, template <typename> typename Cmp = greater>
class mono_deque : public deque<pair<int, T>>{ // Monotonic 单调
    public:
    //将元素保存到末尾并自动保持单调性
    mono_deque & push(int idx, const T &x) {
        while (!this->empty() && !Cmp<T>()(this->back().second, x)) this->pop_back();
        this->push_back({idx, x});
        return *this;
    }
    //将队列中坐标小于等于 idx 的元素删除
    mono_deque & shrink_to(int idx = -1) {
        while (!this->empty() && this->front().first <= idx) this->pop_front();
        return *this;
    }
    //获取当前队列中的极值
    T get_extremum() {return this->front().second;}
};

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
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> a(n);
    for (auto &[x, y] : a) cin >> x >> y;

    sort(a.begin(),a.end());

    mono_deque<int, greater> dec_q;
    mono_deque<int, less> inc_q;
    int ans = INT_MAX;
    increaseEnumerate(0, n - 1,
        [&](int l, int r) { //匹配函数
            return l <= r && dec_q.get_extremum()- inc_q.get_extremum() >= d; 
        },
        [&](int l, int r) { //插入函数
            inc_q.push(r, a[r].second);
            dec_q.push(r, a[r].second);
        },
        [&](int l, int r) {inc_q.shrink_to(l); dec_q.shrink_to(l);}, //删除函数
        [&](int l, int r) { // 更新函数
            if (r + 1 == n) return;
            ans = min(ans, a [r + 1].first - a[l].first);
        });
    cout << (ans == INT_MAX ? -1 : ans) << endl;
}
```















