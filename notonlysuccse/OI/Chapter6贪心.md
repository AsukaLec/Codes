[TOC]

# <center>第六章  贪心</center>

## Lead in

### Intro
> Q：你现在有一堆 5， 一堆2， 一堆1，如何凑出27？

针对这个问题，我们可以用这个策略，先拿最大的5，拿5个5凑出25，然后拿1个2凑出27。
但是这种思想对于这个模型是错误的。

!!! : **贪心的定义**
    从**初始状态**到**目标状态**
    求一个**最优方案**
    有多种**状态转移**的方式
    仅根据**当前状态**来制定策略

发现没有，这个定义其实会面对不少问题
- 如何确定各种“状态”？
- 根据**当前状态**做出的选择一定是最优的吗？

> 所以说，在运用贪心的思想时，我们需要**证明**它的正确性。
> 这也是为什么，有时候我们根据贪心策略做出的选择并不一定是最优的。
> 比如对于上面问题中的例子：

假设现在有一个状态 $X(x_i)$, $x + 5 <= n$,我们其实可以证明，在目前这个状态下，下一步选择5是最优的。
**我们可以运用反证法进行证明：**
- 假设在状态 $X(x_i)$ 下，选择2是最优的
- 这个时候就不能选5了，因为这样子就是 $2 + 5$，明显比直接选5差
  - 选择2，此时 $cur = (x + 2)$
    - 这个时候若是再选择2 $cur = (x + 4)$
      - 这种情况下再选择 2 就是 $(x + 6)$ 比直接选5差；
      - 所以只能选 1， 但是这和直接选5没有区别，这个分支挂了。
  - 选择1，此时 $cur = (x + 3)$
    - 因为选了1，**就代表当前选1是最优，2和5都不能选了**，所以只能继续选1
    - 很显然，这样子最后和直接加5没有区别，这条分支也挂了

至此，我们就证明了当$(x + 5 \leq n)$时，选择 5 是最优解。
选择2和1都是同样的证明过程。

**但是**，这个只针对上面这一组数字，我们换一组数字就不成立了。
> eg. [1, 2, 5] 替换为 [1, 3, 4, 5]
> 对于目标是 7 的情况，我们选择5当作第一次选择，最后需要3个数字
> 而选择3， 4 则只需要2个数字

!!! : So， 贪心的思想是？
    1. 制定某个贪心的策略
    2. 证明这个策略的正确性

### 例子1：集合选择问题
> Q: 有n个开区间 $(l_i, r_i)$
> 选择尽量多的开区间
> 使得这些区间两两没有交集

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\贪心Lead In1.png" width="600"/>
  </div>
</div>

**易得，区间的选择顺序是无关的，所以先排序再进行选择。**

**如果以左端点（起始）出现的顺序进行排序**，那么如果有一个特别长的区间在前面，那么后面的区间就很不能被选择到
所以**需要按照右端点（结束）进行排序。**

所以有以下策略：

!!! : 策略
    1. 按照右端点从小到大排序
    2. 每次选择第一个区间，同时删除所有与它有交集的区间
    3. 重复2，直到没有区间为止
        <div style="display:flex; gap:2em; justify-content:center;">
          <div style="text-align:center;">
            <img src="photos\贪心Lead In2.png" width="600"/>
          </div>
        </div>

**证明：**
假设在某一步选择了区间 $x_0$。区间 $x_0$ 的左端点为 $l_0$, 右端点为 $r_0$，是按照贪心策略选择的第一个区间.

那么和区间 $x_0$ 不相交的区间一定符合以下两个特征：
- 左端点 $l_i \leqslant r_0$ （在区间 $x_0$ 右侧）
- 右端点 $r_i \geqslant l_0$ （在区间 $x_0$ 左侧）

因为区间已经排了序，**所以在区间 $x_0$ 左侧没有区间存在**，所以只需要考虑在区间 $x_0$ 右侧的区间。

对于剩下的区间，若满足 $l_i \geqslant r_0$，则将它们加入集合 $S_0$ 中
假设我们下一步选择了区间 $x_1$，同样会有个集合 $S_1$。
根据题意，$S_0$ 一定包含了 $S_1$。
同理，在第二步中，我们无论选择了哪一个区间，其剩余的区间集合一定是包含在 $S_0$ 中的
即 $S_0$ 中包含的可能段数的最大值一定会大于或等于其子空间的可能段数的最大值。
所以此时选择区间 $x_0$ 是最优的。

!!! : 启发
    1. 如果顺序无关，那么可以尝试先排序
    2. 排序的方式有多种，如左右端点、中点、长度、组合
    3. 不断尝试，寻找反例
    4. 对于求最大集合的问题，只需证明在选择a后，剩余选项集合 $S[A]$ 包含了其他作出其他选择后的剩余选项集合 $S[i]$ 即可

> 抽象一下
> 状态： 已选区间的集合
> 初始状态： 空集合
> 目标状态： 无法再选择
> 最优方案： 最大集合
> 状态转移： 选择一个不重叠的区间
> 策略： 按右端点排序后，仅根据已选择的右端点选择第一个不重叠的区间


### 例子2：截止日期问题
> Q: 有n个任务，每个任务有一个截止日期 $d_i$ 和一个收益 $p_i$，每个任务需要1个单位时间完成
> 在截止日期前完成任务可以获得收益，求最大收益
eg.
$$\def\arraystretch{1.5}
\begin{array}{|c|c|c|}\hline
\textsf{截止日期} & \textsf{1} & \textsf{2} & \textsf{3} & \textsf{3} \\ \hline
收益 & 2 & 1 & 9 & 8 \\ \hline
\end{array}
$$

顺序无关，尝试排序：
- 按收益排序，可能会出现收益高但是截止日期早的任务无法完成的情况，如先选9，8， 剩下前面两个就没时间做了
- 按截至日期排序，1， 2， 8： 前期时间浪费在低收益任务上

很显然，以上两种方法都不行

换一种特殊的方法思考：
我们从最后一天开始给前面排任务
最后一天做的必然是还在截止时间内收益最高的任务
往前一天也同理：
发现没有，是不是很像第一个例子中集合最优状态转移方式下，剩余可选集合一定包含在最优选择的剩余集合中

!!! : 启发
    1. 正向不行时，想一下逆向的思路
    2. 如何简单判断一个思路可行与否？看一下任意的剩余的状态选择集合之间与最优的剩余集合之间的关系

> 抽象一下
> 状态： 第 $i$ 天
> 初始状态： 最后一天
> 目标状态： 第一天
> 最优方案： 最大收益
> 状态转移： 选择一个在截止日期内收益最高的任务
> 策略： 仅根据当前日期，选择收益最大的

