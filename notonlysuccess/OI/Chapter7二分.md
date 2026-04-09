[TOC]

# <center>第七章 二分</center>

## Lead In
### Intro
> Q: 给你一个鸡蛋，用最少的次数找出从哪一层楼扔下去鸡蛋会碎？
很直观，不细说了，下面给出定义

!!! : 定义
    在一个答案区间内 $[Low, High]$
    存在一个函数 $f(x)$ 满足 $f(x) \rightarrow {False, True}$
    对于可能的解空间，必须满足两级分布，即前半部分为 False，后半部分为 True
    （或前半部分为 True，后半部分为 False）
    比如说在楼层问题中，到达某一层楼之前，鸡蛋都不会碎，之后鸡蛋都会碎

对于这种模型，就可以使用二分找到第一个 True 或者最后一个 False

实现
```cpp
int binary_search (int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (f(mid)) { //判断 True or False
            // 找第一个 True
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (low == high + 1 && f(low)) {
        cout << "not found\n";
        return -1; // 未找到符合条件的解
    }

    return low; // 返回第一个 True 的位置
    // return high + 1; // 也可以
    // return high; // 返回最后一个 False 的位置
}
```

模板(浮点数不可用)
```cpp
template<typename T, typename M> // M : match 函数
T get_first_macth(T low, T high, M match) {
    while (low <= high) {
        T mid = low + (high - low) / 2;
        if (match(mid)) hi = mid - 1;
        else low = mid + 1;
    }
    return low;
}
```
**注意这个模板 `false` 在前， `true` 在后**
时间复杂度 $O(\log{n})$


### 例 1 有序数组中是否存在目标
```
arr : 1 1 3 5 7 7 8    target = 5
idx : 0 1 2 3 4 5 6
res : F F F T T T T
```
```cpp
auto match = [&](int index) {
    return arr[index] >= target;
};

int index = get_first_macth(0, n - 1, match);

if (index == n || arr[index] != target) return false;
return true;
```

上面这一坨可以在c++中简化为
但是只能判断有没有，不能返回下标
```cpp
binary_search(arr.begin(), arr.end(), target);
binary_search(arr, arr + n, target); //左闭右开
```

### 例 2 有序数组中寻找第一个大于等于目标的下标
```cpp
auto match = [&](int index) {
    return arr[index] >= target;
};
int index = get_first_macth(0, n - 1, match);

return index; // index 可能等于 n
```
或者用 `lower_bound` 目标在数组中的第一个位置
相对应的还有 `upper_bound` 目标在数组中的最后一个位置的下一个位置
```cpp
lower_bound(arr.begin(), arr.end(), target) - arr.begin();
lower_bound(arr, arr + n, target) - arr; //左闭右开
```

### 例 3 有序数组中寻找最后一个小于目标的下标
```cpp
auto match = [&](int index) {
    return arr[index] >= target;
};
```
为了适应模板 改成 `>= target` 

### 例 4 最多将数组分成 $M$ 组， 每组之和不能超过 $X$, 求 $X$ 的最小值
朴素来讲，分成三步
- 枚举 $N$ 个元素最多划分成 $M$ 组的所有方案
- 在每种方案中，计算每组的和，取最大值
- 取所有方案中最大值的最小值

在这种思路下，第一步就会复杂度爆炸

**尝试交换顺序**
- 枚举 最大值 $X$ 的所有可能值 （下界为数组中最大值，上界为数组所有元素之和）
- 判断在 最大值为 $X$ 的情况下，是否能将数组划分成不超过 $M$ 组

第二步描述的实际上就是我们要求的 $match$ 函数
只要其满足两极性的条件，就可以用**二分来找到满足条件的**最小的 $X$


**两极性为何成立？**
若两极性成立，则必须满足如下要求
$match$ 中参数为当前枚举的最大值，返回的结果为是否可以划分为小于等于 $M$ 组

$$ 
\begin{aligned}
match(x) \rightarrow True \Rightarrow match(y) \rightarrow True | y > x \\
match(x) \rightarrow False \Rightarrow match(z) \rightarrow False | z < x \\
\end{aligned}
$$

可以抽象成
```cpp
int lo = *max_element(vec.begin(), vec.end());
int hi = accumulate(vec.begin(), vec.end(), 0);
int min_x = get_first_match(lo, hi, match);
```
tips: `lo` `hi`的取值直接用 `0`, `INT_MAX` 也是可以的，因为最多也只需要遍历 $\log_2 2^{31} = 31$ 次 没有什么区别
**粗略和精确的上下界区别并不大**

!!! : 小结 
    可称此类题目为 **二分答案** 类
    寻找符合某个条件的最小值或最大值
    直接求解困难
    找到一个满足两极性的 $match$ 函数
    使用二分进行求解

### 例 5 求解一元五次方程的根
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\二分 LeadIn.png" width="600"/>
  </div>
</div>

可以发现，函数的取值在区间 [-3, 3]之内并不满足单调性，但很明显对于 匹配函数 $f(x) \geq 0 $ 满足两极性，所以可以用二分法求解
但是这涉及到了浮点数二分的问题
```cpp
const double eps = 1e-6;
double lo = -3, hi = 3;
while (lo + eps < hi) {
    double mid = (lo + hi) / 2;
    if (match(mid)) hi = mid;
    else lo = mid;
}
return lo; // 或 hi
//return hi 也许
```

---


## 7.1 模板题 P2249 查找
### 题目描述

输入 $n$ 个不超过 $10^9$ 的单调不减的（就是后面的数字不小于前面的数字）非负整数 $a_1,a_2,\dots,a_{n}$，然后进行 $m$ 次询问。对于每次询问，给出一个整数 $q$，要求输出这个数字在序列中第一次出现的编号，如果没有找到的话输出 $-1$ 。

### 输入格式

第一行 $2$ 个整数 $n$ 和 $m$，表示数字个数和询问次数。

第二行 $n$ 个整数，表示这些待查询的数字。

第三行 $m$ 个整数，表示询问这些数字的编号，从 $1$ 开始编号。

### 输出格式

输出一行，$m$ 个整数，以空格隔开，表示答案。

### 输入输出样例 #1

#### 输入 #1

```
11 3
1 3 3 3 5 7 9 11 13 15 15
1 3 6
```

#### 输出 #1

```
1 2 -1 
```

### 说明/提示

数据保证，$1 \leq n \leq 10^6$，$0 \leq a_i,q \leq 10^9$，$1 \leq m \leq 10^5$

**本题输入输出量较大，请使用较快的 IO 方式。**

### 题解
模板题 what can I say
```cpp
template<typename T, typename M>
T get_first_match(T lo, T hi, M match) {
    while (lo <= hi) {
        T mid = lo + (hi - lo) / 2;
        if (match(mid)) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m; 
    cin >> n >> m;
    vector<int> vec(n);
    for (auto &x : vec) cin >> x;

    int target;

    auto match = [&](int mid) {
        return vec[mid] >= target;
    };

    while (m --) {
        cin >> target;
        int idx = get_first_match<int, decltype(match)>(0, n -1, match);
        cout << (target == vec[idx] ? idx + 1 : -1) << " ";
    }
}
```

---

## 7.2 LeetCode 410 分割数组的最大值

### 题目描述
给定一个非负整数数组 `nums` 和一个整数 `k` ，将数组分成 `k` 个非空的连续子数组，使得这 `k` 个子数组各自和的最大值 最小。返回该最小的最大子数组和。

### 示例
#### 示例 1：
输入：`nums = [7,2,5,10,8], k = 2`  
输出：`18  `
解释：将其分为 [7,2,5] 和 [10,8]，最大子数组和为 18。

#### 示例 2：
输入：`nums = [1,2,3,4,5], k = 2`  
输出：`9`

#### 示例 3：
输入：`nums = [1,4,4], k = 3`  
输出：`4`

### 输入格式
数组 `nums` 和整数 `k`。

### 输出格式
一个整数，表示分割后最小的最大子数组和。

### 约束
$1 \le |nums| \le 1000$  
$0 \le nums[i] \le 10^6$  
$1 \le k \le \min(50, |nums|)$

### 题解
思路前面说了，只需要枚举 最大子数组和 `X` 的所有可能值就好
match函数就定义为 判断在 最大子数组和为 `X` 的情况下，是否能将数组划分成不超过 `k` 组
```cpp
int main () {
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0)->sync_with_stdio(false);

    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (auto &x : nums) cin >> x;

    int lo = *max_element(nums.begin(), nums.end());
    int hi = accumulate(nums.begin(), nums.end(), 0);

    vector<int> PartialSum(n);
    partial_sum(nums.begin(), nums.end(), PartialSum.begin());

    // for (auto &x: PartialSum) {
    //     cout << x << " ";
    // }

    auto match = [&](int mid) {
        int l = 0, r = 0;
        int count = 0;
        while (r < n) {
            while (r < n && PartialSum[r] - (l == 0 ? 0 : PartialSum[l - 1]) <= mid) {
                r ++;
            }
            count ++;
            l = r;
        }
        return count <= k;
    };

    int x = get_first_match(lo, hi, match);
    cout << x << "\n";
}
```


## 7.3 Lq2191 卡牌
### 题目描述
这天，小明在整理他的卡牌。

他一共有 $n$ 种卡牌，第 $i$ 种卡牌上印有正整数数 $i$（$i \in [1, n]$），且第 $i$ 种卡牌现有 $a_i$ 张。

若有 $n$ 张卡牌，其中每种卡牌各一张，则称为一套牌。小明为了凑出尽可能多套牌，拿出了 $m$ 张空白牌，可在上面写上数 $i$ 将其当做第 $i$ 种牌，但第 $i$ 种牌最多手写 $b_i$ 张。

问：小明最多能凑出多少套牌？

### 输入格式
共 3 行：

- 第一行：两个正整数 $n, m$。  
- 第二行：$n$ 个正整数 $a_1, a_2, \dots, a_n$。  
- 第三行：$n$ 个正整数 $b_1, b_2, \dots, b_n$。

### 输出格式
一行，一个整数表示答案。

### 样例输入
```
4 5
1 2 3 4
5 5 5 5
```

### 样例输出
```
3
```

### 样例说明
这 5 张空白牌中, 拿 2 张写 1 , 拿 1 张写 2 , 这样每种牌的牌数就变为了 3,3,3,4, 可以凑出 3 套牌, 剩下 2 张空白牌不能再帮助小明凑出一套。

### 评测用例规模与约束
$1 \le n \le 2\times 10^5$  
$0 \le a_i, b_i \le 2n$  
$0 \le m \le n^2$

### 题解
思考的过程其实和 7.2 是类似的
正向来看，在确定了最多能补的牌 $m$ 和每一种牌能补的个数 $b_i$，我们只需要枚举每一种情况并判断其可实现的最多套数 $x$，但这必然超时
所以我们可以换思路，枚举最多可实现的套数 $x$， 判断给定套数下利用空白牌可否补全。

!!! : 当然，也是有要注意的点的：
    1. 不难发现，这个问题的解是符合两极性的，但是，与模板中相反， $x$ 较大时，不符合我们要的条件，较小时则符合条件，这意味着 $match$ 函数中判断 `true` `false` 应该反过来
    同时，模板中找的是 **第一个符合条件的值**，我们要找的问题其实对应到模板是 **最后一个不符合条件的值**，所以输出答案的时候要 `-1`
    2. 编写的时候注意上下界，建议直接 `0 - 1e9`

对于二分答案的问题，在枚举的过程中的时间复杂度是 $O(\log(n))$ 的，这意味着对于大多数题目来说，如果不想超时，$match$ 函数的时间复杂度最低也得是 $O(n)$，这个方法也许可以用于快速判断一个题是否可以化为二分答案类问题，以及如何思考 $match$ 函数的编写 

```cpp
int  main() {
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    long long  m; cin >> m;
    vector<int> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    auto match = [&](int mid) {
        long long cur = 0;
        for (int i = 0; i < n; i ++) {
            if (a[i] < mid) {
                if (b[i] < mid - a[i]) return true;
                cur += mid - a[i];
            } 

            if (cur > m) return true;
        }
        return false;
    };

    int lo = 0;
    int hi = 1e9;
    int ans = get_first_match(lo, hi, match);

    cout << ans - 1 << "\n";
}
```

---

## 7.4 P2678 [NOIP 2015 提高组] 跳石头

### 题目描述

一年一度的“跳石头”比赛又要开始了！

这项比赛将在一条笔直的河道中进行，河道中分布着一些巨大岩石。组委会已经选择好了两块岩石作为比赛起点和终点。在起点和终点之间，有 $N$ 块岩石（不含起点和终点的岩石）。在比赛过程中，选手们将从起点出发，每一步跳向相邻的岩石，直至到达终点。

为了提高比赛难度，组委会计划移走一些岩石，使得选手们在比赛过程中的最短跳跃距离尽可能长。由于预算限制，组委会至多从起点和终点之间移走 $M$ 块岩石（不能移走起点和终点的岩石）。

### 输入格式

第一行包含三个整数 $L,N,M$，分别表示起点到终点的距离，起点和终点之间的岩石数，以及组委会至多移走的岩石数。保证 $L \geq 1$ 且 $N \geq M \geq 0$。

接下来 $N$ 行，每行一个整数，第 $i$ 行的整数 $D_i\,( 0 < D_i < L)$， 表示第 $i$ 块岩石与起点的距离。这些岩石按与起点距离从小到大的顺序给出，且不会有两个岩石出现在同一个位置。

### 输出格式

一个整数，即最短跳跃距离的最大值。

### 输入输出样例 #1