### 例子3： n 个有序数组排序
> Q: 给定 $n$ 个从小到大排好序的数组，合并成一个从小到大的新数组

看起来，这道题十分简单：
因为给定的n个数组都是有序的，所以在每次选择时，我们只需要将n个数组的第一个元素进行比较并选择出最小的，放到新数组的末尾。

但是，这个方法的复杂度会很高，每一次比较n个数需要 $O(n)$ 的时间复杂度，设每个有序数组长度为 $m$，那么总的时间复杂度为 $O(mn)$。

**我们可以用优先队列来解决这个问题：**
**TIPS：**
> ### 优先队列简介
> 优先队列（Priority Queue）是一种抽象数据结构，它允许插入元素，并总是能够快速访问或删除具有最高（或最低）优先级的元素。与普通队列（FIFO）不同，优先队列不遵循先进先出的原则，而是根据元素的优先级进行操作。
> #### 主要特点
> - **插入（Insert）**：添加一个元素及其优先级。 
> - **删除（Delete）**：移除并返回优先级最高的元素（在最大优先队列中）或最低的元素（在最小优先队列中）。
> - **查找（Peek）**：查看优先级最高的元素，但不移除它。
> #### 实现方式
> - 通常使用\*\*堆（Heap）\*\*数据结构实现：
>   - **最大堆（Max-Heap）**：根节点是最大值。
>   - **最小堆（Min-Heap）**：根节点是最小值。
> #### 时间复杂度
> - 插入：O(log n)
> - 删除：O(log n)
> - 查找：O(1)

!!! : 策略
    1. 初始时先将每一个头元素放进优先队列 **（记录取出的数组和位置）**
    2. 每次从优先队列中取出最小元素，放入目标数组
    3. 对于取出的元素，若它所在的数组还有剩余元素，则将下一个元素放入优先队列

!!! : 启发
    1. 贪心多用优先队列，截止日期也可以用哦
    2. 用最合适的方式记录状态

> 抽象一下
> 状态： 当前优先队列
> 初始状态： 第一列放入优先队列
> 目标状态： 优先队列为空
> 最优方案： 新数组有序
> 状态转移： 选取一个元素
> 策略： 仅根据当前优先队列选择最小元素


### All in ALL
- 制定某个贪心的策略
- 证明这个策略的正确性

---

## 6.1 Leetcode 435 无重叠区间
### 题目描述
给定一个区间的集合 $intervals$ ，其中 $intervals[i] = [starti, endi]$ 。返回 需要移除区间的最小数量，使剩余区间互不重叠 。  
> 注意 只在一点上接触的区间是 不重叠的。例如 $[1, 2]$ 和 $[2, 3]$ 是不重叠的。

### 示例
#### 示例 1:
输入: $intervals = [[1,2],[2,3],[3,4],[1,3]]  $
输出: 1  
解释: 移除 $[1,3]$ 后，剩下的区间没有重叠。

#### 示例 2:
输入: $intervals = [[1,2],[1,2],[1,2]]  $
输出: 2  
解释: 你需要移除两个 $[1,2]$ 来使剩下的区间没有重叠。

#### 示例 3:
输入: $intervals = [[1,2],[2,3]]  $
输出: 0  
解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

#### 提示:
- $1 <= intervals.length <= 10^5$
- $intervals[i].length == 2$
- $-5 * 10^4 <= starti < endi <= 5 * 10^4$

### 题解
Lead in里面证明过的最优的策略，这里主要看看如何编写

首先就是第一步的排序，用到一个匿名函数
```cpp
//按照第二个元素进行排序
sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
    return a[1] < b[1]; //升序
});
```

**Next，如何选择和已选区间不重叠的第一个元素**
朴素来讲，保存每一个区间，每次做选择的时候都遍历一遍，判断是否重叠
但是这样子时间复杂度会很高，达到 $O(n^2)$

先看一下下面这张图：
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\贪心6.1.1.png" width="300"/>
  </div>
</div>

瞪眼法可以看出我们要选的是第一个，第四个，第七个，第八个区间
假设我们现在已经选了第一个区间，这是否代表我们需要把第一个区间存下来，然后和后面的区间逐个进行比较？
完全不需要，记录下当前更新的右端点，**只要下一个区间的左端点大于等于当前右端点，就可以选择它**，并更新右端点。
为什么，因为我们这个序列是已经排过序了的，可以自己验证一下。

完整代码如下，主要看看如何处理选择的区间
实话讲我觉得这里挺直接的。
```cpp
int  main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> intervals;
    int n, m;
    cin >> n >> m;  
    intervals.resize(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> intervals[i][j];
        }
    }

    //按照第二个元素进行排序
    sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
        return a[1] < b[1]; //升序
    });
    
    int ans = 0;
    int right = -5e4; //初始化右端点 无限靠近左侧

    for (auto &interval : intervals) {
        if (interval[0] >= right) {
            right = interval[1];
            ans ++;
        }   
    }
    
    cout << intervals.size() - ans << "\n";
}
```

---

## 6.2 HDU 1789 Doing Homework again
### 题目描述
Ignatius刚从第30届ACM/ICPC回来。现在他有很多作业要做。每位老师都给他一个交作业的截止日期。如果Ignatius在截止日期后交作业，老师会扣除他期末考试的分数。现在我们假设做每份作业总是需要一天的时间。所以Ignatius想让你帮他安排做作业的顺序，以最小化扣分。

### 输入
输入包含多个测试用例。输入的第一行是一个整数 $T$，表示测试用例的数量。接下来是T个测试用例。
每个测试用例以一个正整数 $N(1<=N<=1000)$ 开始，表示作业的数量。然后是2行。第一行包含N个整数，表示各科目的截止日期，第二行包含N个整数，表示扣分。

### 输出
对于每个测试用例，你应该输出最小的总扣分，每行一个测试用例。

### 示例 :
输入:  
```
3  
3  
3 3 3  
10 5 1  
3  
1 3 1  
6 2 3  
7  
1 4 6 4 2 4 3  
3 2 1 7 6 5 4  
```
输出:  
```
0  
3  
5  
```