#### 输入 #1

```
25 5 2 
2
11
14
17 
21
```

#### 输出 #1

```
4
```

### 说明/提示

#### 输入输出样例 1 说明

将与起点距离为 $2$ 和 $14$ 的两个岩石移走后，最短的跳跃距离为 $4$（从与起点距离 $17$ 的岩石跳到距离 $21$ 的岩石，或者从距离 $21$ 的岩石跳到终点）。

#### 数据规模与约定

对于 $20\%$的数据，$0 \le M \le N \le 10$。    
对于 $50\%$ 的数据，$0 \le M \le N \le 100$。  
对于 $100\%$ 的数据，$0 \le M \le N \le 50000,1 \le L 
 \le 10^9$。

### 题解
思路还是一样的
正向来想，给定了 $n$ 个石头可供选择，最多选 $M$ 个石头移除
我们要找最小区间的最大值，意味着我们要进行 $C^m_n$ 次选择，同时遍历整个数组来求得最小值，很明显，这是不可以接受的

所以还是逆向来想，我们二分查找 最小跳跃距离 `X`
关于解空间的两极性，可以这样想：假定最大的最小跳跃距离 为 `Y`， 那么对于大于 `Y` 的 `X`，给定的 $n, m$ 肯定无法满足要求，反之可以满足要求，所以我们要求的是**最后一个不满足要求的 `X`** 即$$[T, T, T, ..., T, F, F, F,..., F]$$ 这种类型

至于 $match$ 函数的编写，实际上用到了贪心的思想，如果两块相邻的石头的间隔小于 `X`，那么我们就移除后一块石头，并用再下一块石头重新计算间隔。

在具体编写的过程中，既然是从头到尾的遍历，那就尽量少用`while`循环，直接用 `for` 循环来实现，没有那么多细节需要思考

**如下所示，在跳出`while`循环后，`cnt` 还会自增，`i` 也会自增，所以此时判断究竟是什么导致跳出`while` 循环就十分复杂**
```cpp
    auto match = [&](int mid) {
        int cnt = 0;
        int interval = 0;

        for (int i = 1; i <= n + 1;) {
            if (stones[i] - stones[i - 1] >= mid) {i ++; continue;}
            else {
                while (interval < mid && i <= n + 1) {
                    interval += stones[i] - stones[i - 1];
                    i ++;
                    cnt ++;
                }
                if (interval < mid) return true;
                if (cnt > m + 1) return true;
                interval = 0;
            }
        }
        return false;
    };
```

**简洁又高效的写法如下，从头到尾直接遍历就好。`interval` 的利用也十分高效，如果区间符合要求，赋值为0就好，如果不是，直接 `cnt` 自增 1，省去了很多不必要的判断。每次循环结束都判断 `cnt` 和 `m` 的大小关系**
```cpp
    auto match = [&](int mid) {
        int cnt = 0;
        int interval = 0;

        for (int i = 1; i < n + 2; i ++) {
            interval += stones[i] - stones[i - 1];
            if (interval >= mid) {
                interval = 0;
                continue;
            } else {
                cnt ++;
            }
            if  (cnt > m) return true;
        }
        return false;
    };
```

完整代码如下
```cpp
int main() {
    int l, n, m;
    cin >> l >> n >> m;
    vector<int> stones (n + 2, 0);
    for (int i = 1; i <= n; i ++) {cin >> stones[i];}
    stones[n + 1] = l;

    int lo = 0;
    int hi = l + 1;
    auto match = [&](int mid) {
        int cnt = 0;
        int interval = 0;

        for (int i = 1; i < n + 2; i ++) {
            interval += stones[i] - stones[i - 1];
            if (interval >= mid) {
                interval = 0;
                continue;
            } else {
                cnt ++;
            }
            if  (cnt > m) return true;
        }
        return false;
    };

    int ans = get_first_match(lo, hi, match);
    cout << --ans << "\n";
}
```

---


## 7.5 P1024 [NOIP 2001 提高组] 一元三次方程求解

### 题目描述

有形如：$a x^3 + b x^2 + c x + d = 0$  这样的一个一元三次方程。给出该方程中各项的系数（$a,b,c,d$ 均为实数），并约定该方程存在三个不同实根（根的范围在 $-100$ 至 $100$ 之间），且根与根之差的绝对值 $\ge 1$。要求由小到大依次在同一行输出这三个实根(根与根之间留有空格)，并精确到小数点后 $2$ 位。

提示：记方程 $f(x) = 0$，若存在 $2$ 个数 $x_1$ 和 $x_2$，且 $x_1 < x_2$，$f(x_1) \times f(x_2) < 0$，则在 $(x_1, x_2)$ 之间一定有一个根。

### 输入格式

一行，$4$ 个实数 $a, b, c, d$。

### 输出格式

一行，$3$ 个实根，从小到大输出，并精确到小数点后 $2$ 位。

### 输入输出样例 #1

#### 输入 #1

```
1 -5 -4 20

```

#### 输出 #1

```
-2.00 2.00 5.00

```

### 题解
并没有那么显然，在Lead In 中提到的浮点数二分法,适用的前提是在一段区间内，前一段子区间的函数值的符号与后一段子区间的函数值的符号不同。

也就是说，我们不可以直接在原始区间上二分寻找答案。

但是如果是在符合这个条件的区间内，我们还是可以用二分法去找到答案的。
现在的问题就变成了如何找到这样的区间


题目给了**根与根之差的绝对值 $\ge 1$** 的条件，这就意味着在区间 $[-100, 100]$ 上，任意长度为 $1$ 的子区间内，最多只能有一个根
**所以我们可以枚举所有长度为 $1$ 的子区间**，寻找符号不同的子区间，然后在这些子区间内使用浮点数二分法寻找根

```cpp
const double eps = 1e-6;
int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0)->sync_with_stdio(false);

    double a, b, c, d;
    cin >> a >> b >> c >> d;
    auto f = [&](double x) {
        return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
    };

    vector<double> roots;
    //处理整数的情况
    for (int x = -100; x <= 100; x ++) if(abs(f(x)) < eps) roots.push_back(x);


    for (int x = -100; x <= 99; x ++) {
        double f1 = f(x);
        double f2 = f(x + 1);
        if (f1 * f2 > -eps) continue;
        double lo = x, hi = x + 1;
        while (lo + eps < hi) {
            double mid = (lo + hi) / 2;
            if (f(mid) * f1 > 0) lo = mid;
            else hi = mid;
        }
        roots.push_back(lo);
    }

    
    sort(roots.begin(), roots.end());
    cout << fixed << setprecision(2);
    for (auto &x : roots) cout << x << " ";
}
```

小坑，该题思路与前几题侧重点不同，需多加注意。

---

## 7.6 Lq17098 第k小的和
### 题目描述
给定两个序列 $A, B$，长度分别为 $n, m$。

设另有一个序列 $C$ 中包含了 $A, B$ 中的数两两相加的结果（$C$ 中共有 $n\times m$ 个数）。问 $C$ 中第 $K$ 小的数是多少。请注意重复的数需要计算多次。例如序列 $1,1,2,3$ 中，最小和次小都是 $1$，而 $3$ 是第 $4$ 小。

### 输入格式
输入的第一行包含三个整数 $n, m, K$，相邻两个整数之间使用一个空格分隔。

第二行包含 $n$ 个整数，分别表示 $A_1, A_2, \dots, A_n$，相邻两个整数之间使用一个空格分隔。

第三行包含 $m$ 个整数，分别表示 $B_1, B_2, \dots, B_m$，相邻两个整数之间使用一个空格分隔。

### 输出格式
输出一行包含一个整数，表示答案（即 $C$ 中第 $K$ 小的数）。

### 样例输入
```
3 4 5
1 3 4
2 3 5 6
```

### 样例输出
```
6
```

### 评测用例规模与约定
- 对于 $40\%$ 的评测用例，$n, m \le 5000$，$A_i, B_i \le 1000$；
- 对于所有评测用例，$1 \le n,m \le 10^5$，$1 \le A_i, B_i \le 10^9$，$1 \le K \le n\times m$。

### 题解
根据题目给的条件，如果直接枚举的话，生成答案的矩阵的复杂度是 $O(n \times m)$，去找到第 $k$ 小的数的复杂度也是 $O(n \times m)$，总复杂度为 $O(n \times m)$，显然会超时

所以我们还是要用二分答案的思路来解题
可以很容易地想到，如果有一个数 $X$ 大于第 $k$ 小的数，那么比 $X$ 大的数一定满足条件。进而可以很容易证明相加的序列满足两极性。

**接下来就是如何二分寻找答案。**
如果一个数是第 $k$ 小的数，那么小于它的数的个数一定是 $k - 1$ 个
所以我们可以定义 $match$ 函数为：判断小于 `mid` 的数的个数是否大于或等于 $k$。

**当然，这只是第一层二分，枚举的是 $X$**
**我们要找的是在每一列中，小于 `mid` 的数的个数**

在match函数中，如果我们直接遍历计算小于 `mid` 的数的个数，那么复杂度是 $O(n \times m)$，显然还是会超时
所以我们需要在match函数中再使用二分来计算小于 `mid` 的数的个数

这里有个捷径 **upper_bound**函数
```cpp
upper_bound(b.begin(), b.end(), mid - a[i]) - b.begin();
```
**函数找到的是第一个大于 `mid - a[i]` 的位置，所以还要减掉 `b.begin()` 得到小于等于 `mid - a[i]` 的个数**

ac代码如下，注意开int和long long
```cpp
template<typename T, typename M>
T get_first_match(T lo, T hi, M match) {
    while (lo <= hi) {
        T mid = lo + (hi - lo) / 2;
        if (match(mid)) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0)->sync_with_stdio(false);
    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<int> a(n);
    vector<int> b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    auto match = [&](int mid) {
        long long cnt = 0;
        for (auto A: a) {
            cnt += (upper_bound(b.begin(), b.end(), mid - A) - b.begin());
        }
        return cnt >= k; 
    };

    long long ans = get_first_match(a[0] + b[0], a[n - 1] + b[m - 1], match);
    cout << ans << "\n";
}
```

---

## 7.7 Lq2129 技能升级  

!!! :  绝世好题，主要看AC代码中边界条件的处理

### 题目描述
小蓝最近正在玩一款 RPG 游戏。他的角色一共有 $N$ 个可以加攻击力的技能。

其中第 $i$ 个技能首次升级可以提升 $A_i$ 点攻击力，以后每次升级增加的点数都会减少 $B_i$。第 $\lceil \frac{A_i}{B_i} \rceil$ 次之后，再升级该技能将不会改变攻击力。

现在小蓝可以总计升级 $M$ 次技能，他可以任意选择升级的技能和次数。请你计算小蓝最多可以提高多少点攻击力？

### 输入格式
输入第一行包含两个整数 $N$ 和 $M$。

以下 $N$ 行每行包含两个整数 $A_i$ 和 $B_i$。

### 输出格式
输出一行包含一个整数表示答案（最多能提高的总攻击力）。

### 样例输入
```
3 6
10 5
9 2
8 1
```

### 样例输出
```
47
```

### 评测用例规模与约定
- 对于 $40\%$ 的评测用例，$1 \le N, M \le 1000$；
- 对于 $60\%$ 的评测用例，$1 \le N \le 10^4,\; 1 \le M \le 10^7$；
- 对于所有评测用例，$1 \le N \le 10^5,\; 1 \le M \le 2\times 10^9,\; 1 \le A_i, B_i \le 10^6$。


### 题解
初始的思路有点像贪心，同样是二分查找答案，维护一个优先队列，每次升级都选择当前能提升攻击力最多的技能进行升级，同时按规则存入下一次更新用到能加的点数进入到优先队列中。按照这个思路就可以编写match函数。
**要注意的是mid越大越不可能符合条件，所以解的两极性是相反的。**
可是我们之前论证过，想要不超时，match函数的时间复杂度得是 $O(n)$ 的，而优先队列每一次插入删除操作的时间复杂度是 $O(\log{n})$ 的，进而每次match的时间复杂度是 $O(M \log{n})$ 的，显然会超时。

接下来是超时版
``` cpp
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> b(n);
    priority_queue<pair<int, int>> pq;

    for (int i = 0; i < n; i ++) {
        int x; cin >> x;
        pq.push({x, i});
        cin >> b[i];
    }

    // while(!pq.empty()) {
    //     cout << pq.top().first << " " << pq.top().second << endl;
    //     pq.pop();
    // }

    // 越大越不可能，所以两极性是反过来的
    auto match = [&](long long mid) {
        priority_queue<pair<int, int>> temp_pq = pq;
        int cnt = 0; long long cur = 0;
        while(!temp_pq.empty() && cnt < m) {
            auto [price, idx] = temp_pq.top();
            temp_pq.pop();
            cur += price * 1ll; cnt ++;
            
            if (price - b[idx] > 0) {
                temp_pq.push({price - b[idx], idx});
            }
        }
        if (cur <mid) return true;
        else return false;
    };

    long  long ans = get_first_match(0ll, (long long)1e15, match);
    cout << ans - 1 << "\n";
}
```

--- 

现在的问题是如何将match函数的时间复杂度降低到 $O(n)$ 的级别呢？
要降到 $O(n)$ 的级别，**我们可以借鉴上一题的思路**