### 题解
思路前面有，这里借助优先队列来实现贪心策略
why？因为每次我们都需要选择当前截止日期内扣分最高的作业
优先队列的队首元素正好是当前最大的元素
从后往前遍历截止日期，每往前遍历一次就把截止日期为当前日期的作业放入优先队列
选中了就弹出，没选中就留着
分析一下可以发现，这个算法的时间复杂度为 $O(D * N \log N)$ D，其中D为截止日期的最大值
如何优化成 $O(N \log N)$ 呢？
不会，下一个 :)
```cpp
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<int, int>> arr(n);
        int maxD = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i].first;
            maxD = max(maxD, arr[i].first);
        }
        int total = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i].second;
            total += arr[i].second;
        }

        vector<vector<int>> scores(maxD + 1);

        for (auto &[d, s] : arr) scores[d].push_back(s);
        
        priority_queue<int> pq;
        for (int i = maxD; i >= 1; i--) {
            for (auto &s : scores[i]) pq.push(s);

            if (pq.size()) { //防止为空
                total -= pq.top();
                pq.pop();
            }
        }
        cout << total << endl;
    }
}
```

---

## 6.3 LeetCode 23 合并 K 个升序链表

### 题目描述
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

### 示例
#### 示例 1:
输入: $lists = [[1,4,5],[1,3,4],[2,6]]$
输出: $[1,1,2,3,4,4,5,6]$
解释: 链表数组如下：
```
[
  1->4->5,
  1->3->4,
  2->6
]
```
将它们合并到一个有序链表中得到。
$1->1->2->3->4->4->5->6$

#### 示例 2:
输入: lists = $[]$
输出: $[]$

#### 示例 3:
输入: lists = $[[]]$
输出: $[]$

### 题解
使用优先队列（最小堆）来实现贪心策略，每次从所有链表的头节点中选择最小的节点加入结果链表。

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        using node = ListNode;
        node *dummy = new node(); //用一个空节点方便遍历
        node *tail = dummy;
        
        struct Cmp {
            bool operator()(node* a, node* b) {
                return a -> val > b -> val; //小顶堆
            }
        };
        priority_queue<node*, vector<node*>, Cmp> pq;
        //或者
        auto cmp = [](node* a, node* b) {
            return a -> val > b -> val;
        };
        priority_queue<node*, vector<node*>, decltype(cmp)> pqq(cmp);
        //

        for (auto list : lists) {
            if (list) pq.push(list); //防止空链表
        }
        while (pq.size()) {
            auto s = pq.top();
            pq.pop();
            tail -> next = s;
            tail = tail -> next;
            if (s -> next) pq.push(s -> next);
        }
        
        return dummy -> next;
    }
};
```

---

## 6.4 lq 19715 回文数组

### 题目描述
小蓝在无聊时随机生成了一个长度为 $n$ 的整数数组，数组中的第 $i$ 个数为 $a_i$，他觉得随机生成的数组不太美观，想把它变成回文数组，也就是对于任意 $i ∈ [1, n]$ 满足 $a_i = a_{n−i+1}$。小蓝一次操作可以指定相邻的两个数，将它们一起加 1 或减 1；也可以只指定一个数加 1 或减 1，请问他最少需要操作多少次能把这个数组变成回文数组？

### 输入
输入的第一行包含一个正整数 n。

第二行包含 n 个整数 $a_1, a_2, ⋯, a_n$，相邻整数之间使用一个空格分隔。

### 输出
输出一行包含一个整数表示答案。

### 示例:
输入:  
```
4
1 2 3 4
```
输出:  
```
3
```
解释: 第一次操作将 $a_1, a_2$ 加 1，变为 2, 3, 3, 4；后面两次操作将 $a_1$ 加 1，变为 4, 3, 3, 4。

### 题解

这道题的贪心策略还是比较好想的
题目给了两种状态转移的方式
- 选择一个数加1或减1
- 选择两个相邻的数一起加1或减1

那么我们对于当下状态的选取，就直接用相邻的两个数就好了，并且在这两个数之前，所有的数都已经处理完毕

假设数组有 $n$ 个数，我们将 $a[n-i+1]$ 和 $a[n]$ 作差，结果放入新的数组 $sub[n]$ 中

接下来就要想出一个贪心策略，使加减的次数最少
对于任意状态下的两个数 $sub[i]$ 和 $sub[i+1]$
- 若它们异号，则每个数都是只能单独操作，总的操作次数加上每个数的绝对值
- 若它们同号，则可以选择一起操作，选择绝对值较小的数进行一起操作，将较小那个变成符合要求的数后，再把剩下那个数设置为 $sub[i]$ 重写进入一个新的状态进行判断。

代码如下，学习一下如何精简代码
```cpp
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<int> sub(n/2);
    for (int i = 0; i < n/2; i++) {
        sub[i] = a[n - i - 1] - a[i];
    }

    long long  count = 0;
    for(int i = 0;i < n / 2; i++) {
        if (i + 1 < n) { //判断符号是否相同
            if (1ll * sub [i] * sub[i + 1] > 0) { //开 long long 防止溢出
                int min_abs = min(abs(sub[i]), abs(sub[i + 1]));
                count += min_abs;
                if (sub[i] > 0) {
                    sub[i] -= min_abs;
                    sub[i + 1] -= min_abs;
                } else {
                    sub [i] += min_abs;
                    sub[i + 1] += min_abs;
                }
            }
        } 
        count += abs(sub[i]);
    }
    cout << count;
}
```

有兴趣的话把下面这坨调一下 :)
```cpp

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    vector<int> sub(n/2);
    for (int i = 0; i < n/2; i++) {
        sub[i] = a[n - i - 1] - a[i];
    }

    int count = 0;
    for(int i = 0;i < n / 2 ; ) {
        if (sub[i] == 0)    i += 1;

        else if(sub[i] > 0) {
            if (sub[i + 1] < 0){
                count += sub[i];
                i += 1;
            } else if (sub[i + 1] > sub[i]){
                sub[i + 1] -= sub[i];
                count += sub[i];
                i += 1;
            } else if (sub[i + 1] <= sub[i]) {
                count += sub[i];
                i += 2;
            }
        } else if (sub[i] < 0) {
            if (sub[i + 1] > 0) {
                count += -sub[i];
                i += 1; 
            } else if (sub[i + 1] < sub[i]) {
                sub[i + 1] -= sub[i];
                count -= sub[i];
                i += 1;
            } else if (sub[i + 1] >= sub[i]) {
                count -= sub[i];
                i += 2;
            }
        }
    }
    cout << count;
    //for(auto &x : sub) cout << x << " ";
}
```

---

## 6.5 Lq3532 平均
### 题目描述
有一个长度为 n 的数组（n 是 10 的倍数），每个数 $a_i$ 都是区间 [0,9] 中的整数。小明发现数组里每种数出现的次数不太平均，而更改第 i 个数的代价为 $b_i$ ，他想更改若干个数的值使得这 10 种数出现的次数相等（都等于 n/10），请问代价和最少为多少。

### 输入
输入的第一行包含一个正整数 n。

接下来 n 行，第 i 行包含两个整数 a_i, b_i，用一个空格分隔。

### 输出
输出一行包含一个正整数表示答案。

### 示例

输入:  
```
10
1 1
1 2
1 3
2 4
2 5
2 6
3 7
3 8
3 9
4 10
```
输出:  
```
27
```
### 样例说明
只更改第 1,2,4,5,7,8 个数，需要花费代价 1+2+4+5+7+8=27。

### 评测用例规模与约定
对于 20% 的评测用例，n ≤ 1000；

对于所有评测用例，n ≤ 10^5 ，0 < b_i ≤ 2×10^5 。

### 题解

没想到还挺简单，但是码力要提升
这道题的贪心还是非常显而易见的：
我们可以把输入的数据划分到十个槽里面，每个槽最少放 $n/10$ 个数
那么用 $cost$ 最大的元素把槽填满就好了，剩下的拿去修改
```cpp

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(10);
    for(int i = 0; i < n ; i ++) {
        int x, value;
        cin >> x >> value;
        a[x].push_back(value);
    }

    for (auto &vec : a) {
        sort(vec.begin(), vec.end(), greater<int>());
    }

    int times = n / 10;
    long long ans = 0;

    for (int i = 0; i < 10; i ++) {
        if(a[i].size() != 0) for (size_t j = times; j < a[i].size(); j++) ans += a[i][j];
    }

    cout << ans << endl;
}
```

---

## 6.6 Lq19724 食堂
### 题目描述
$S$ 学校里一共有 $a_2$ 个两人寝、$a_3$ 个三人寝、$a_4$ 个四人寝，而食堂里有 $b_4$ 个四人桌和 $b_6$ 个六人桌。学校想要安排学生们在食堂用餐，并且满足每个寝室里的同学都在同一桌就坐，请问这个食堂最多同时满足多少同学用餐？

### 输入格式
采用多组数据输入。

输入共 $q+1$ 行。

第一行为一个正整数 $q$ 表示数据组数。

后面 $q$ 行，每行五个非负整数 $a_2,a_3,a_4,b_4,b_6$ 表示一组数据。

### 输出格式
输出共 $q$ 行，每行一个整数表示对应输入数据的答案。

### 示例
输入:  
```
2
3 0 1 0 1
0 2 2 1 1
```
输出:  
```
6
10
```


### 样例说明
对于第一组数据，只有一个六人桌，因此最多安排三个两人寝的同学就餐，答案为 (2+2+2)=6 。

对于第二组数据，用一个六人桌安排两个三人寝的同学，用一个四人桌安排一个四人寝的同学，答案为 (3+3)+(4)=10 。

### 评测用例规模与约定
对于 20% 的评测用例，保证 $a_2+a_3+a_4≤8 $。

对于 100% 的评测用例，保证 $q≤100, b_4+b_6≤a_2+a_3+a_4≤100 $。

### 题解
首先我们想一下有哪些可能的情况
```
3 + 3 = 6
4 + 2 = 6
2 + 2 + 2 = 6