**我们可以遍历查找每一个技能在 `mid` 的条件下，最多能升级多少次**
即是说我们要找到对于每一个技能，当 当前能加的技能点小于多少 **(即本题要求的`mid`)** 时，就不再升级，即寻找`mid = ?`时，选中的数字尽可能多又尽可能大。
比如以下例子
```cpp
10 5 0
 9 6 3 0
11 9 7 5 3 1 0
```
假定我给的最多升级次数是 `m = 6`， 那么通过二分枚举，可以发现最小的`mid`是 6.
在计算答案时，只需要按照这个过程，用等差数列求和的性质求和就行。

**但是还有个问题，加入一开始给定的最大升级次数是 `m = 7` 呢?**
要解决这个问题，我们可以先看看当 `mid` 取不同的值的时候，对应到最大升级次数是多少
- `mid = 6` 对应的最大升级次数是 `6`
- `mid = 5` 对应的最大升级次数是 `8`

**也就是说，假如给定的最大升级次数夹在 `6` 和 `8` 之间，那么，我们要补的那个数就一定是当前的 `mid = 6` 再减 1，即5**
**同理，假设把其中一个`5`换成`4`，那么 `mid = 5` 对应的最大升级次数就变成了 `7`，就不会出现这个问题了**



接下来是 AC 代码
```cpp
int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout.tie(0)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> skills(n);
    for (auto &[a, b] : skills) cin >> a >> b;
    
    auto match = [&](int x) {
        long long cnt = 0;
        for (auto &[a, b] :skills) {
            if (a < x) continue;
            cnt += (a - x) / b + 1;
        }
        return cnt <= m;
    };
    //注意到这里其实是前面不符合条件，后面符合
    int maxSkills = get_first_match(1, 1000000000, match);

    long long sum = 0;
    int totalCnt = 0;
    for (auto &[a, b] : skills) {
        if (a < maxSkills) continue;
        int cnt = (a - maxSkills) / b + 1;
        sum += (a + (a - (cnt - 1) * b)) * 1ll * cnt / 2;
        totalCnt += cnt;
    }

    if (totalCnt < m) {
        sum += (long long)(maxSkills - 1) * (m - totalCnt);
    }
    cout << sum << "\n";
}
```

---

## 7.8 Lq180 三体攻击

!!! : 主要是三维差分

### 题目描述
三体人将对地球发起攻击。为了抵御攻击，地球人派出 $A\times B\times C$ 艘战舰，在太空中排成一个 $A$ 层 $B$ 行 $C$ 列的立方体。其中，第 $i$ 层第 $j$ 行第 $k$ 列的战舰（记为战舰 $(i,\,j,\,k)$）的生命值为 $d(i,\,j,\,k)$。

三体人将会对地球发起 $m$ 轮“立方体攻击”，每次攻击会对一个小立方体中的所有战舰都造成相同的伤害。具体地，第 $t$ 轮攻击用 $7$ 个参数 $l_{a_t},\,r_{a_t},\,l_{b_t},\,r_{b_t},\,l_{c_t},\,r_{c_t},\,h_t$ 描述；

所有满足 $i\in[l_{a_t},\,r_{a_t}],\;j\in[l_{b_t},\,r_{b_t}],\;k\in[l_{c_t},\,r_{c_t}]$ 的战舰 $(i,\,j,\,k)$ 会受到 $h_t$ 的伤害。如果一个战舰累计受到的总伤害超过其防御力，那么这个战舰会爆炸。

地球指挥官希望你能告诉他，第一艘爆炸的战舰是在哪一轮攻击后爆炸的。

### 输入格式
第一行包括 $4$ 个正整数 $A,\,B,\,C,\,m$；

第二行包含 $A\times B\times C$ 个整数，其中第 $((i-1)\times B + (j-1))\times C + (k-1) + 1$ 个数为 $d(i,\,j,\,k)$；

第 $3$ 到第 $m+2$ 行中，第 $(t-2)$ 行包含 $7$ 个正整数 $l_{a_t},\,r_{a_t},\,l_{b_t},\,r_{b_t},\,l_{c_t},\,r_{c_t},\,h_t$。

约束：$A\times B\times C \le 10^6,\; m \le 10^6,\;0 \le d(i,\,j,\,k),\,h_t \le 10^9$。

### 输出格式
输出第一个爆炸的战舰是在哪一轮攻击后爆炸的（保证一定存在这样的战舰）。

### 输入输出样例
#### 输入
```
2 2 2 3
1 1 1 1 1 1 1 1
1 2 1 2 1 1 1
1 1 1 2 1 2 1
1 1 1 1 1 1 2
```

#### 输出
```
2
```

### 题解
还是进行复杂度分析：
如果我们每一轮都暴力地直接统计每一个战舰的受伤情况并判断是否击沉，那么时间复杂度是 $O(A \times B \times C \times m)$，是 $10^{12}$ 量级的，这是不可接受的。

所以我们会很自然地想到在每一次统计受损情况时，使用差分来进行优化
但是，如果从第一次攻击开始使用差分，那么每轮攻击过后还需要把差分还原成原数组，时间复杂度依然是 $O(A \times B \times C \times m)$ 量级的，等于没用。

所以我们用二分答案的思路来解题
我们二分查找第一个产生击沉的战舰的攻击轮次 `mid`
在 `match` 函数中，我们只需要把前 `mid` 轮攻击的伤害都累加到差分数组中，最后再还原成原数组，判断是否有战舰被击沉。

**当然，本题的二分策略是很好想的，主要问题在于如何实现三维差分**
不要去想三维每个点是什么样子的，而是去想这个点是几个维度的交点，右交点则为减，左交点为加，最后把符号乘起来就是这个点的值
```cpp

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int A, B, C, m;
    cin >> A >> B >> C >> m;
    // 层 列 行
    auto hp = vector(A + 2, vector(B + 2, vector<int>(C + 2)));
    for (int i = 1; i <= A; i ++) {
        for (int j = 1; j <= B; j ++) {
            for (int k = 1; k <= C; k ++) {
                cin >> hp[i][j][k];
            }
        }
    }
    //每一次攻击用元组存下来
    vector<tuple<int, int, int, int, int, int, int>> attacks(m);
    for (auto &[a, b, c, d, e, f, g] : attacks) {
        cin >> a >> b >> c >> d >> e >> f >> g;
    }

    auto match = [&](int mid) {
        auto diff = vector(A + 2, vector(B + 2, vector<long long>(C + 2)));
        for (int i = 0; i < mid; i ++) {
            auto [la, ra, lb, rb, lc, rc, d] = attacks[i];
            //接下来是三维差分 类比想想一维，左边的加，右边的减
            // 三个都在左边，加 d
            diff[la][lb][lc] += d;
            // 两个在左边，一个在右边，减 d
            diff[la][lb][rc + 1] -= d;
            diff[la][rb + 1][lc] -= d;
            diff[ra + 1][lb][lc] -= d;
            // 一个在左边，两个在右边，加 d
            diff[la][rb + 1][rc + 1] += d;
            diff[ra + 1][lb][rc + 1] += d;
            diff[ra + 1][rb + 1][lc] += d;
            // 三个都在右边，减 d
            diff[ra + 1][rb + 1][rc + 1] -= d;
        }
        // 三维前缀和
        for (int i = 1; i <= A; i ++) {
            for (int j = 1; j <= B; j ++) {
                for (int k = 1; k <= C; k ++) {
                    diff[i][j][k] += diff[i][j][k-1]
                                  +  diff[i][j-1][k]
                                  +  diff[i-1][j][k]
                                  -  diff[i-1][j-1][k]
                                  -  diff[i-1][j][k-1]
                                  -  diff[i][j-1][k-1]
                                  +  diff[i-1][j-1][k-1];
                    if (diff[i][j][k] > hp[i][j][k]) return true;
                }
            }
        }
        return false;
    };
    int ans = get_first_match(1, m, match);
    cout << ans << endl;
}
```