3 + 2 = 5

4 = 4
2 + 2 = 4

3 = 3

2 = 2
```
写到这贪心的策略还是非常显而易见的，先遍历六人桌，再遍历四人桌，然后对于找到一个满足的情况对号入座就好
**找到一种情况后直接到下一桌**

为啥？
一开始我还想着用数组存每一张桌子剩余的座位数，结果发现完全没必要
为啥？
我们只需要按照这个顺序从上到下遍历，可以保证的是，按照这个顺序选择到一定是最优的。
为啥？
假如某一个状态下我只选了两个人去一张六人桌，
如果我能够在这张桌子上再加三个人，那么它们早就去了，在先前遍历的时候就已经排除了这种情况
什么，你问他们能不能单独去一张四人桌，就像他们单独去一张六人桌一样？
很遗憾，这种情况实际上在前面也已经排除了
所以按照这个顺序向下遍历就好了。

**重头戏来了**
代码怎么写最简便？
(哦对，对于这种输入输出比较多的，可以关流同步和解绑cin.tie提高效率)

**先看一个比较恶臭的版本**
```cpp
int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int a2, a3, a4, b4, b6;
        cin >> a2 >> a3 >> a4 >> b4 >> b6;

        int ans = 0;
        // 优先处理 b6部分
        //用 a3 + a3填 b6
        while (a3 >= 2 && b6) {a3 -= 2; b6--; ans += 6;}

        // 用 a4 + a2 填 b6
        while (a4 && a2 && b6) {a4 -- ; a2 --; b6--; ans += 6;}

        // 用 a2 + a2 + a2 填 b6
        while (a2 >= 3 && b6) {b6 --; a2 -= 3; ans += 6;}

        // 用 a3 + a2 填 b6 
        while (a2 && a3 && b6) {a2 --; a3 --; b6 --; ans += 5;}

        // 用 a4 填 b6 
        while (a4 && b6) {b6 --; a4 --; ans += 4;}
        // 用 a2 + a2 填 b6
        while (a2 >= 2 && b6) {a2 -= 2; b6 --; ans += 4;}

        // 用a3填 b6
        while (a3 && b6) {a3 --; b6 --; ans += 3;}
        // 用 a2 填 b6
        while (a2 && b6) {a2 --; b6 --; ans += 2;}



        // 处理 b4部分 不需要判定 b4 剩余的空间是否够塞多一组人
        // 用 a4 填 b4
        while (a4 && b4) {a4 --; b4 --; ans += 4;}
        // 用 a2 + a2 填 b4
        while (a2 >= 2 && b4) {b4 --; a2 -= 2; ans += 4;}

        // 用 a3 填 b4
        while (a3 && b4) {a3 --; b4 --; ans += 3;}

        // 用 a2 填 b4
        while (a2 && b4) {a2 --; b4 --; ans += 2;}
        
        cout << ans << "\n";
    }
}
```

**还有人类吗？**
**看看老师怎么写的**
```cpp
int main () {
    int q;
    cin >> q;
    while (q--) {
        int a2, a3, a4, b4, b6;
        cin >> a2 >> a3 >> a4 >> b4 >> b6;
        vector<tuple<int, int, int, int>> patterns = {
            {0, 2, 0, 6}, // a3 + a3 
            {1, 0, 1, 6}, // a4 + a2 
            {3, 0, 0, 6}, // a2 + a2 + a2 
            {1, 1, 0, 5}, // a3 + a2 
            {0, 0, 1, 4}, // a4 
            {2, 0, 0, 4}, // a2 + a2 
            {0, 1, 0, 3}, // a3 
            {1, 0, 0, 2}, // a2 
        };

        vector<int> boards(b6, 6);
        boards.insert(boards.end(), b4, 4);

        int total = 0;
        for (auto &board : boards) {
            for (auto &[need_a2, need_a3, need_a4, score] : patterns) {
                if (a2 >= need_a2 && a3 >= need_a3 && a4 >= need_a4 && board >= need_a2 * 2 + need_a3 * 3 + need_a4 * 4) {
                    a2 -= need_a2;
                    a3 -= need_a3;
                    a4 -= need_a4;
                    total += score;
                    break;
                }
            }
        }
        cout << total << "\n";
    }
}
```

清爽，你就学吧 QAQ

---

## 6.7 Lq3518 三国游戏

### 题目描述
小蓝正在玩一款游戏。游戏中魏(\(X\))、蜀(\(Y\))、吴(\(Z\))三个国家各自拥有一定数量的士兵\(X, Y, Z\)（一开始可以认为都为\(0\) )。游戏有\(n\)个可能会发生的事件，每个事件之间相互独立且最多只会发生一次，当第\(i\)个事件发生时会分别让\(X, Y, Z\)增加\(A_i, B_i, C_i\)。

当游戏结束时（所有事件的发生与否已经确定），如果\(X, Y, Z\)的其中一个大于另外两个之和，我们认为其获胜。例如，当\(X > Y + Z\)时，我们认为魏国获胜。小蓝想知道游戏结束时如果有其中一个国家获胜，最多发生了多少个事件？如果不存在任何能让某国获胜的情况，请输出\(-1\)。

### 输入格式
输入的第一行包含一个整数\(n\)。

第二行包含\(n\)个整数表示\(A_i\)，相邻整数之间使用一个空格分隔。

第三行包含\(n\)个整数表示\(B_i\)，相邻整数之间使用一个空格分隔。

第四行包含\(n\)个整数表示\(C_i\)，相邻整数之间使用一个空格分隔。

### 输出格式
输出一行包含一个整数表示答案。

### 示例
输入:  
```
3
1 2 2
2 3 2
1 0 7
```
输出:  
```
2
```


### 评测用例规模与约定
对于\(40\%\)的评测用例，\(n \leq 500\)；

对于\(70\%\)的评测用例，\(n \leq 5000\)；

对于所有评测用例，\(1 \leq n \leq 10^5\)，\(1 \leq A_i, B_i, C_i \leq 10^9\)。

### 题解
我们要找出让 \(X > Y + Z\) 的最大事件数
**等价于找出让 \(X - Y - Z > 0\) 的最大事件数**
（这点很重要，直接解释了为什么第一种方法不对）
初始状态为所有事件都发生，然后逐个移出事件，直到满足条件为止

那么移出事件的顺序是什么？
**贪心策略：每次移除 \(A_i - B_i - C_i\) 最小的事件**
因为求的是最大事件数，所以每次都要尽量减少 \(X - Y - Z\) 的减少量
- 当 \(A_i - B_i - C_i\) 为正时，移除该事件会使 \(X - Y - Z\) 减小，代表若该事件发生，会有助于满足条件
- 当 \(A_i - B_i - C_i\) 为负时，移除该事件会使 \(X - Y - Z\) 增加，代表若该事件发生，不利于满足条件

朴素的来讲，我们要找到最大的事件数，就是要让 \(A_i - B_i - C_i\) 为正的事件全部发生，**同时**，再从剩下的事件中选择**尽可能多的** \(A_i - B_i - C_i\) 为负的事件，使得 \(X - Y - Z > 0\) 成立。

先来看错误的版本
```cpp
int main () {
    int n ;
    cin >> n;
    vector<vector<int>> abc(n, vector<int>(3));

    vector<long long> start(3, 0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> abc[j][i];
            start[i] += abc[j][i];
        }
    }

    int ans = 0;

    for (int i = 0; i < 3; i ++) {
        sort(abc.begin(), abc.end(), [i](auto &a, auto &b) {
            if (a[i] != b[i]) return a[i] < b[i];
            else return a[(i + 1) % 3] + a[(i + 2) % 3] >= b[(i + 1) % 3] + b[(i + 2) % 3];
        });

        vector<long long> curr = start;

        for (int x = 0; x < n; x++) {
            if (curr[i] < curr[(i + 1) % 3] + curr[(i + 2) % 3]) {
                curr[i] -= abc[x][i];
                curr[(i + 1) % 3] -= abc[x][(i + 1) % 3];
                curr[(i + 2) % 3] -= abc[x][(i + 2) % 3];
                continue;
            } else {
                ans = max(ans, n - x);
                break;
            }
        }
    }
    cout << ans << "\n";
}
```

这个版本中是先按照 \(X\) 的值确定顺序，再按照 \(Y + Z\) 的值确定顺序
但是这样子是不对的，因为我们要考虑的是 \(A_i - B_i - C_i\) 的值
有可能 \(A_i\) 相同，但 \(A_i - B_i - C_i\) 的正负性不相同。

so，正确的版本如下
主要区别在与sort的写法
```cpp
int main () {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n ;
    cin >> n;
    vector<vector<int>> abc(n, vector<int>(3));

    vector<long long> start(3, 0);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < n; j++) {
            cin >> abc[j][i];
            start[i] += abc[j][i];
        }
    }

    int ans = -1;

    for (int i = 0; i < 3; i ++) {

        //
        //区别
        sort(abc.begin(), abc.end(), [i](auto &a, auto &b) {
            return (a[i] - a[(i + 1) % 3] - a[(i + 2) % 3]) < (b[i] - b[(i + 1) % 3] - b[(i + 2) % 3]);
        });
        //
        //

        vector<long long> curr = start;

        for (int x = 0; x < n; x++) {
            if (curr[i] <= curr[(i + 1) % 3] + curr[(i + 2) % 3]) {
                curr[i] -= abc[x][i];
                curr[(i + 1) % 3] -= abc[x][(i + 1) % 3];
                curr[(i + 2) % 3] -= abc[x][(i + 2) % 3];
                continue;
            } else {
                ans = max(ans, n - x);
                break;
            }
        }

        if (curr[0] == 0) ans = max(ans, -1);
    }

    cout << ans << "\n";
}
```
!!! : 虽然但是，我觉得这里面模3的想法还是很天才的
    群论这一块

看看老师怎么写的
```cpp

int main () {
    int n;
    cin >> n;
    using xyz = tuple<int, int, int>;
    
    // 输入，注意占位符的使用
    vector<xyz> arr(n);
    for (auto &[x, _, __] : arr) cin >> x;
    for (auto &[_, y, __] : arr) cin >> y;  
    for (auto &[_, __, z] : arr) cin >> z;

    int ans = -1;
    
    //匿名函数 用于计算
    auto calc = [&]() {
        // 转换原来的不等式为一个值排序的问题
        auto getV = [](xyz &t) {
            auto [a, b, c] = t;
            return a - b - c;
        };
        // 排序依据，先排正值，再排负值
        sort (arr.begin(), arr.end(), [&](xyz &a, xyz &b) {
            return getV(a) > getV(b);
        });
        
        // 次数从0开始累加
        long long v = 0;
        int cnt = 0;
        for (auto x: arr) {
            v += getV(x);
            cnt += (v > 0);
        }
        ans = max(ans, cnt);
    };

    calc();
    // 高效的交换
    for (auto &[x, y, z] : arr) swap(x, y);
    calc();
    for (auto &[x, y, z] : arr) swap(x, z);
    calc();
    cout << ans << "\n";
}
```
!!! : 优点
    1. 主要是利用了tuple和匿名函数来简化代码
    2. 占位符用于输入tuple的不同元素。
    3. 匿名函数和swap用于高效地交换tuple中的元素，从而避免重复代码。

---

## 6.8 Lq 3541 最大开支 **还是得多看下**

### 题目描述
小蓝所在学校周边新开业了一家游乐园，小蓝作为班长，打算组织大家去游乐园玩。已知一共有\(N\)个人参加这次活动，游乐园有\(M\)个娱乐项目，每个项目都需要买门票后才可进去游玩。门票的价格并不是固定的，团购的人越多单价越便宜，当团购的人数大于某个阈值时，这些团购的人便可以免费进入项目进行游玩。这\(M\)个娱乐项目是独立的，所以只有选择了同一个项目的人才可以参与这个项目的团购。第\(i\)个项目的门票价格\(H_i(X)\)与团购的人数\(X\)的关系可以看作是一个函数：

\[ H_i(X) = \max(K_i \times X + B_i, 0) \]

其中\(\max\)表示取二者之中的最大值。当\(H_i = 0\)时说明团购人数达到了此项目的免单阈值。

这\(N\)个人可以根据自己的喜好选择\(M\)个娱乐项目中的一种，或者有些人对这些娱乐项目都没有兴趣，也可以选择不去任何一个项目。每个人最多只会选择一个娱乐项目，如果多个人选择了同一个娱乐项目，那么他们都将享受对应的团购价格。小蓝想知道他至少需要准备多少钱，使得无论大家如何选择，他都有能力支付得起所有\(N\)个人购买娱乐项目的门票钱。

### 输入格式
第一行两个整数\(N\)、\(M\)，分别表示参加活动的人数和娱乐项目的个数。接下来\(M\)行，每行两个整数，其中第\(i\)行为\(K_i\)、\(B_i\)，表示第\(i\)个游乐地点的门票函数中的参数。

### 输出格式
一个整数，表示小蓝至少需要准备多少钱，使得大家无论如何选择项目，自己都支付得起。

### 示例
输入:  
```
4 2
-4 10
-2 7
```
输出:  
```
12
```

### 样例说明
样例中有\(4\)个人，\(2\)个娱乐项目，我们用一个二元组\((a, b)\)表示\(a\)个人选择了第一个娱乐项目，\(b\)个人选择了第二个娱乐项目，那么就有\(4 - a - b\)个人没有选择任何项目，方案\((a, b)\)对应的门票花费为\(\max(-4 \times a + 10, 0) \times a + \max(-2 \times b + 7, 0) \times b\)，所有的可能如下所示：

| a | b | 花费 |
|---|---|------|
| 0 | 0 | 0    |
| 0 | 1 | 5    |
| 0 | 2 | 6    |
| 0 | 3 | 3    |
| 0 | 4 | 0    |
| 1 | 0 | 6    |
| 1 | 1 | 11   |
| 1 | 2 | 12   |
| 1 | 3 | 9    |
| 2 | 0 | 4    |
| 2 | 1 | 9    |
| 2 | 2 | 10   |
| 3 | 0 | 0    |
| 3 | 1 | 5    |
| 4 | 0 | 0    |

其中当\(a = 1, b = 2\)时花费最大，为\(12\)。此时\(1\)个人去第一个项目，所以第一个项目的单价为\(10 - 4 = 6\)，在这个项目上的花费为\(6 \times 1 = 6\)；\(2\)个人去第二个项目，所以第二个项目得单价为\(7 - 2 \times 2 = 3\)，在这个项目上的花费为\(2 \times 3 = 6\)；还有\(1\)个人没去任何项目，不用统计；总花费为\(12\)，这是花费最大的一种方案，所以答案为\(12\)。

### 评测用例规模与约定
对于\(30\%\)的评测用例，\(1 \leq N, M \leq 10\)。

对于\(50\%\)的评测用例，\(1 \leq N, M \leq 1000\)。

对于\(100\%\)的评测用例，\(1 \leq N, M, B_i \leq 10^5\)，\(-10^5 \leq K_i < 0\)。

### 题解
先来一坨不可名状之物

!!! : WHY？？？
    首先可以发现每个项目的单价和人数的关系是一个二次函数，且开口向下
    那么对于每个项目，我们可以计算出一个最优人数，使得该项目的总花费最大

    在这个视角下的贪心策略就是：
    1. 计算出每个项目的最优人数和对应的最大花费
    2. 将这些项目按照最大花费从大到小排序
    3. 依次选择项目，直到人数用完或者没有更多项目可选
    
    但是有个问题，比如出现以下情况（二元组第一个空代表单价最大值时对应的人数，第二个空代表单价最大值）：
    <100, 100>, <1, 99>, <1, 99>, ..., <1, 99>
    这种情况下，假设我们初始只有100个人，那么按照这种策略最后的总划分只有100。但实际上，我们可以做到 9900 

    针对此，我们推出了一个改进版，排序的条件是单价的最大值
    还是不对，比如 <1, 101> <100, 10000>
    还是初始一百个人 这你不炸了


```cpp
int main() {
    int n; cin >> n;
    int m; cin >> m;
    
    // vector<vector<long long>> items(m, vector<long long>(4));
    // for (auto &item : items) {
    //     cin >> item[0] >> item[1];
    // }

    // for (auto &item : items) {
    //     int cur = item[1] / (2 * (- item[0]));
    //     if ((item[0] * cur * cur + item[1] * cur) > (item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1))) {
    //         item[2] = cur;
    //         item[3] = item[0] * cur * cur + item[1] * cur;
    //     } else {
    //         item[2] = cur + 1;
    //         item[3] = item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1);
    //     }
    // }

    vector<vector<long long>> items(m, vector<long long>(2));  // 只初始化 2 个元素
    for (auto &item : items) {
        cin >> item[0] >> item[1];
    }

    for (auto &item : items) {
        long long cur = item[1] / (2 * (-item[0]));
        long long cost1 = item[0] * cur * cur + item[1] * cur;
        long long cost2 = item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1);
        if (cost1 > cost2) {
            item.push_back(cur);
            item.push_back(cost1);
            item.push_back(item[0] * cur + item[1]);
        } else {
            item.push_back(cur + 1);
            item.push_back(cost2);
            item.push_back(item[0] * (cur + 1) + item[1]);
        }   
    }

    sort(items.begin(), items.end(), [](auto &a, auto &b) {
        // if (a[3] != b[3]) return a[3] > b[3];
        // else return a[2] < b[2];
        if (a[4] != b[4]) return a[4] > b[4];
        else return a[2] < b[2];
    });

    // for (auto &item : items) {
    //     for (auto &x : item) cout << x << " ";
    //     cout << "\n";
    // }
    long long ans = 0;

    for (int i = 0; i < m; i ++) {
        if (n >= items[i][2]) {
            ans += items[i][3];
            n -= items[i][2];
        } else if (n != 0){
            ans += items[i][0] * n * n + items[i][1] * n;
        }
    }
    cout << ans << endl;
}
```
我们来看看正确的思路：

!!! : 正确思路
    我们现在不去记算每一个项目的可能的最大值
    假设在最开始输入每一个项目的时候，我们都只放一个人进去这个项目
    那么我们可以得到其收益的增量 \(k_i * 1 + b_i - 0 \) 记为 \(\Delta price_{i, 1}\)
    然后把这这一堆放到一个优先队列，并弹出最大值作为我们的第一个选择
    
    **然后**，计算选定的这个项目的下一个**增量** \(\Delta price_{i, 2} = k_i * 2 + b_i - (k_i * 1 + b_i) \)

    把这个增量重新放回优先队列,再进行下一轮
    如果有一个增量小于等于0了，说明这个项目已经不值得继续选择下去了，直接丢弃即可
    （注意一下代码中如何实现“丢弃”，因为我们用的是优先队列，所以当遍历到这个增量时，直接break就好了）
    **思路比较像 Lead In 中的 例题 3 的贪心策略**

!!! : WHY IT WORKS？
    直观来讲，我们干了一件什么事？
    对于给定的 \(N\) 个人数，我们每次只放一个人，且只放到对总花费增益最大的项目中

    因为总价关于人数是一个二次函数，且开口向下
    所以每一个项目的增加一个人的增益一定是一开始大后面慢慢变小的
    **所以直接取最大总增益的情况时，人均收益一定是被拉低了的**

    这样子就有点 “当前状态” ——> “状态转移” 的感觉了
    而我们一开始的做法带有很强的**全局视野**




接下来是AC代码
```cpp
int main() {
    int n, m;
    cin >> n >> m;
    priority_queue<tuple<long long, int, int, int>> pq; //收益，行，列，当前选取的数量
    for (int i = 0; i < m; i ++) {
        int k, b;
        cin >> k >> b;
        pq.emplace(b + k, k, b, 1);
    }
    // 优先队列默认按降序排列

    long long ans = 0;

    while (n --) {
        auto [delta_price, k, b, x] = pq.top();
        pq.pop();
        if (delta_price <= 0) break;

        ans += delta_price;
        long long price = 1ll * (b + k * x) * x;
        long long next_price = 1ll * (b + k * (x + 1)) * (x + 1);
        pq.emplace(next_price - price, k, b, x + 1);
    }

    cout << ans << endl;
}
```
T_T

---

## 6.9 Lq1596 巧克力

### 题目描述
小蓝很喜欢吃巧克力，他每天都要吃一块巧克力。

一天小蓝到超市想买一些巧克力。超市的货架上有很多种巧克力，每种巧克力有自己的价格、数量和剩余的保质期天数，小蓝只吃没过保质期的巧克力，请问小蓝最少花多少钱能买到让自己吃\(x\)天的巧克力。

### 输入描述
输入的第一行包含两个整数\(x, n\)，分别表示需要吃巧克力的天数和巧克力的种类数。

接下来\(n\)行描述货架上的巧克力，其中第\(i\)行包含三个整数\(a_i, b_i, c_i\)，表示第\(i\)种巧克力的单价为\(a_i\)，保质期还剩\(b_i\)天（从现在开始的\(b_i\)天可以吃），数量为\(c_i\)。

### 输出描述
输出一个整数表示小蓝的最小花费。如果不存在让小蓝吃\(x\)天的购买方案，输出\(-1\)。

### 示例

输入:  
```
10 3
1 6 5
2 7 3
3 10 10
```
输出:  
```
18
```

### 样例说明
一种最佳的方案是第\(1\)种买\(5\)块，第\(2\)种买\(2\)块，第\(3\)种买\(3\)块。前\(5\)天吃第\(1\)种，第\(6\)、\(7\)天吃第\(2\)种，第\(8\)至\(10\)天吃第\(3\)种。

### 评测用例规模与约定
对于\(30\%\)的评测用例，\(n, x \leq 1000\)；

对于所有评测用例，\(1 \leq n, x \leq 100000\)，\(1 \leq a_i, b_i, c_i \leq 10^9\)。

### 题解
这道题，跟之前讲的那个哪一天做哪个作业那个模型是一样的
不同在哪呢，在于巧克力的数量是会变的
所以说在存储巧克力价格的基础上，还要存储不同巧克力剩余的数量

如果按照数量存的话，一直插入删除我感觉堆实现的优先队列时间复杂度会爆炸
如下是爆炸了的第一版
```cpp
int main() {
    int days, n;
    cin >> days >> n;

    // 单价 保质期 数量
    vector<vector<int>> chocolates(n, vector<int>(3));
    for (auto &choc : chocolates) {
        cin >> choc[0] >> choc[1] >> choc[2];
    }

    sort(chocolates.begin(), chocolates.end(), [](auto &a, auto &b) {
        return a[1] > b[1];
    });

    long long cost = 0;
    priority_queue<int, vector<int>, greater<int>> pq; //只用存单价
    int idx = 0;
    while (days) {
        while (idx < n && chocolates[idx][1] >= days) {
            int count = min(days, chocolates[idx][2]);
            for (int i = 0; i < count; i++) {
                pq.push(chocolates[idx][0]);
            }
            idx ++;
        }

        if (pq.size()) {
            cost += pq.top();
            pq.pop();
            days --;
        } else {
            cout << -1 << "\n";
            return 0;
        }
    }
    cout << cost << "\n";
}
```

重构了一下，用`pair`存储单价和数量
```cpp
int main() {
    int days, n;
    cin >> days >> n;

    // 单价 保质期 数量
    vector<vector<int>> chocolates(n, vector<int>(3));
    for (auto &choc : chocolates) {
        cin >> choc[0] >> choc[1] >> choc[2];
    }

    // 按保质期降序排序
    sort(chocolates.begin(), chocolates.end(), [](auto &a, auto &b) {
        return a[1] > b[1];
    });

    long long cost = 0;

    using pii = pair<int, int>; //划重点，你就学吧
    priority_queue<pii, vector<pii>, greater<pii>> pq; //只用存单价 和 数量

    int idx = 0;
    while (days) {
        while (idx < n && chocolates[idx][1] >= days) {
            pq.emplace(chocolates[idx][0], chocolates[idx][2]);
            idx ++;
        }

        if (pq.size()) {
            auto [price, count] = pq.top();
            pq.pop();
            cost += price;
            if (count > 1) {
                pq.emplace(price, count - 1);
            }
            days --;
        } else {
            cout << -1 << "\n";
            return 0;
        }
    }
    cout << cost << "\n";
}
```

---

## 6.10 Lq 2213 打折
### 题目描述
小蓝打算采购\(n\)种物品, 每种物品各需要 1 个。

小蓝所住的位置附近一共有\(m\)个店铺, 每个店铺都出售着各种各样的物品。

第\(i\)家店铺会在第\(s_i\)天至第\(t_i\)天打折, 折扣率为\(p_i\), 对于原件为\(b\)的物品, 折后价格为\(\lfloor \frac{b \cdot p_j}{100} \rfloor\)。其它时间需按原价购买。

小蓝很忙, 他只能选择一天的时间去采购这些物品。请问, 他最少需要花多少钱才能买到需要的所有物品。

题目保证小蓝一定能买到需要的所有物品。

### 输入格式
输入的第一行包含两个整数\(n, m\), 用一个空格分隔, 分别表示物品的个数和店铺的个数。

接下来依次包含每个店铺的描述。每个店铺由若干行组成, 其中第一行包含四个整数\(s_i, t_i, p_i, c_i\), 相邻两个整数之间用一个空格分隔, 分别表示商店优惠的起始和结束时间、折扣率以及商店内的商品总数。之后接\(c_i\)行, 每行包含两个整数\(a_j, b_j\), 用一个空格分隔, 分别表示该商店的第\(j\)个商品的类型和价格。商品的类型由 1 至\(n\)编号。

### 输出格式
输出一行包含一个整数表示小蓝需要花费的最少的钱数。

### 示例
输入:  
```
2 2
1 2 89 1
1 97
3 4 77 1
2 15
```
输出:  
```
101
```


### 评测用例规模与约定
对于\(40\%\)的评测用例, \(n, m \leq 500\), \(s_i \leq t_i \leq 100\), \(\sum c_i \leq 2000\)；

对于\(70\%\)的评测用例, \(n, m \leq 5000\), \(\sum c_i \leq 20000\);

对于所有评测用例, \(1 \leq n, m \leq 100000\), \(1 \leq c_i \leq n\), \(\sum c_i \leq 400000\), \(1 \leq s_i \leq t_i \leq 10^9\), \(1 < p_i < 100\), \(1 \leq a_j \leq n\), \(1 \leq b_j \leq 10^9\)。

### 运行限制
- **最大运行时间： 10秒**
- 最大运行内存： 512MB

### 题解
很遗憾，经过尝试后，这道题我没有找到很好的贪心策略
举一个很简单的例子
我们知道我们想找到一个日期，在这个日期，打折的商店尽可能多
所以我们可以先把所有商店的打折日期用差分数组存下来，最后再进行一次前缀和并找到极大值
然而，有可能出现这样的情况
<1, 4> <1, 2> < 3, 4>
这样每一天都有两个商店在打折，但是我们要分成两种情况去讨论，处理这种重复的成本是很高的。我们的本意是根据打折的日期来进行剪枝寻找最有可能成为最优的那一天

所以最后暴力枚举了
但是还是有些细节要注意的，比如说用 multiset来存储最低价格
用 $\Delta$ 来存储增量而非每次都重新计算

**这道题其实引出了一个问题：何为贪心**
可见的是，这道题更多是寻找并优化一种枚举的策略
至于说给定任意一种状态去优化自己的决策而做到贪心，在这道题中没有很好的体现

代码如下，麻
```cpp
int main() {
    int n, m; cin >> n >> m;

    vector<tuple<int, int, int, int>> actions; // 时间，折扣信息，商品原价，商品类型
    vector<multiset<int>> prices(n + 1); // 每种商品的当前价格集合
    // 数据预处理
    for (int i = 0; i < m; i ++) {
        int start, end, discount, cnt;
        cin >> start >> end >> discount >> cnt;
        while (cnt--) {
            int type, baseprice;
            cin >> type >> baseprice;
            prices[type].insert(baseprice);
            actions.emplace_back(start, discount, type, baseprice); // 折扣开始，价格降低
            actions.emplace_back(end + 1, -discount, type, baseprice); // 折扣结束，价格恢复
        }
    }

    // 遍历统计最小值
    sort(actions.begin(), actions.end()); // 按时间排序（默认按第一个元素升序）

    long long total = 0;
    for (int i = 1; i <= n; i ++) {
        total += *prices[i].begin(); // 初始总价为每种商品的最低价之和
    }
    long long ans = total;

    for (auto [time, discount, type, baseprice] : actions) {
        int currentPrice = *prices[type].begin();//当前最低价
        if (discount > 0) {
            prices[type].insert( 1ll * baseprice * discount / 100); // 插入折扣价
        } else {
            prices[type].erase(prices[type].find(1ll * baseprice * (-discount) / 100)); // 移除折扣价
        } //multiset 的 erase 只能删除所有相同值，需用 find 定位到具体元素再删除

        int price = *prices[type].begin();
        int delta = price - currentPrice;
        total += delta;
        ans = min(ans, total);
    }
    cout << ans << "\n";
}
```

本章完结