---


## 7.9 P1083 借教室

!!! : 类似 7.8 一维差分和前缀和

### 题目描述

在大学期间，经常需要租借教室。大到院系举办活动，小到学习小组自习讨论，都需要向学校申请借教室。教室的大小功能不同，借教室人的身份不同，借教室的手续也不一样。

面对海量租借教室的信息，我们自然希望编程解决这个问题。

我们需要处理接下来 $n$ 天的借教室信息，其中第 $i$ 天学校有 $r_i$ 个教室可供租借。共有 $m$ 份订单，每份订单用三个正整数描述，分别为 $d_j,s_j,t_j$，表示某租借者需要从第 $s_j$ 天到第 $t_j$ 天租借教室（包括第 $s_j$ 天和第 $t_j$ 天），每天需要租借 $d_j$ 个教室。

我们假定，租借者对教室的大小、地点没有要求。即对于每份订单，我们只需要每天提供 $d_j$ 个教室，而它们具体是哪些教室，每天是否是相同的教室则不用考虑。

借教室的原则是先到先得，也就是说我们要按照订单的先后顺序依次为每份订单分配教室。如果在分配的过程中遇到一份订单无法完全满足，则需要停止教室的分配，通知当前申请人修改订单。这里的无法满足指从第 $s_j$ 天到第 $t_j$ 天中有至少一天剩余的教室数量不足 $d_j$ 个。

现在我们需要知道，是否会有订单无法完全满足。如果有，需要通知哪一个申请人修改订单。

### 输入格式

第一行包含两个正整数 $n,m$，表示天数和订单的数量。

第二行包含 $n$ 个正整数，其中第 $i$ 个数为 $r_i$，表示第 $i$ 天可用于租借的教室数量。

接下来有 $m$ 行，每行包含三个正整数 $d_j,s_j,t_j$，表示租借的数量，租借开始、结束分别在第几天。

每行相邻的两个数之间均用一个空格隔开。天数与订单均用从 $1$ 开始的整数编号。

### 输出格式

如果所有订单均可满足，则输出只有一行，包含一个整数 $0$。

否则（订单无法完全满足）输出两行，第一行输出一个负整数 $-1$，第二行输出需要修改订单的申请人编号。

### 输入输出样例 #1

#### 输入 #1

```
4 3 
2 5 4 3 
2 1 3 
3 2 4 
4 2 4
```

#### 输出 #1

```
-1 
2
```

### 说明/提示

【输入输出样例说明】

第 $1$ 份订单满足后，$4$ 天剩余的教室数分别为 $0,3,2,3$。第 $2$ 份订单要求第 $2$ 天到第 $4$ 天每天提供 $3$ 个教室，而第 $3$ 天剩余的教室数为 $2$，因此无法满足。分配停止，通知第 $2$ 个申请人修改订单。

【数据范围】

对于 $10\%$ 的数据，有 $1\le n,m\le 10$；

对于 $30\%$ 的数据，有 $1\le n,m\le 1000$；

对于 $70\%$ 的数据，有 $1 \le n,m \le 10^5$；

对于 $100\%$ 的数据，有 $1 \le n,m \le 10^6$，$0 \le r_i,d_j\le 10^9$，$1 \le s_j\le t_j\le n$。

### 题解
这道题暴力地想的话，每一份订单我们都遍历两次数组以观察是否满足条件，时间复杂度为 $O(n \times m)$，是 $10^{12}$ 量级的，显然会超时
所以可以很容易想到，人越少，越容易满足条件，反之亦然，所以我们可以对满足订单的人数进行二分查找
在match函数中，主要用到差分和前缀和来降低复杂度，注意一些差分和前缀和的细节，还有二分模板在全false下输出的为上界 + 1 的问题

AC代码如下，记得开 long long
```cpp

int main() {
    int  n, m;
    cin >> n >> m;
    vector<int> rooms(n);
    for (auto &x : rooms) cin >> x;

    vector<tuple<int, int, int>> rent(m);
    for (auto & [d, s, t] : rent) cin >> d >> s >> t;

    auto match = [&](int mid) {
        vector<long long> diff(n + 2, 0); // 差分的小trick 要开大两格，分别在首尾，避免越界
        for (int i = 0; i < mid; i ++) {
            auto &[d, s, t] = rent[i];
            diff[s] += d;
            diff[t + 1] -= d;
        }
        for (int i = 1; i <= n; i ++) { //在尾部开多的那一格在前缀和的时候不用考虑
            diff[i] += diff[i - 1];
            if (diff[i] > rooms[i - 1]) return true;
        }
        return false;
    };

    int ans = get_first_match(0, m, match);
    if (ans == m + 1) cout << 0 << endl; //注意越界条件，二分找不到的时候（即全false，输出的是m + 1）
    else cout << -1 << endl << ans << endl;
}
```

--- 

## 7.10 P1314 [NOIP 2011 提高组] 聪明的质监员

!!! : 一眼二分，我已急哭，前缀和，噫嘘唏！

### 题目描述

小 T 是一名质量监督员，最近负责检验一批矿产的质量。这批矿产共有 $n$ 个矿石，从 $1$ 到 $n$ 逐一编号，每个矿石都有自己的重量 $w_i$ 以及价值 $v_i$。检验矿产的流程是：

1. 给定 $m$ 个区间 $[l_i,r_i]$；
2. 选出一个参数 $W$；
3. 对于一个区间 $[l_i,r_i]$，计算矿石在这个区间上的检验值 $y_i$：

$$y_i=\sum\limits_{j=l_i}^{r_i}[w_j \ge W] \times \sum\limits_{j=l_i}^{r_i}[w_j \ge W]v_j$$  

其中 $j$ 为矿石编号，$[p]$ 是指示函数，若条件 $p$ 为真返回 $1$，否则返回 $0$。

这批矿产的检验结果 $y$ 为各个区间的检验值之和。即：$\sum\limits_{i=1}^m y_i$。

若这批矿产的检验结果与所给标准值 $s$ 相差太多，就需要再去检验另一批矿产。小 T 不想费时间去检验另一批矿产，所以他想通过调整参数 $W$ 的值，让检验结果尽可能的靠近标准值 $s$，即使得 $|s-y|$ 最小。请你帮忙求出这个最小值。

### 输入格式

第一行包含三个整数 $n,m,s$，分别表示矿石的个数、区间的个数和标准值。

接下来的 $n$ 行，每行两个整数，中间用空格隔开，第 $i+1$ 行表示 $i$ 号矿石的重量 $w_i$ 和价值 $v_i$。

接下来的 $m$ 行，表示区间，每行两个整数，中间用空格隔开，第 $i+n+1$ 行表示区间 $[l_i,r_i]$ 的两个端点 $l_i$ 和 $r_i$。注意：不同区间可能重合或相互重叠。

### 输出格式

一个整数，表示所求的最小值。

### 输入输出样例 #1

#### 输入 #1

```
5 3 15 
1 5 
2 5 
3 5 
4 5 
5 5 
1 5 
2 4 
3 3 
```

#### 输出 #1

```
10

```

### 说明/提示

【输入输出样例说明】

当 $W$ 选 $4$ 的时候，三个区间上检验值分别为 $20,5,0$，这批矿产的检验结果为 $25$，此时与标准值 $S$ 相差最小为 $10$。

【数据范围】

对于 $10\%$ 的数据，有 $1 ≤n,m≤10$；

对于 $30\%$ 的数据，有 $1 ≤n,m≤500$；

对于 $50\%$ 的数据，有 $1 ≤n,m≤5,000$；
 
对于 $70\%$ 的数据，有 $1 ≤n,m≤10,000$；

对于 $100\%$ 的数据，有 $1 ≤n,m≤200,000$，$0 < w_i,v_i≤10^6$，$0 < s≤10^{12}$，$1 ≤l_i ≤r_i ≤n$。

### 题解
初上手，不妨顺着题目的思路，可以发现，**如果 $W$ 越大，那么满足条件的矿石就越少，检验结果 $y$ 就越小，反之亦然**
也就是说，一般是来说（即 $y$ 的最小值比 $s$ 小的情况；如果大于的话直接就取这个最小值了，算是一种特殊情况），**$y - s$ 会有一个 0 点**，在这个点左侧， 这个值都大于0，在这个点右侧，这个值都小于0，**符合两极性**

而且，可以很容易地得出， $y - s$ 的最小值位于这个零点的“两侧”

**所以我们可以用二分法来寻找这个 0 点**
在match函数中，我们需要计算当 $W$ 取某个值时，求得的 $y$ 与 $s$ 的差值，并判断其正负，并最后找到第一个满足 $y - s < 0$ 的 $W$ 的值，最后比较两边的值，输出最小的那个就行。

**接下来问题就是如何在match函数计算出 $y$ 的值**
按照我们之前的论证，这个函数的时间复杂度是 $O(n)$ 的。
因为每次计算的区间都有 $m$ 个，所以每个区间的计算都要是 $O(1)$ 的，才能保证总的时间复杂度是 $O(n)$ 级别的。
所以对于每一个 $W$， 计算前，**先计算出满足条件的重量和价值的前缀和数组**，时间复杂度是 $O(n)$ ，然后每个操作都是 $O(1)$ 的，这样就不会超时了。

代码如下，回去看前缀和
```cpp
//7.10
int main() {
    int n, m;
    long long s;
    cin >> n >> m >> s;
    vector<pair<int, int>> stones(n + 1);
    int maxW = 0;
    for (int i = 1; i < n + 1; i ++){
        cin >> stones[i].first >> stones[i].second;
        maxW = max(maxW, stones[i].first);
    }
    vector<pair<int, int>> segs(m);
    for (auto &[a, b] : segs) cin >> a >> b;

    auto calc = [&](int w) { // 噫嘘唏，前缀和！
        vector<int> cnt (n + 1);
        vector<long long> val (n + 1);
        for (int i = 1; i <= n; i ++) {
            cnt[i] = cnt[i - 1] + (stones[i].first >= w);
            val[i] = val[i - 1] + (stones[i].first >= w) * stones[i].second;
        }
        long long total = 0; 
        for (auto &[l, r]: segs) {
            total += (cnt[r] - cnt[l - 1]) * (val[r] - val[l - 1]) * 1ll;
        }
        return total;
    };

    auto match = [&](int mid) {
        return calc(mid) < s;
    };

    int minW = get_first_match(1, maxW, match);

    long long sub1 = abs(calc(minW) - s);
    long long sub2 = abs(calc(minW - 1) - s);

    cout << (sub1 < sub2 ? sub1 : sub2) << "\n";
}
```

---

## 7.11 Lq3544 管道

!!! : 开数组之前想想 大小为 $10^9$ 的 int类型 vector数组有 8GB 哦

### 题目描述
有一根长度为 $len$ 的横向的管道，该管道按照单位长度分为 $len$ 段，每一段的中央有一个可开关的阀门和一个检测水流的传感器。

一开始管道是空的，位于 $L_i$ 的阀门会在 $S_i$ 时刻打开，并不断让水流入管道。

对于位于 $L_i$ 的阀门，它流入的水在 $T_i$ ($T_i \geq S_i$) 时刻会使得从第 $L_i - (T_i - S_i)$ 段到第 $L_i + (T_i - S_i)$ 段的传感器检测到水流。

求管道中每一段中间的传感器都检测到有水流的最早时间。

### 输入格式
输入的第一行包含两个整数 $n, len$，用一个空格分隔，分别表示会打开的阀门数和管道长度。

接下来 $n$ 行每行包含两个整数 $L_i, S_i$，用一个空格分隔，表示位于第 $L_i$ 段管道中央的阀门会在 $S_i$ 时刻打开。

### 输出格式
输出一行包含一个整数表示答案。

### 样例输入
```
3 10
1 1
6 5
10 2
```

### 样例输出
```
5
```

### 评测用例规模与约定
- 对于 $30\%$ 的评测用例，$n \leq 200$，$S_i, len \leq 3000$；
- 对于 $70\%$ 的评测用例，$n \leq 5000$，$S_i, len \leq 10^5$；
- 对于所有评测用例，$1 \leq n \leq 10^5$，$1 \leq S_i, len \leq 10^9$，$1 \leq L_i \leq len$，$L_{i-1} < L_i$。

### 题解

初版，二分枚举符合条件的时刻，但是爆内存

```cpp
int main() {
    long long n, len;
    cin >> n >> len;
    vector<pair<int, int>> sges(n);
    for (auto &[l, s] : sges) cin >> l >> s;

    auto match = [&](long long mid) {
        vector<long long> pipe(len + 2, 0);
        for (auto &[l, s] :sges) {
            if (mid >= s) {
                pipe[max(l - (mid - s), 1ll )] += 1;
                pipe[min(l + (mid - s) + 1, len + 1)] -= 1;
            }  
        }
        for (int i = 1; i <= len; i ++) {
            pipe[i] += pipe[i - 1];
            if (pipe[i] == 0) return false;
        }
        return true;
    };

    int ans = get_first_match(1ll, (long long)1000000000, match);
    cout << ans << endl;
}
```

实际上，这道题可以转换为一个区间覆盖的问题
对于每个阀门，计算出 $T$ 时刻它能覆盖的区间，最后把这些区间按照左端点排序，贪心地选择区间来覆盖 $[1, len]$，如果能覆盖成功，那么这个 $T$ 就是满足条件的时刻

```cpp
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, len;
    cin >> n >> len;
    vector<pair<int, int>> pipes(n);
    for (auto &[x, s] : pipes) cin >> x >> s;

    auto match = [&](int time) {
        vector<pair<int, long long>> segs;
        for (auto &[x, s] :pipes) {
            int delta = time - s;
            if (delta < 0) continue;
            segs.emplace_back(x- delta, x + delta);
        }
        sort(segs.begin(), segs.end());
        long long maxRight = 0;
        for (auto &[l, r] : segs) {
            if (l <= maxRight + 1) {
                maxRight = max(maxRight, r);
            } else {
                return false;
            }
        }
        return maxRight >= len;
    };

    int ans = get_first_match(1, INT_MAX, match);
    cout << ans << "\n";
}
```

在每个match函数中我们都要进行一次排序，但是可以发现，不管处在那一时刻，每个阀门左端点的相对顺序都是一样的，所以这个排序我们可以放到开头来做
**注意比较的是 $L_i - (Time - S_i)$ 即 $L_i + S_i$**

```cpp
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, len;
    cin >> n >> len;
    vector<pair<int, int>> pipes(n);
    for (auto &[x, s] : pipes) cin >> x >> s;

    sort(pipes.begin(), pipes.end(), [](auto &a, auto &b) {
        return a.first + a.second < b.first + b.second; // 按照 s 升序排序
    });

    auto match = [&](int time) {
        vector<pair<int, long long>> segs;
        for (auto &[x, s] :pipes) {
            int delta = time - s;
            if (delta < 0) continue;
            segs.emplace_back(x- delta, x + delta);
        }
        long long maxRight = 0;
        for (auto &[l, r] : segs) {
            if (l <= maxRight + 1) {
                maxRight = max(maxRight, r);
            } else {
                return false;
            }
        }
        return maxRight >= len;
    };

    int ans = get_first_match(1, INT_MAX, match);
    cout << ans << "\n";
}
```

---

## 7.12 Lq19705 成绩统计

### 题目描述
小蓝的班上有 $n$ 个人，一次考试之后小蓝想统计同学们的成绩，第 $i$ 名同学的成绩为 $a_i$。当小蓝统计完前 $x$ 名同学的成绩后，他可以从 $1 \sim x$ 中选出任意 $k$ 名同学的成绩，计算出这 $k$ 个成绩的方差。小蓝至少要检查多少个人的成绩，才有可能选出 $k$ 名同学，他们的方差小于一个给定的值 $T$？

提示：
$k$ 个数 $v_1, v_2, \dots, v_k$ 的方差 $\sigma^2$ 定义为: $\sigma^2 = \frac{\sum_{i=1}^k (v_i - \bar{v})^2}{k}$，其中 $\bar{v}$ 表示 $v$ 的平均值，$\bar{v} = \frac{\sum_{i=1}^k v_i}{k}$。

### 输入格式
输入的第一行包含三个正整数 $n, k, T$，相邻整数之间使用一个空格分隔。

第二行包含 $n$ 个正整数 $a_1, a_2, \dots, a_n$，相邻整数之间使用一个空格分隔。

### 输出格式
输出一行包含一个整数表示答案。如果不能满足条件，输出 $-1$。

### 样例输入

```
5 3 1
3 2 5 2 3
```

### 样例输出

```
4
```

### 样例说明
检查完前三名同学的成绩后，只能选出 $3, 2, 5$，方差为 $1.56$；

检查完前四名同学的成绩后，可以选出 $3, 2, 2$，方差为 $0.33 < 1$，所以答案为 $4$。

### 评测用例规模与约定
- 对于 $10\%$ 的评测用例，保证 $1 \leq n, k \leq 10^2$；
- 对于 $30\%$ 的评测用例，保证 $1 \leq n, k \leq 10^3$；
- 对于所有评测用例，保证 $1 \leq n, k \leq 10^5$，$1 \leq T \leq 2^{31} - 1$。

### 题解
可以发现，$x$ 越大，选出 $k$ 个同学的成绩的方差就越小，所以这个问题是具有两极性的，可以用二分法来解决。所以可以二分寻找满足条件的 $x$ 的最小值
对于每次二分，我们的问题转换为 **在 $x$ 个数中，选出 $k$ 个数，使其方差最小。**

初始思路是对选出来的数进行排序，然后单调性枚举，滑动窗口更新最小值
在每个match函数中，滑动窗口这一个操作的时间复杂度是 $O(n)$ 级别的，也就是说，对于每一个窗口内的数求方差必须是 $O(1)$ 级别的

所以我们需要在滑动窗口中维护一些前缀和来帮助我们快速地计算出方差的值
以下是数学推导

$$
\begin{aligned}
\sum\limits_{i=1}^k (v_i - \bar{v})^2  &= \sum\limits_{i=1}^k v_i^2 - 2\bar{v}\sum\limits_{i=1}^k v_i + k\bar{v}^2 
\end {aligned}
$$

式子中第一项在每次滑动窗口更新时可以用前缀和直接更新；第三项的平均数可以通过前缀和来更新； 第二项的 $\sum\limits_{i=1}^k v_i$ 则是直接由前缀和数组就可以直接求得。

以下是 AC 代码
```cpp
int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k, T;
    cin >> n >> k >> T;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    auto match = [&](int mid) {
        vector<int> b(a.begin(), a.begin() + mid); //注意不可以直接在原数组上排序
        sort(b.begin(), b.end());
        vector<long long> sum(mid + 1), sum2(mid + 1);
        for (int i = 1; i <= mid; i ++){
            sum[i] = sum[i - 1] + b[i - 1]; // 一次项
            sum2[i] = sum2[i - 1] + 1ll * b[i - 1] * b[i - 1]; //二次项
        }

        for (int i = k; i <= mid; i ++) {
            int l = i - k + 1, r = i;
            double avg = (double)(sum[r] - sum[l - 1]) / k;
            double var = (sum2[r] - sum2[l - 1] - 2 * avg * (sum[r] - sum[l - 1]) + k * avg * avg) / k;
            if (var <= T) return true;
        }
        return false;
    };

    int ans  = get_first_match(k, n, match);
    if (ans == n + 1) cout << -1 << "\n";
    else cout << ans << "\n";
}
```

---


**本章完结**