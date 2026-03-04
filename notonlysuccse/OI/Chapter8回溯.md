[TOC]
<style>
.blue-quote { 
    border-left: 4px solid #2b8bf2; 
    padding-left: 12px; 
    color: #333; 
    background-color: #f3f8ff; /* 添加浅蓝色背景 */
}
.red-quote { 
    border-left: 4px solid #f44336; 
    padding-left: 12px; 
    color: #333; 
    background-color: #ffe5e5; /* 添加浅红色背景 */
}
.green-quote { 
    border-left: 4px solid #4caf50; 
    padding-left: 12px; 
    color: #333; 
    background-color: #e8f5e9; /* 添加浅绿色背景 */
}
.lightgrey-quote { 
    border-left: 4px solid #9e9e9e; 
    padding-left: 12px; 
    color: #333; 
    background-color: #f5f5f5; /* 添加浅灰色背景 */
}
.yellow-quote { 
    border-left: 4px solid #ffeb3b; 
    padding-left: 12px; 
    color: #333; 
    background-color: #fffde7; /* 添加浅黄色背景 */
}
.purple-quote { 
    border-left: 4px solid #9c27b0; 
    padding-left: 12px; 
    color: #333; 
    background-color: #f3e5f5; /* 添加浅紫色背景 */
}
.orange-quote { 
    border-left: 4px solid #ff9800; 
    padding-left: 12px; 
    color: #333; 
    background-color: #fff3e0; /* 添加浅橙色背景 */
}
.cyan-quote { 
    border-left: 4px solid #00bcd4; 
    padding-left: 12px; 
    color: #333; 
    background-color: #e0f7fa; /* 添加浅青色背景 */
}
.pink-quote { 
    border-left: 4px solid #e91e63; 
    padding-left: 12px; 
    color: #333; 
    background-color: #fce4ec; /* 添加浅粉色背景 */
}
.grey-quote { 
    border-left: 4px solid #607d8b; 
    padding-left: 12px; 
    color: #333; 
    background-color: #eceff1; /* 添加浅灰蓝色背景 */
}
</style>

# <center>第八章 回溯</center>

## Lead In
### Intro
!!! : 回溯本质上是一种枚举

**定义：**
<blockquote class="grey-quote">

从 **初始状态** 经过 **不确定的步数，** 到 **有条件** 的 **目标状态**
每个状态有一种或多种方式到下一个状态（**状态转移**）
在过程中进行一定的判定，对一定不可能的目标状态**提前结束枚举**（剪枝）
</blockquote>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯 1.png " width="600"/>
  </div>
</div>

---

### 引言
假设你正在玩一款RPG游戏，控制一个角色在迷宫中行动，有一把钥匙，有血量、攻击力等等属性(**初始状态:坐标、是否有钥匙、以及属性**)

目标是到达有圣杯的位置并用钥匙打开(**目标状态:坐标位于圣杯位置且有钥匙**)

迷宫会有多条岔路，游戏规定每次必须选择一条路，不能走回头路

每个节点会有宝箱或者怪物，宝箱可能会让你的属性提升，怪物则会发生战斗，如果失败，不会死亡，但会抢走你的钥匙(**状态转移:改变坐标和对应的属性、钥匙的有无**)

#### 最朴素的玩法：枚举
把从起点到终点的所有方案都规划出来，对每条路进行校验，看看能不能成功到达终点

#### 高级玩法（Save/Load大法，回档，回溯，traceback）
每次选择岔路前，先存档，再选择岔路，再次遇到岔路，再次存档
当发现走到死胡同后，读取上次的存档，然后选择另一条路

#### 更高明一点的玩法(剪枝)
如果发现战斗失败,钥匙丢失,那这条路就没必要继续走下去了
因为就算有最后找到有宝箱,也无法用钥匙打开

---

### 例子1 Leetcode 77 组合
<blockquote class="green-quote">
给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。

你可以按 **任何顺序** 返回答案。

**示例 1：**
    输入：n = 4, k = 2输出：[ [2,4], [3,4], [2,3], [1,2], [1,3], [1,4],]

**示例 2：**
    输入：n = 1, k = 1输出：[[1]]

**提示：**
- `1 <= n <= 20`
- `1 <= k <= n`
</blockquote>

初始状态： [ ] 空集合
目标状态：长度为k的**组合**， 包含的数字在1到n之间且不重复
状态转移：每次选择一个数字加入组合中，直到组合长度达到k
要求：列举出所有方案，不能重复
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯 2.png " width="600"/>
  </div>
</div>

#### 朴素做法
如果 k = 1, 那么只需要一层循环，枚举1到n的数字即可
```cpp
vector<vector<int>> ans;
vector<int> combination;
for (int i = 1; i <= n; ++i) {
    combination.push_back(i);
    ans.push_back(combination);
    combination.pop_back();
}
```
如果 k = 2, 那么需要两层循环，第一层枚举第一个数字，第二层枚举第二个数字
```cpp
vector<vector<int>> ans;
vector<int> comb;
for (int i = 1; i <= n; ++i) {
    comb.push_back(i);
    for (int j = i + 1; j <= n; ++j) { //注意是 i + 1
        comb.push_back(j);
        ans.push_back(comb);
        comb.pop_back();
    }
    comb.pop_back();
}
```
但 k 不是固定的，而是一个变量，不能写死循环的层数
**即 经过不确定的步数， 到有条件的目标状态**

#### 递归做法
```cpp
//c++ 11
vector<vector<int>> ans;
vector<int> comb; //状态
void traceback(){
    if (comb.size() == k){ //达到目标状态
        ans.push_back(comb);
        return;
    }
    //下界
    int lower = comb.size() == 0 ? 1 : comb.back() + 1; 
    for (int i = lower; i <= n; i ++) { //状态转移
        comb.push_back(i);
        traceback();
        comb.pop_back();
    }
}
int main(){
    traceback();
}
```

```cpp
//c++ 17
vector<vector<int>> ans;
vector<int> comb; 
auto traceback = [&](auto &self) {
    if (comb.size() == k){
        ans.push_back(comb);
        return;
    }
    int lower = comb.size() == 0 ? 1 : comb.back() + 1; 
    for (int i = lower; i <= n; i ++) {
        comb.push_back(i);
        self(self); //递归调用
        comb.pop_back();
    }
};
int main(){
    traceback(traceback);
}
```

#### 剪枝
其实我们在枚举状态时,从 $back()+1$ 开始枚举,而不是从1开始,就已经在剪枝了

当然,还可以有更好的剪枝, 枚举的上界也可以优化, 剩余还需要填充的个数是 $k-comb.size()$,如果我们当前选择 $x$ ,那么最多可以选择 $[x,x+l,x+2,…n]$ 也就是 $n-x+1$ 个,如果比 $k-comb.size()$ 小,那么说明后续一定不可能组合成 $k$ 个数字

所以上界 $ n-x+1 \geq k-comb.size()$

因此 $x \leq n+1-k+comb.size()$

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯 3.png " width="600"/>
  </div>
</div>

说明：比如在上图中，枚举到 $[1, 4]$ 时，还要再填一个比 4 大的数，可实际已经没有这样的数了，所以这一段可以直接剪掉

```cpp
vector<vector<int>> ans;
vector<int> comb;
auto traceback = [&](auto &self) {
    if (comb.size() == k){
        ans.push_back(comb);
        return;
    }
    int lower = comb.size() == 0 ? 1 : comb.back() + 1; 
    int upper = n + 1 - (k - comb.size()); //枚举上界 剪枝
    for (int i = lower; i <= upper; i ++) {
        comb.push_back(i);
        self(self);
        comb.pop_back();
    }
};
traceback(traceback);
```

***

### 例子2 Leetcode 78 子集
<blockquote class="green-quote">

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。
解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
输入：
`nums = [1,2,3]`
输出：
`[[], [1], [2], [1,2], [3], [1,3], [2,3], [1,2,3]]`
</blockquote>

#### 做法 1 
相当于在上一道题中，取 k 从0到n的所有情况
- 等价于没有限制，每一个状态都是合法状态，都加入到答案数组中
- 并且是从一个数组中取数，而非 `1 - n`， 我们假设 `index[i]` 是子集中第 i 个元素对应原数组的下标，需要满足 `index[i] < index[i+1]` 来保证子集中的元素不重复
- 因此可以传递一个下界，每次递归枚举的时候，直接从上一个选择的元素下标开始枚举

```cpp
vector<vector<int>> ans;
vector<int> subset;
auto traceback = [&](auto &self, int lower) -> void {
    ans.push_back(subset); //每个状态都是合法状态
    for (int i = lower; i < nums.size(); i ++) {
        subset.push_back(nums[i]);
        self(self, i + 1); //下界是上一个选择的元素下标 + 1
        subset.pop_back();
    }
};
taceback(traceback, 0);
```

<blockquote class="red-quote">

**辅助状态**
其实 $subset$ 已经可以表示完整的状态
如果不传递 $lower$ , 我们可以循环找到 $subset$ 最后一个元素在原数组中的下标,然后从这个下标开始找, 达到一样的效果
但每次都寻找一遍,显然时间会更慢
**因此我们可以添加辅助状态,来加速状态的转移**
辅助状态是回溯中一个非常重要的概念,好的辅助状态可以极大的提高运行速度

如何确定？ **如何最快地剪枝**
</blockquote>

#### 做法 2
子集也可以看做是否选择某个元素，因此对于每个位置，有两种状态转移方式，选择和不选择
**该做法的状态为**：对于当前子集，枚举到第几个元素
**目标状态**：枚举完所有元素
**状态转移**：选择、不选择
```cpp
vector<vector<int>> ans;
vector<int> subset;
auto traceback = [&](auto &self, int pos) {
    if (pos == nums.size()) {
        ans.push_back(subset);
        return;
    }
    //不选择当前元素
    self(self, pos + 1);
    subset.push_back(nums[pos]);
    //选择当前元素
    self(self, pos + 1);
    subset.pop_back();
};
taceback(traceback, 0);
```
<blockquote class="red-quote">

**Trick: 状态是否作为参数传递**
上两个程序可以看到,$subset、pos、lower$都是状态,但是$subset$作为全局上下文,$pos$和$lower$作为参数传递

其实,他们都作为全局上下文,或者都作为参数都是可以的

但一般而言,**基本数据类型作为参数,非基本数据类型作为全局上下文**会更方便编写
</blockquote>

```cpp
//都作为上下文
//都需要额外维护基础数据类型的回滚
vector<vector<int>> ans;
vector<int> subset;
int pos = 0;
auto traceback = [&] (auto &self) {
    if (pos == nums.size()) {
        ans.push_back(subset);
        return;
    }
    pos ++;
    slef(self);
    pos --;

    subset.push_back(nums[pos]);
    pos ++;
    self(self);
    subset.pop_back();
    pos --;
};
taceback(traceback);
```
```cpp
//都作为参数
//虽然不用回滚，但是每次大参数传递需要额外的开销，内存和时间都会增长
vector<vector<int>> ans;
auto traceback = [&](auto &self, vector<int> subset, int pos) {
    if (pos == nums.size()) {
        ans.push_back(subset);
        return;
    }
    self(self, subset, pos + 1);

    vector<int> newSubset = subset;
    newSubset.push_back(nums[pos]);

    self(self, newSubset, pos + 1);
};
vector<int> subset;
taceback(traceback, subset, 0);
```

---

### 模板
```js
traceback(state) :
    if (check(state)) : //判断到达目标状态
        savesolution(state)
        return //可选

    for each candidates:
        if (illegalty(state, candidates[i])) ://非法状态
            continue //剪枝
        update(state, candidate) //更新状态
        traceback(state) //递归
        rollback(state, candidate) //回滚状态
```

---

### 例子3 Leetcode 37 数独
<blockquote class="green-quote">

编写一个程序，通过填充空格来解决数独问题。
一个数独的解法需遵循如下规则：
- 数字 1-9 在每一行只能出现一次。
- 数字 1-9 在每一列只能出现一次。
- 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
- 空白格用 '.' 表示。
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯 4.png " width="600"/>
  </div>
</div>
</blockquote>

#### 分析
- 初始状态：初始棋盘
- 目标状态：填充完成的棋盘
- 状态转移：挨个枚举每个位置
  -  如果已经填了数字，直接转移到下一个位置
  -  如果没有数字，那么填 1 - 9 的数字

如果按照朴素的枚举方法，把所有答案枚举出来，再进行目标状态的校验，数据量非常大($9^{81}$)，因此需要在枚举的过程中进行剪枝，提前结束不合法的状态。
也就是说，**将一部分目标状态的条件，提前进行检测**，如果不满足条件，就不继续枚举下去

并且为了方便判断条件成立，可以将 9 行，9 列，9  宫有哪些数字提前列举出来，作为**辅助状态**，方便判断

```cpp
//给定初始棋盘
auto board = vector(9, vector(9));

//辅助状态
auto rows = vector(9, vector(9 ,0));
auto cols = vector(9, vector(9 ,0));
auto cells = vector(3, vector(3, vector(9, 0)));

for (int i = 0; i < 9; i ++) {
    for (int j = 0; j < 9; j ++) {
        if (board[i][j] == '.') continue;
        int digit = board[i][j] - '1';
        rows[i][digit] = 1;
        cols[j][digit] = 1;
        cells[i / 3][j / 3][digit] = 1;
    }
}

auto traceback = [&](auto &self, int pos) {
    if (pos == 81) return true;
    int x = pos / 9, y = pos % 9;
    if (board[x][y] != '.') return self(self, pos + 1);

    // 枚举每个转移
    for (int d = 0; d < 9; d ++) {
        if (rows[x][d] || cols[y][d] || cells[x / 3][y / 3][d]) continue; // 非法状态 剪枝

        // 状态更新
        board[x][y] = d + '1';
        rows[x][d] = 1;
        cols[y][d] = 1;
        cells[x / 3][y / 3][d] = 1;

        // 状态转移
        if (self(self, pos + 1)) return true; 
        // 如果找到一个合法的解了，就直接返回，不需要继续枚举了
        //直接从 第 81 层 回溯到 第 0 层

        // 状态回滚
        board[x][y] = '.';
        rows[x][d] = 0;
        cols[y][d] = 0;
        cells[x / 3][y / 3][d] = 0;
    }
    return false;
};
traceback(traceback, 0);
```
---

### 模板 （寻找一个答案）
多个return true, 直接从目标状态回溯到初始状态

```js
traceback(state) :
    if (check(state)) : //判断到达目标状态
        savesolution(state)
        return true

    for each candidates: //对于每个可能的转移
        if (illegalty(state, candidates[i])) ://非法状态
            continue //剪枝
        update(state, candidate) //更新状态
        if (traceback(state)) return true; //如果找到一个合法的解了，就直接返回，不需要继续枚举了
        rollback(state, candidate) //回滚状态
    return false; //没有找到合法的解
```
---

### 复杂度
回溯的复杂度难以精确计算，程序运行速度取决于具体的数据。
比如完全空白的数独和第一个空白位置要填9的数独，在运行速度上相差很大

所以只能通过答案的理论个数来推导，或者计算无法剪枝情况下的理论上界
- 组合数： $C(n, k)$, $O(k * C(n, k))$
- 子集数： $2^n$, $O(n * 2^n)$
- 数独无法剪枝的情况下： 有 $9^m$ 个方案， $m$ 是空格的数量，时间复杂度是 $O(9^m)$

这些复杂度都是指数级的，但是由于<mark>剪枝</mark>的存在，使其远远达不到上界

---

### 是否可以采用回溯？
- 是否有其他解法？
- 是否求唯一解？ **(题目保证答案存在且唯一)**
  - 如果是判断解是否存在，通常很容易超时
- n 的范围一般小于等于 100
- 条件的复杂度，越复杂越容易剪枝，n的范围也可以适当增大
- 出题人÷不÷

---

### 回溯的写法
复杂的回溯代码通常100行左右
可拆解成以下函数
- `traceback` 回溯主函数
- `can` 是否可以到达下一个函数或者 `illegality` 是否非法状态(剪枝)
- `update` 更新状态
- `rollback` 回滚状态
- `check` 检测最终状态是否合法

### 回溯的技巧和延伸
1. 剪枝
2. 辅助状态
3. 枚举的顺序，可以先枚举状态转移的候选项最少的
4. Dancelinks 舞蹈链，非常高级的回溯技巧

---

### 和贪心的对比
- 相同点：
  - 从初始状态，通过状态转移，到目标状态
- **不同点：**
  - 贪心：每次状态转移时，可以选择最优的方案，不需要枚举其他方案
  - 回溯：无法知道状态是否最优，所以只能参与逐个枚举
 
---
---

## 8.1 Leetcode46 全排列

!!! : 主要是 `next_permutation` 函数的使用； 以及辅助状态的确定
### 题目描述
给定一个不含重复数字的数组 `nums` ，返回其所有可能的全排列。你可以按 **任意顺序** 返回答案。
**示例 1：**
```
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
``` 
**示例 2：**
```
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```
**示例 3：**
```
输入：nums = [1]
输出：[[1]]
```
**提示：**
- `1 <= nums.length <= 6`
- `-10 <= nums[i] <= 10`
- `nums` 中的所有整数 互不相同

### 题解
组合的时间复杂度是 $O(k * C(n, k))$, 因为每个组合需要 $O(k)$ 的时间来复制到答案数组中
而全排列的时间复杂度是 $O(n * n!)$, 因为每个排列需要 $O(n)$ 的时间来复制到答案数组中，而全排列的数量是 $n!$ 个

需要一个**辅助状态**来记录当前的排列中哪些数字已经被使用了，避免重复使用同一个数字
```cpp
int n = nums.size();
vector<vector<int>> ans;
vector<int> perm;
vector<int> used(n);
auto traceback = [&](auto &self) {
    if (perm.size() == n) {
        ans.push_back(perm);
        return;
    }

    for (int i = 0; i < n; i ++) {
        if (used[i]) continue; //剪枝
        used[i] = 1; //状态更新
        perm.push_back(nums[i]);
        self(self); //状态转移
        perm.pop_back(); //状态回滚
        used[i] = 0; //状态回滚
    }
};
traceback(traceback);
```

<blockquote class="orange-quote">

c++ 提供了一个函数 `next_permutation` 可以直接得到到给定序列的**下一个**全排列
因此我们也可以通过不断调用 `next_permutation` 来得到所有的全排列，直到回到初始状态为止

用这个的目的就在于在需要生成全排列的时候，不需要自己写回溯代码了，直接调用这个函数就可以了，代码量会大大减少
**同时，这个函数是按照字典序来生成全排列的，因此如果我们需要按照字典序来输出全排列的话，这个函数也是非常方便的**，只需要先对输入数组进行**排序**，然后不断调用 `next_permutation` 就可以了
</blockquote>

```cpp
do {
    ans.push_back(nums);
} while (next_permutation(nums.begin(), nums.end()));
return ans;
```
---

## 8.2 Leetcode 47 全排列 II

!!! : 主要是回溯中如何进行去重

### 题目描述
给定一个**可包含重复数字**的序列 `nums` ，按任意顺序返回所有不重复的全排列。
**示例 1：**
```输入：nums = [1,1,2]
输出：[[1,1,2],[1,2,1],[2,1,1]]
``` 
**示例 2：**
```输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
``` 
**提示：**
- `1 <= nums.length <= 8`
- `-10 <= nums[i] <= 10`
- `nums` 中的数字可能重复

### 题解
可以发现，由于重复数字的影响，在每一层中可选的元素并非剩余的所有元素，而是选择“不同的数字”，因此需要对每一层的选择进行去重

具体的实现方法：
- 法零：用set存储最终答案，自动去重 （空间换时间，比较暴力）
- 法一：可以在每一层for循环中，单独使用一个set来记录已经选择过的数字，如果当前数字已经在set中出现过，则跳过该数字 （空间换时间）
- 法二：**先把数组排列**，每一层的for循环中，如果当前数字和上一个数字一样，就跳过这个数字 （每一次排序都是 $O(n \log n)$ 的时间复杂度的哦）

```cpp
//法零 用set存ans，实现去重，但是过于暴力
int n = nums.size();
set<vector<int>> ans;
vector<int> perm;
vector<int> used(n);
autpo traceback = [&](auto &self) {
    if (perm.size() == n) {
        ans.insert(perm);
        return;
    }
    
    for (int i = 0; i < n; i ++) {
        if (used[i]) continue; //剪枝
        used[i] = 1; //状态更新
        perm.push_back(nums[i]);
        self(self); //状态转移
        perm.pop_back(); //状态回滚
        used[i] = 0; //状态回滚
    }
};
traceback(traceback);
return vector<vector<int>>(ans.begin(), ans.end());
```

```cpp
// 法一
int n = nums.size();
vector<vector<int>> ans;
vector<int> perm;
vector<int> used(n); 
auto traceback = [&](auto &self) {
    if (perm.size() == n) {
        ans.push_back(perm);
        return;
    }
    vector<int> levelUsed(21); //记录本层使用过的数字
    for (int i = 0; i < n; i ++) {
        if (used[i]) continue; //剪枝
        if (levelUsed[nums[i] + 10]) continue; //本层已经使用过该数字
        levelUsed[nums[i] + 10] = 1; //标记本层使用过该数字
        used[i] = 1; //状态更新
        perm.push_back(nums[i]);
        self(self); //状态转移
        perm.pop_back(); //状态回滚
        used[i] = 0; //状态回滚
    }
};
traceback(traceback);
return ans;
```

```cpp
// 法二
int n = nums.size();
sort(nums.begin(), nums.end()); //先排序
vector<vector<int>> ans;
vector<int> perm;
vector<int> used(n);
auto traceback = [&](auto &self) {
    if (perm.size() == n) {
        ans.push_back(perm);
        return;
    }
    for (int i = 0; i < n; i ++) {
        if (used[i]) continue; //剪枝

        // 本方案关键，注意边界条件
        if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue; //去重

        used[i] = 1; //状态更新
        perm.push_back(nums[i]);
        self(self); //状态转移
        perm.pop_back(); //状态回滚
        used[i] = 0; //状态回滚
    }
};
traceback(traceback);
return ans;
```

```cpp
// 法三 next_permutation 可以自动去重
int n = nums.size();
sort(nums.begin(), nums.end()); 
vector<vector<int>> ans;
do {
    ans.push_back(nums);
} while (next_permutation(nums.begin(), nums.end()));
return ans;
```
---

## 8.3 Leetcode 81 组合总和
### 题目描述
给你一个**无重复元素**的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为 `target` 的 **所有不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。
`candidates` 中的数字可以无限制重复被选取。对于给定的输入，保证和为 `target` 的不同组合数少于 150 个。
**示例 1：**
```
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
```
**示例 2：**
```
输入：candidates = [2,3,5], target = 8
输出：[[2,2,2,2],[2,3,3],[3,5]]
```
**示例 3：**
```
输入：candidates = [2], target = 1
输出：[]
```
**提示：**
- `1 <= candidates.length <= 30`
- `1 <= candidates[i] <= 200`
- `candidates` 中的每个元素都 互不相同
- `1 <= target <= 500`
- 题目保证和为 `target` 的不同组合数少于 150 个
  
### 题解

首先根据题意，可以想到，第一次剪枝就是要判断每一条路径上的和是否已经超过了 `target`，如果超过了，就不需要继续枚举下去了

**同时，根据组合的性质** `2->3->6` 和 `3->2->6` 是同一个组合，因此我们需要保证每一层枚举的数字都是从上一个选择的数字开始的，来避免重复枚举同一个组合,此为第二次剪枝

根据上面的两种剪枝思路可以生成两个辅助状态，`sum` 来记录当前路径上的和， `lower` 来记录当前层枚举的下界

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> ans;
        vector<int> comb;
        auto traceback = [&](auto &self, int lower, int sum) {
            if (sum == target) {
                ans.push_back(comb);
                return;
            }

            for (int i = lower; i < candidates.size(); i++) {
                if (sum + candidates[i] > target) continue;
                comb.push_back(candidates[i]);
                self(self, i, sum + candidates[i]);
                comb.pop_back();
            }
        };
        traceback(traceback, 0, 0);
        return ans;
    }
};
```
---

## 8.4 Leetcode 39 组合总和 II
### 题目描述
给定一个**有重复元素**的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为 `target` 的 **所有不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。
`candidates` 中的每个数字在每个组合中只能使用 **一次**。对于给定的输入，保证和为 `target` 的不同组合数少于 150 个。
**示例 1：**
```
输入：candidates = [10,1,2,7,6,1,5], target = 8
输出：[[1,1,6],[1,2,5],[1,7],[2,6]]
```
**示例 2：**
```
输入：candidates = [2,5,2,1,2], target = 5
输出：[[1,2,2],[5]]
```
**示例 3：**
```
输入：candidates = [1], target = 1
输出：[[1]]
```
**提示：**
- `1 <= candidates.length <= 100`   
- `1 <= candidates[i] <= 50`
- `1 <= target <= 30`

### 题解
与上一题的区别在于 **每个数字只能使用一次**，且在给定`candidates` 中有重复元素，所以和全排列 II 一样，需要考虑去重
用到的方法是：
先对 `candidates` 进行排序，在每一层枚举的时候，如果当前数字和上一个数字一样，就代表重复了，因此跳过这个数字即可
```cpp
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        sort(candidates.begin(), candidates.end()); //
        vector<vector<int>> ans;
        vector<int> comb;
        auto traceback = [&](auto &self, int lower, int sum) {
            if (sum == target) {
                ans.push_back(comb);
                return;
            }

            int last = 0; //

            for (int i = lower; i < candidates.size(); i++) {
                if (sum + candidates[i] > target) continue;

                if (last == candidates[i]) continue; //
                last = candidates[i]; //

                comb.push_back(candidates[i]);
                self(self, i + 1, sum + candidates[i]); //
                comb.pop_back();
            }
        };
        traceback(traceback, 0, 0);
        return ans;
    }
};
```
---

## 8.5 Leetcode 17 电话号码的字母组合
### 题目描述
给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。答案可以按 **任何顺序** 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯8.5.png " width="300"/>
  </div>
</div>

**示例 1：**
```
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
```
**示例 2：**
```
输入：digits = ""
输出：[]
```
**提示：**
- `0 <= digits.length <= 4`
- `digits[i]` 是范围 `['2', '9']` 的一个数字。

### 题解
这题主要看一下怎么存的各个字母，有点秀
```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits) {
        vector<string> phone = {
            "",
            "",
            "abc",
            "def",
            "ghi",
            "jkl",
            "mno",
            "pqrs",
            "tuv",
            "wxyz"
        };
        vector<string> ans;
        string comb;
        auto traceback = [&](auto &self) {
            if (comb.size() == digits.size()) {
                if (comb.size() != 0) ans.push_back(comb);
                return;
            }

            int d = digits[comb.size()] - '0';
            for (char c : phone[d]) {
                comb += c;
                self(self);
                comb.pop_back();
            }
        };
        traceback(traceback);
        return ans;
    }
};
```
---

## 8.6 Leetcode 87 复原IP地址
### 题目描述
给定一个只包含数字的字符串 `s` ，复原它并返回所有可能的 IP 地址格式。
IP 地址由四部分组成，每部分是一个 0 到 255 之间的整数，且不能包含前导零。返回的 IP 地址可以按 **任何顺序** 排列。
**示例 1：**
```    
输入：s = "25525511135"
输出：["255.255.11.135","255.255.111.35"]
```

**示例 2：**
```    
输入：s = "0000"
输出：["0.0.0.0"]
```

**示例 3：**
``` 
输入：s = "1111"
输出：["1.1.1.1"]
```

**示例 4：**
```    
输入：s = "010010"
输出：["0.10.0.10","0.100.1.0"]
```

**示例 5：**
```
输入：s = "10203040"
输出：["10.20.30.40","102.0.30.40","10.203.0.40"]
```

### 题解
单纯用字符串难以处理，因此我们可以用一个长度为4的整数数组来存储当前的IP地址的四个部分，这样就可以方便地进行状态更新和回滚了，最后输出答案还很方便

```cpp
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;
        vector<int> ip;// 用int快速判断，最后一起放到string里面
        auto traceback = [&](auto &self, int pos) {
            if (pos == s.size()) { 
                if (ip.size() == 4) { //防溢出
                    ans.push_back("" + to_string(ip[0]) + "." + to_string(ip[1]) + "." + to_string(ip[2]) + "." + to_string(ip[3]));
                }
                return;
            }

            //单独成一组
            if (ip.size() < 4) {
                ip.push_back(s[pos] - '0');
                self(self, pos + 1);
                ip.pop_back();
            }
            //和前一个数字成一组
            if (ip.size() && ip.back() != 0) {
                int next = ip.back() * 10 + s[pos] - '0';
                if (next <= 255) {
                    ip.back() = next;
                    self(self, pos + 1);
                    ip.back() /= 10;
                }
            }
        };
        traceback(traceback, 0);
        return ans;
    }
};
```

## 8.7 Leetcode 37 解数独
### 题目描述
编写一个程序，通过填充空格来解决数独问题。
一个数独的解法需遵循如下规则：
- 数字 1-9 在每一行只能出现一次。
- 数字 1-9 在每一列只能出现一次。
- 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
- 空白格用 '.' 表示。
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯 4.png " width="600"/>
  </div>
</div>

**示例 1：**
```
输入：
board = [
["5","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]
]
输出：[
["5","3","4","6","7","8","9","1","2"],
["6","7","2","1","9","5","3","4","8"],
["1","9","8","3","4","2","5","6","7"],
["8","5","9","7","6","1","4","2","3"],
["4","2","6","8","5","3","7","9","1"],
["7","1","3","9","2","4","8","5","6"],
["9","6","1","5","3","7","2","8","4"],
["2","8","7","4","1","9","6","3","5"],
["3","4","5","2","8","6","1","7","9"]
]
```

### 题解
<blockquote class="orange-quote">

**关键点：**
pos 一维转二维；
剪枝；
单个答案，找到后直接返回
</blockquote>

```cpp
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        int rows[9][9] = {};
        int cols[9][9] = {};
        int grids[3][3][9] = {};

        // 初始化辅助状态 
        //用于记录在 行 列 宫 中出现过的数字 出现过则为 1        
        for (int i = 0; i < 9; i ++) {
            for (int j = 0; j < 9; j ++) {
                if (board[i][j] == '.') continue;
                int d = board[i][j] - '1';
                rows[i][d] = 1;
                cols[j][d] = 1;
                grids[i / 3][j / 3][d] = 1;
            }
        }

        auto traceback = [&](auto &self, int pos) -> bool { // 一维记录 pos
            if (pos == 81) return true;
            // 一维转二维
            int x = pos / 9,  y = pos % 9;

            // 已经有数字，直接跳过，进入下一层
            if (board[x][y] != '.') return self(self, pos + 1);

            //枚举每个数字
            for (int d = 0; d < 9; d ++) {
                // 非法状态 剪枝
                if (rows[x][d] || cols[y][d] || grids[x / 3][y / 3][d]) continue;

                board[x][y] = d + '1';
                rows[x][d] = 1;
                cols[y][d] = 1;
                grids[x / 3][y / 3][d] = 1;

                // 因为答案只有一种，所以在最后一层找到答案后，直接一路往上返回
                if (self(self, pos + 1)) return true; 、

                board[x][y] = '.';
                rows[x][d] = 0;
                cols[y][d] = 0;
                grids[x / 3][y / 3][d] = 0;                
            }
            //枚举都失败了，此路不通，返回false
            return false;
        };
        traceback(traceback, 0);
    }
};
```
---

## 8.8 Leetcode 51 N 皇后
### 题目描述
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

**n 皇后问题** 研究的是如何将 `n` 个皇后放置在 `n×n` 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 `n` ，返回所有不同的 **n 皇后问题** 的解决方案。

每一种解法包含一个不同的 **n 皇后问题** 的棋子放置方案，该方案中 `'Q'` 和 `'.'` 分别代表了皇后和空位。

**示例 1：**
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯8.8.jpg " width="500"/>
  </div>
</div>

```
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
```
**示例 2：**
```
输入：n = 1
输出：[["Q"]]
```
**提示：**
- `1 <= n <= 9`

### 题解
本题的关键点在于：
- 如何高效地遍历
- 如何记录每个皇后的攻击范围

针对第一个问题，根据题意可以知道，每个皇后的攻击范围是所在的行、列、斜线，也就是说，如果我们在第一行放了一个皇后，那么这下一个皇后一定不会出现在第一行，因此我们可以按照行来进行枚举，每一层枚举放在哪一列。这样的话在记录每个皇后攻击范围的时候也不用单独统计行

针对第二个问题，首先可以按照第一个问题下的思路，开一个 `n` 大小的数组记录某一列**是否有皇后** ($O(1)$ 的复杂度，切记不要用一个二维数组计算某个位置是否有皇后，那样子的复杂度是 $O(n)$ 的)
按照这个思路，同一方向的斜线的数量是 $2n - 1$，因此我们可以开两个大小为 $2n - 1$ 的数组来记录两条斜线的攻击范围
注意，每有一个皇后，更新数组时要 `+1`，回滚时要 `-1`，因为可能有多个皇后攻击同一个位置
注意映射关系

```cpp
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        vector<int> col(n, 0), dg(2 * n - 1, 0), bdg(2 * n - 1, 0);

        auto traceback = [&](auto &self, int row) {
            if (row == n) {
                ans.push_back(board);
                return;
            }

            for (int i = 0; i < n; i ++) {
                //判定是否合法，注意反斜线的映射关系
                if (col[i] || dg[row + i] || bdg[row - i + n - 1]) continue;
                board[row][i] = 'Q';
                col[i] = dg[row + i] = bdg[row - i + n - 1] = 1;
                self(self, row + 1);
                board[row][i] = '.';
                col[i] = dg[row + i] = bdg[row - i + n - 1] = 0;
            }
        };
        traceback(traceback, 0);
        return ans;
    }
};
```
---

## 8.9 Leetcode 679 24 点游戏
### 题目描述
给定一个长度为4的整数数组 `cards` 。你有 `4` 张卡片，每张卡片上都包含一个范围在 `[1,9]` 的数字。您应该使用运算符 `['+', '-', '*', '/']` 和括号 `'('` 和 `')'` 将这些卡片上的数字排列成数学表达式，以获得值24。

你须遵守以下规则: 

- 除法运算符 `'/'` 表示实数除法，而不是整数除法。
    - 例如， `4 /(1 - 2 / 3)= 4 /(1 / 3)= 12` 。
- 每个运算都在两个数字之间。特别是，不能使用 `“-”` 作为一元运算符。
    - 例如，如果 `cards =[1,1,1,1]` ，则表达式 `“-1 -1 -1 -1”` 是 **不允许** 的。
- 你不能把数字串在一起
    - 例如，如果 `cards =[1,2,1,2]` ，则表达式 `“12 + 12”` 无效。

如果可以得到这样的表达式，其计算结果为 `24` ，则返回 `true `，否则返回 `false` 。

**示例 1:**

    输入: cards = [4, 1, 8, 7]
    输出: true
    解释: (8-4) * (7-1) = 24

**示例 2:**

    输入: cards = [1, 2, 1, 2]
    输出: false

**提示:**

- `cards.length == 4`
- `1 <= cards[i] <= 9`


### 题解
<blockquote class="orange-quote">

本题重点在于如何处理每个元素是否被用过
可以维护一个`used` 数组，初始四个元素都设置为 `0`，当一个元素**被使用**时，设置为 `True`，回滚时设置为 `False`
同时把运算生成的元素加入到数组中，设置为'False'，回滚时删除这个元素
</blockquote>

```cpp
class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        vector<double> nums(4);
        for (int i = 0; i < 4; i ++) nums[i] = cards[i];
        vector<int> used(4, 0);

        auto calc = [&](double a, double b, char op) {
            if (op == '+') return a + b;
            if (op == '-') return a - b;
            if (op == '*') return a * b;
            return a / b;
        };


        auto traceback = [&](auto &self) {
            if (nums.size() == 7) { // 四个数字和三个运算符 最后生成结果时候数组长度为7
                return abs(24 - nums.back()) < 1e-6;
            }

            for (int i = 0; i < nums.size(); i ++) {
                if (used[i]) continue;
                for (int j = 0; j < nums.size(); j ++) {
                    if (used[j] || j == i)  continue;

                    used[i] = used[j] = 1;

                    for (char op : "+-*/") {
                        nums.push_back(calc(nums[i], nums[j], op));
                        used.push_back(0);

                        if (self(self)) return true;

                        nums.pop_back();
                        used.pop_back();
                    }
                    used[i] = used[j] = 0;
                }
            }
            return false;
        };
        return traceback(traceback);
    }
};
```
---

## 8.10 lq3511 飞机降落
### 问题描述

$N$ 架飞机准备降落到某个只有一条跑道的机场。其中第 $i$ 架飞机在 $T_i$ 时刻到达机场上空，到达时它的剩余油料还可以继续盘旋 $D_i$ 个单位时间，即它最早可以于 $T_i$ 时刻开始降落，最晚可以于 $T_i + D_i$ 时刻开始降落。降落过程需要 $L_i$ 个单位时间。

一架飞机降落完毕时，另一架飞机可以立即在同一时刻开始降落，但是不能在前一架飞机完成降落前开始降落。

请你判断 $N$ 架飞机是否可以全部安全降落。

### 输入格式

输入包含多组数据。

第一行包含一个整数 $T$，代表测试数据的组数。

对于每组数据，第一行包含一个整数 $N$。

以下 $N$ 行，每行包含三个整数：$T_i$，$D_i$ 和 $L_i$。

### 输出格式

对于每组数据，输出 `YES` 或者 `NO`，代表是否可以全部安全降落。

### 样例输入
```
2
3
0 100 10
10 10 10
0 2 20
3
0 10 20
10 10 20
20 10 20
```
### 样例输出
```
YES
NO
```
### 样例说明
对于第一组数据，可以安排第 $3$ 架飞机于 $0$ 时刻开始降落，$20$ 时刻完成降落。安排第 $2$ 架飞机于 $20$ 时刻开始降落，$30$ 时刻完成降落。安排第 $1$ 架飞机于 $30$ 时刻开始降落，$40$ 时刻完成降落。

对于第二组数据，无论如何安排，都会有飞机不能及时降落。

### 评测用例规模与约定
对于 $30\%$ 的数据，$N \leq 2$。

对于 $100\%$ 的数据，$1 \leq T \leq 10$，$1 \leq N \leq 10$，$0 \leq T_i, D_i, L_i \leq 10^5$。

### 题解
初见有点像贪心里面的区间的相关问题，但是鉴于本题限制条件比较复杂，贪心策略下没有比较好的解决方法
所以转向回溯的策略：
只需要生成飞机编号的全排列，然后对于每一种排列，按照这个顺序来安排飞机降落，判断是否满足条件即可

**method 1**：直接生成全排列，暴力枚举每一种情况，时间复杂度是 $O(n! * n)$ 的
```cpp
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T --) {
        int n; cin >> n;
        vector<tuple<int, int, int>> planes(n);
        
        for (auto &[t, d, l] : planes) cin >> t >> d >> l;
        
        auto can_land = [&]() {
            int last = 0;
            for (auto &[t, d, l] : planes) {
                if (t + d < last) return false;
                last = max(last, t) + l;
            }
            return true;
        };

        auto check = [&]() {
            sort(planes.begin(), planes.end());
            do {
                if (can_land()) return true;
            } while (next_permutation(planes.begin(), planes.end()));
            return false;
        };
        cout << (check() ? "YES" : "NO") << "\n";
    }
}
```

**method 2**：
把所有全排列列出来再判断等于没有剪枝捏
所以边生成全排列边判断是否合法，剪掉不合法的分支
```cpp
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T; cin >> T;
    while (T --) {
        int n; cin >> n;
        vector<tuple<int, int, int>> planes(n);
        
        for (auto &[t, d, l] : planes) cin >> t >> d >> l;
        
        vector<int> used(n);

        auto traceback =[&](auto &self, int cnt, int last) {
            if (cnt == n) return true;

            for (int i = 0; i < n; i ++) {
                if (used[i]) continue;
                auto [t, d, l] = planes[i];
                if (t + d < last) continue; // 剪枝
                used[i] = true;
                if (self(self, cnt + 1, max(last, t) + l)) return true; 
                used[i] = false;
            }
            return false;
        };

        cout << (traceback(traceback, 0, 0) ? "YES" : "NO") << "\n";
    }
}
```

---

## 8.11 lq19712 数字接龙
!!! : 本题重点在于如何处理交叉，以及二维迷宫中如何快速移动

### 问题描述

小蓝最近迷上了一款名为《数字接龙》的迷宫游戏，游戏在一个大小为 $N \times N$ 的格子棋盘上展开，其中每一个格子处都有着一个 $0 \ldots K-1$ 之间的整数。游戏规则如下：

从左上角 $(0,0)$ 处出发，目标是到达右下角 $(N-1, N-1)$ 处的格子，每一步可以选择沿着水平/垂直/对角线方向移动到下一个格子。

对于路径经过的棋盘格子，按照经过的格子顺序，上面的数字组成的序列要满足：$0, 1, 2, \ldots, K-1, 0, 1, 2, \ldots, K-1, 0, 1, 2 \ldots$。

途中需要对棋盘上的每个格子恰好都经过一次（仅一次）。

路径中不可以出现交叉的线路。例如之前有从 $(0,0)$ 移动到 $(1,1)$，那么再从 $(1,0)$ 移动到 $(0,1)$ 线路就会交叉。

为了方便表示，我们对可以行进的所有八个方向进行了数字编号，如下图 2 所示；因此行进路径可以用一个包含 $0 \ldots 7$ 之间的数字字符串表示，如下图 1 是一个迷宫示例，它所对应的答案就是：`41255214`。

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯8.11.png " width="500"/>
  </div>
</div>

现在请你帮小蓝规划出一条行进路径并将其输出。如果有多条路径，输出字典序最小的那一个；如果不存在任何一条路径，则输出 $-1$。

### 输入格式

第一行包含两个整数 $N, K$。

接下来输入 $N$ 行，每行 $N$ 个整数表示棋盘格子上的数字。

### 输出格式

输出一行表示答案。如果存在答案输出路径，否则输出 $-1$。

### 样例输入
```
3 3
0 2 0
1 1 1
2 0 2
```
### 样例输出
```
41255214
```
### 样例说明

行进路径如图 1 所示。

### 评测用例规模与约定

对于 $80\%$ 的评测用例：$1 \leq N \leq 5$。

对于 $100\%$ 的评测用例：$1 \leq N \leq 10, 1 \leq K \leq 10$。

### 题解
首先拆解这道题
**辅助状态**：
- 一个用于记录路径的字符串 `path` 
- 当前位置 `pos`
- 一个 `vis[][]` 数组来记录每个格子是否被访问过

**限制条件**：
- 1. 最后要走到`n - 1, n - 1` 处
- 2. 要遍历所有格子
- 3. 0 , 1, 2, ... K - 1 
- 4. 不能交叉
- 5. 八个方向移动（网格移动如何快速写出？）

**Solution**：
- 1. 检查最后 `pos == n ^ 2 - 1` 就行
- 2. 检查字符串长度 `path.size() == n ^ 2 `
- 3. 直接判断
- 4. 最朴素的方式是直接记录之前的路径，每次移动都检查是否交叉，十分麻烦。
  - 针对这个问题，我们可以把整个棋盘放大一倍，即可解决，原理如下
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\回溯8.11-2.png " width="500"/>
  </div>
  <div style="text-align:center;">
    <img src="photos\回溯8.11-3.png " width="500"/>
  </div>
</div>


**如何在迷宫中移动？**
用一个数组 `dir` 来记录每个方向移动两个方向上的偏移量
```cpp
vector<pair<int, int>> dir = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};
```

AC代码
```cpp
vector<pair<int, int>> dir = {
    {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector(n, vector<int>(n));

    auto maze = vector(n * 2, vector(n * 2, 0));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            cin >> maze[i * 2][j * 2];
        }
    }
    auto vis = vector(n * 2, vector(n * 2, 0));
    string ans ;

    auto inside = [&](int x, int y) { // 迷宫问题基本都需要这个，判断是否还在迷宫中
        return x >= 0 && x < n * 2 && y >= 0 && y < n * 2;
    };

    auto traceback = [&](auto &self, int x, int y) {
        if (x == n * 2 - 2 && y == n * 2 - 2) {
            if ((int)ans.size() == n * n - 1) return true;
            return false;
        }

        for (int d = 0; d < 8; d ++) {
            auto [dx, dy] = dir[d];
            int nx = x + dx, ny = y + dy; //next_x, next_y 但是要走两步
            //同时 nx和 ny 也是必要的，因为要判断是否交叉
            int nnx = nx + dx, nny = ny + dy; //next_next_x, next_next_y
            
            if (!inside(nnx, nny)) continue; //只需要nnx和nny判断是否越界，因为nx和ny在两点之间，越界了就不合法
            if (vis[nx][ny] || vis[nnx][nny]) continue; //判断是否交叉，nx和ny在两点之间，nnx和nny在要去的点上
            if (maze[nnx][nny] != (maze[x][y] + 1) % k) continue; //判断数字是否满足要求
            vis[nx][ny] = vis[nnx][nny] = true;
            ans += d + '0'; //字符串

            if (self(self, nnx, nny)) return true;

            //还原
            ans.pop_back();
            vis[nx][ny] = vis[nnx][nny] = false;
        }
        return false;
    };

    vis[0][0] = true; //起点
    if (traceback(traceback, 0, 0) && maze[0][0] == 0) {
        cout << ans << "\n";
    } else {
        cout << -1 << "\n";
    }
}
```

<blockquote class="orange-quote">
本题目前未找到任何做法（在不进行特判的情况下）进行有效剪枝通过 n=10，k=1 的数据。

But Why?
因为此时 `0, 1, 2, ... k - 1` 中只有一个数字 `0`，因此对于每个格子来说，满足条件的下一个格子就是它周围的所有格子，因此没有任何剪枝效果了
</blockquote>

---

## 8.12 P8642 [蓝桥杯 2016 国 AC] 路径之谜（疑似错题） lq89

### 题目背景

本题疑似为错题，不保证存在对于任意合法输入都能在时限内给出答案的算法。为了保证本题尽可能可做，我们已经根据蓝桥杯中本题实际的测试数据范围进行缩小，原数据范围 $N\leq 20$ 应该完全无解。

本题为搜索题，本题不接受 hack 数据。[关于此类题目的详细内容。](https://www.luogu.com.cn/paste/pf94n89x)

### 题目描述

小明冒充 $X$ 星球的骑士，进入了一个奇怪的城堡。

城堡里边什么都没有，只有方形石头铺成的地面。

假设城堡地面是 $n\times n$ 个方格。如图所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/ku6hk346.png)

按习俗，骑士要从西北角走到东南角。

可以横向或纵向移动，但不能斜着走，也不能跳跃。

每走到一个新方格，就要向正北方和正西方各射一箭。

（城堡的西墙和北墙内各有 $n$ 个靶子）

同一个方格只允许经过一次。但不必做完所有的方格。

如果只给出靶子上箭的数目，你能推断出骑士的行走路线吗？

有时是可以的，比如如图中的例子。

本题的要求就是已知箭靶数字，求骑士的行走路径（测试数据保证路径唯一）

### 输入格式

第一行一个整数 $N(1\leq N\leq 10)$，表示地面有 $N \times N$ 个方格。

第二行 $N$ 个整数，空格分开，表示北边的箭靶上的数字（自西向东）

第三行 $N$ 个整数，空格分开，表示西边的箭靶上的数字（自北向南）

### 输出格式

一行若干个整数，表示骑士路径。

为了方便表示，我们约定每个小格子用一个数字代表，从西北角开始编号 $:0,1,2,3 \cdots $。

比如，图中的方块编号为：

```
0  1  2  3
4  5  6  7
8  9  10 11
12 13 14 15
```
### 输入 

```
4
2 4 3 4
4 3 3 3
```

### 输出 

```
0 4 5 1 2 3 7 11 10 9 13 14 15
```

### 说明/提示
时限 1 秒, 256M。蓝桥杯 2016 年第七届国赛

### 题解
本题思路和上题类似，属于搜索类的题目，以下是初始代码，蓝桥杯上没有tle但是洛谷上tle了
```cpp
vector<pair<int, int>> dir = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<int> col(n), row(n);
    int total = 0; //用 accumulate 替代 
    //accumulate(col.begin(), col.end(), 0)
    for (int i = 0; i < n; i ++) {cin >> col[i]; total += col[i];}
    for (int i = 0; i < n; i ++) {cin >> row[i];}
    vector<int>ans;
    auto maze = vector(n, vector<int>(n, 0));

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    auto traceback = [&](auto &self, int x, int y) {
        if (x == n - 1 && y == n - 1) {
            if ((int)ans.size() == total && ans.back() == n * n - 1) return true;
            return false;
        } // check

        for (int d = 0; d < 4; d ++) {
            auto [dx, dy] = dir[d];
            int nx = x + dx, ny = y + dy;

            //限制条件
            if (!inside(nx, ny)) continue;
            if (maze[nx][ny]) continue;
            if (!row[nx] || !col[ny]) continue; // check

            //状态转移
            maze[nx][ny] = 1;
            row[nx] --; col[ny] --; 
            ans.push_back(nx * n + ny); // 记录路径

            //进入下一层
            if (self(self, nx, ny)) return true;

            //回溯
            ans.pop_back();
            maze[nx][ny] = 0;
            row[nx] ++; col[ny] ++; 
        }
        return false;
    };

    //起点特判
    maze[0][0] = 1;
    col[0] --; row[0] --;
    ans.push_back(0); //注意这一步是必须的，不然在trace back里面pushback的始终会少一个
    
    if (traceback(traceback, 0, 0)) {
        for (int i : ans) cout << i << " " ;
    } else {
        cout << -1 << "\n";
    }
}
```

**思考剪枝的策略：**
可以发现，当某一个北方的靶子剩余箭数为**1**时，如果想往左走，那么是无法到达终点的，因此若位于这一列左侧的北方的箭靶必须剩余箭数为0，否则就剪掉这个分支
对于西方的靶子同理

以下是ac代码
```cpp
vector<pair<int, int>> dir = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    int target = n * n - 1;
    vector<int> col(n), row(n);
     int total = 0; //用 accumulate 替代 
    //accumulate(col.begin(), col.end(), 0)
    for (int i = 0; i < n; i ++) {cin >> col[i]; total += col[i];}
    for (int i = 0; i < n; i ++) {cin >> row[i];}
    vector<int>ans;
    auto maze = vector(n, vector<int>(n, 0));

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    auto traceback = [&](auto &self, int x, int y) {
        if (x == n - 1 && y == n - 1) {
            if ((int)ans.size() == total && ans.back() == target) return true;
            return false;
        } // check

        // if (x == n - 1 && y == n - 1) {
        //     if (accumulate(row.begin(), row.end(), 0) == 0 && 
        //         accumulate(col.begin(), col.end(), 0) == 0) return true;
        //     return false;
        // }

        for (int d = 0; d < 4; d ++) {
            auto [dx, dy] = dir[d];
            int nx = x + dx, ny = y + dy;

            //限制条件
            if (!inside(nx, ny)) continue;
            if (maze[nx][ny]) continue;
            if (!row[nx] || !col[ny]) continue; // check
            // 附加剪枝条件
            if (row[nx] == 1 && accumulate(row.begin(), row.begin() + nx, 0) != 0) continue;
            if (col[ny] == 1 && accumulate(col.begin(), col.begin() + ny, 0) != 0) continue;

            //状态转移
            maze[nx][ny] = 1;
            row[nx] --; col[ny] --; 
            ans.push_back(nx * n + ny); // 记录路径

            //进入下一层
            if (self(self, nx, ny)) return true;

            //回溯
            ans.pop_back();
            maze[nx][ny] = 0;
            row[nx] ++; col[ny] ++; 
        }
        return false;
    };

    //起点特判
    maze[0][0] = 1;
    col[0] --; row[0] --;
    ans.push_back(0); //注意这一步是必须的，不然在trace back里面pushback的始终会少一个

    if (traceback(traceback, 0, 0)) {
        for (int i : ans) cout << i << " " ;
    } else {
        cout << -1 << "\n";
    }
}
```

该方法剪枝后比原来的方法在原来的case上显著变快，但是洛谷上还有一个case过不了，后期考虑dfs
比如下面这个case就不行
```
10
9 6 8 6 8 6 8 6 8 6 
8 7 8 7 7 8 8 7 1 10
```

---

## 8.13 P10419 [蓝桥杯 2023 国 A] 01 游戏 lq17100
!!! : 本题重点在于如何根据题目要求进行剪枝，以及在什么时机进行剪枝
    同时，针对数组中需要快速比较每一行和每一列是否相等时，首先考虑集合，其次，可以利用**位运算**的性质高效地存储和查询每一列或行的特征
### 题目描述

小蓝最近玩上了 $01$ 游戏，这是一款带有二进制思想的棋子游戏，具体来说游戏在一个大小为 $N\times N$ 的棋盘上进行，棋盘上每个位置都需要放置一位数字 $0$ 或者数字 $1$，初始情况下，棋盘上有一部分位置已经被放置好了固定的数字，玩家不可以再进行更改。玩家需要在其他所有的空白位置放置数字，并使得最终结果满足以下条件：

1. 所有的空白位置都需要放置一个数字 $0/1$；
2. 在水平或者垂直方向上，相同的数字不可以连续出现大于两次；
3. 每一行和每一列上，数字 $0$ 和数字 $1$ 的数量必须是相等的 (例如 $N=4$，则表示每一行/列中都需要有 $2$ 个 $0$ 和 $2$ 个 $1$)；
4. 每一行都是唯一的，因此每一行都不会和另一行完全相同；同理每一列也都是唯一的，每一列都不会和另一列完全相同。

现在请你和小蓝一起解决 $01$ 游戏吧！题目保证所有的测试数据都拥有一个唯一的答案。

### 输入格式

输入的第一行包含一个整数 $N$ 表示棋盘大小。

接下来 $N$ 行每行包含 $N$ 个字符，字符只可能是 `0`、`1`、`_` 中的其中一个 (ASCII 码分别为 $48$，$49$，$95$)，`0` 表示这个位置数字固定为 $0$，`1` 表示这个位置数字固定为 $1$，`_` 表示这是一个空白位置，由玩家填充。

### 输出格式

输出 $N$ 行每行包含 $N$ 个字符表示题目的解，其中的字符只能是 `0` 或者 `1`。

#### 输入 

```
6
_0____
____01
__1__1
__1_0_
______
__1___

```

#### 输出

```
100110
010101
001011
101100
110010
011001

```

### 说明/提示

**【评测用例规模与约定】**

对于 $60\%$ 的评测用例，$2\le N\le 6$;  
对于所有评测用例，$2\le N\le 10$，$N$ 为偶数。

### 题解
本道题本质上和填数独比较像，但是限制条件比较复杂，复杂之处在于：
**根据条件在何处进行剪枝需要斟酌**
比如，为了保证出现的次数都是 `n/2`，一种方法是在每一次填入数字时，都检查当前行和当前列的数字出现次数，如果已经超过 `n/2` 就剪掉这个分支
另一种是在每一行或每一列都填完之后，才检查是否满足条件。

以下是本体的主要限制条件和解决方法：
1. 在水平或者垂直方向上，相同的数字不可以连续出现大于两次；
   - 直接在每次填入数字时检查，如果当前行或者当前列的最后两个数字和要填入的数字相同，就剪掉这个分支
2. 每一行和每一列上，数字 $0$ 和数字 $1$ 的数量必须是相等的 (例如 $N=4$，则表示每一行/列中都需要有 $2$ 个 $0$ 和 $2$ 个 $1$)；
   - 在每一行或列填完之后再检查
3. 每一行都是唯一的，因此每一行都不会和另一行完全相同；同理每一列也都是唯一的，每一列都不会和另一列完全相同。
   - 维护一个**集合**，每填完一行或一列就利用集合判断是否重复

可见，本题的限制条件比较复杂，使用函数来进行判断是非常清晰的

```cpp
vector<pair<int, int>> dir = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
};
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<string> board(n);
    for (auto &line : board) cin >> line;

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };
    
    // 满足每一行和每一列都不同的条件，说明每一行和每一列的1的分布都不同了
    auto check = [&]() {
        set<int> rows, cols; //集合存储每一行每一列
        // 行检验
        for (int i = 0; i < n; i ++) {
            int row = 0; 
            for (int j = 0; j < n; j ++) {
                if (board[i][j] == '1') row |= (1 << j); //重点
                // 这里不开数组来存，用row的二进制表达下的某一位来表示这一列是否有1
            }
            if (rows.find(row) != rows.end()) return false; //如果这个row已经存在了，说明这一行和之前的某一行重复了
            rows.insert(row);
        }
        // 列检验
        for (int j = 0; j < n; j ++) {
            int col = 0;
            for (int i = 0; i < n; i ++) {
                if (board[i][j] == '1') col |= (1 << i); //同样的，col的二进制表达下的某一位来表示这一行是否有1
            }
            if (cols.find(col) != cols.end()) return false; //如果这个col已经存在了，说明这一列和之前的某一列重复了
            cols.insert(col);
        }
        return true;
    };

    // 剩下两个限制条件，重复不超过两次和不超过半数
    auto can = [&](int x, int y, int c) {
        // 不超过两次
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            int cnt = 0;
            while (inside(nx, ny) && board[nx][ny] == c) {
                cnt++;
                if (cnt >= 2) return false; //重复不超过两次
                nx += dx; ny += dy;
            }
        }
        // 不超过半数
        // 行
        if (x == n - 1) {
            int cntZero = c == '0' ? 1 : 0;
            for (int i = 0; i < n - 1; i ++) {
                if (board[i][y] == '0') cntZero++;
            }
            if (cntZero * 2 != n) return false; //不超过半数
        }
        //列
        if (y == n - 1) {
            int cntZero = c == '0' ? 1 : 0;
            for (int j = 0; j < n - 1; j ++) {
                if (board[x][j] == '0') cntZero++;
            }
            if (cntZero * 2 != n) return false; //不超过半数
        }

        return true;
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * n) return check(); //check函数来判断当前的board是否合法

        int x = pos / n, y = pos % n;
        if (board[x][y] != '_') {
            if (!can(x, y, board[x][y])) return false; //处理特殊情况
            return self(self, pos + 1);
        }

        //剩下两个限制条件，重复不超过两次和不超过半数
        for (char c : {'0', '1'}) {
            if (can(x, y, c)) {
                board[x][y] = c;
                if (self(self, pos + 1)) return true;
                board[x][y] = '_';
            }
        }
        return false;
    };
    traceback(traceback, 0);
    for (auto &line : board) cout << line << "\n";
}
```

---

## 8.14 P9237 [蓝桥杯 2023 省 A] 像素放置
!!! : 扫雷怎么扫？ 时刻检查左上！

### 题目描述

小蓝最近迷上了一款名为《像素放置》的游戏，游戏在一个 $n \times m$ 的网格棋盘上进行，棋盘含有 $n$ 行，每行包含 $m$ 个方格。玩家的任务就是需要对这 $n \times m$ 个方格进行像素填充，填充颜色只有黑色或白色两种。有些方格中会出现一个整数数字 $x(0 \leq x \leq 9)$，这表示当前方格加上周围八个方向上相邻的方格（分别是上方、下方、左方、右方、左上方、右上方、左下方、右下方）共九个方格内有且仅有 $x$ 个方格需要用黑色填充。

玩家需要在满足所有数字约束下对网格进行像素填充，请你帮助小蓝来完成。题目保证所有数据都有解并且解是唯一的。

### 输入格式

输入的第一行包含两个整数 $n,m$，用一个空格分隔，表示棋盘大小。

接下来 $n$ 行，每行包含 $m$ 个字符，表示棋盘布局。字符可能是数字 $0 \sim 9$，这表示网格上的数字；字符还有可能是下划线（$\text{ASCII}$ 码为 $95$），表示一个不带有数字的普通网格。

### 输出格式

输出 $n$ 行，每行包含 $m$ 个字符，表示答案。如果网格填充白色则用字符 $0$ 表示，如果网格填充黑色则用字符 $1$ 表示。

### 输入输出样例

#### 输入

```
6 8
_1__5_1_
1_4__42_
3__6__5_
___56___
_688___4
_____6__
```

#### 输出 

```
00011000
00111100
01000010
11111111
01011110
01111110
```

### 说明/提示

#### 【样例说明】

![image](https://cdn.luogu.com.cn/upload/image_hosting/v8u2zzne.png)

上图左是样例数据对应的棋盘布局，上图右是此局游戏的解。例如第 $3$ 行第 $1$ 列处的方格中有一个数字 $3$，它周围有且仅有 $3$ 个格子被黑色填充，分别是第 $3$ 行第 $2$ 列、第 $4$ 行第 $1$ 列和第 $4$ 行第 $2$ 列的方格。

#### 【评测用例规模与约定】

对于 $50 \%$ 的评测用例，$1 \leq n,m \leq 5$；

对于所有评测用例，$1 \leq n,m \leq 10$。

### 题解
拿到题上手，可以先想好要哪些辅助状态：
- `cnt` 用于记录某一个格周围还能填多少个黑色格子
- `ans` 用于记录当前的填充方案
- `pos` 用于记录当前填充到哪个格子了

第一条限制条件可以想到，就是在每次填入一个格子时，都检查这个格子周围的数字格子，如果这个格子周围的数字格子已经满足了要求，那么就剪掉这个分支

然而这种方式的剪枝效果较差，比如全0的情况，最后才能判断

所以**引入第二条限制条件**，**当`pos`移动到某一个格子时，位于其左上方的格子的`cnt`必须为`0`，这是因为无论后面怎么移动，都不会改变左上方这个格子周围黑色格子的数量了。**

**可以看到**，第二条限制条件的剪枝效果要远远好于第一条限制条件

代码如下:
```cpp
vector<pair<int, int>> dir = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},  {0, 0},  {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto cnt = vector(n, vector(m, -1)); // -1 代表没有数字
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch; cin >> ch;
            if (isdigit(ch)) cnt[i][j] = ch - '0';
        }
    }
    vector<string> board(n, string(m, '0'));

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    auto can = [&](int x, int y, int c) {
        // check
        // restriction 2: 左上角
        if (x > 0 && y > 0 && cnt[x - 1][y - 1] > c) return false;
        if (x == n - 1 && y > 0 && cnt[x][y - 1] > c) return false;
        if (y == m - 1 && x > 0 && cnt[x - 1][y] > c) return false;
        if (x == n - 1 && y == m - 1 && cnt[x][y] > c) return false;

        //restriction 1: c == 1 时，周围九个格子都要满足条件
        if (c == 1) {
            for (auto[dx, dy] : dir) {
                int nx = x + dx, ny = y + dy;
                if (!inside(nx, ny)) continue;
                if (cnt[nx][ny] == -1) continue; // 没有数字
                if (cnt[nx][ny] == 0) return false; // 周围不能有0
            }
        }
        return true;
    };

    auto update = [&](int x, int y) {
        // update
        board[x][y] = '1';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (cnt[nx][ny] == -1) continue; // 没有数字
            cnt[nx][ny] --; 
        }
    };

    auto rollback = [&](int x, int y) {
        // rollback
        board[x][y] = '0';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (cnt[nx][ny] == -1) continue; // 没有数字
            cnt[nx][ny] ++; 
        }
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * m) return true;

        int x = pos / m, y = pos % m;
        if (can(x, y, 0)) { //check
            if (self(self, pos + 1)) return true;
        }
        if (can(x, y, 1)) {
            update(x, y); // update
            if (self(self, pos + 1)) return true;
            rollback(x, y); // rollback
        }

        return false;
    };
    traceback(traceback, 0);
    for (auto &line : board) cout << line << "\n";
}
```

然而又是蓝桥杯的数据过得了而洛谷过不了......
洛谷的标签是插头dp

**因此我们考虑进一步的剪枝：**
在前面的第二条剪枝规则，在当前格子填入1时，考虑左上方的格子
借鉴这个思路，在当前格子填入0时，在当前格子的右边一个和下面的两行三列六个格子共七个格子中，每个格子都有在当前格子填入0后，所能接受的1的最大数量，如果这个最大数量小于其实际需要的1的数量，那么就剪掉这个分支

比如下面这个例子
``` cpp
0 0 ?
- - 5
- - -
```
对于要填入`?`的格子来说，下面那个格子需要5个1，而在当前格子填入0后，右边一个格子最多只能接受4个1了，因此这个分支就可以剪掉了，即这个格子必须填1

***本题数字上也可以涂黑***

<blockquote class="orange-quote">

**这一步对应修改版中limit下的四层for循环，更细致地来说，对于当前格子周围的8个格子，能填入1的格子只有 `pos` 大于当前格子的格子。**
这里面有两步，需要在纸上细想一下
</blockquote>

```cpp
vector<pair<int, int>> dir = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},  {0, 0},  {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto cnt = vector(n, vector(m, -1)); // -1 代表没有数字
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch; cin >> ch;
            if (isdigit(ch)) cnt[i][j] = ch - '0';
        }
    }

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    //
    auto limit = vector(n ,vector(m, vector<int>(9))); //每一个位置对应的临界值
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            for (int d = 0; d < 9; d ++) {
                auto [dx, dy] = dir[d];
                int nx = i + dx, ny = j + dy;
                if (!inside(nx, ny)) continue;

                int c = 0; // 记录当前格子能接受的最大数量
                //因为前面dir有一定顺序，且实际上每个格子的limit和这个方向确实有关，所以用dd代替d来进行遍历
                for (int dd = 9 - d; dd < 9; dd ++)  {
                    auto [ddx, ddy] = dir[dd];
                    int nnx = nx + ddx, nny = ny + ddy;
                    if (inside(nnx, nny)) c ++; 
                } // 写这个循环目的是为了计算当前格子指向的的格子周围8个格子里面有几个是在给定区域内的
                //也就是说，这层循环的主要作用就是特判边界格子
                limit[i][j][d] = c;
            }
        }
    }
    //

    vector<string> board(n, string(m, '0'));


    auto can = [&](int x, int y, int c) {
        // check
        // restriction 3 
        if (c == 0) {
            for (int d = 0; d < 9; d ++) {
                auto [dx, dy] = dir[d];
                int nx = x + dx, ny = y + dy;
                if (!inside(nx, ny)) continue;
                if (cnt[nx][ny] == -1) continue; // 没有
                if (cnt[nx][ny] > limit[x][y][d]) return false; // 超过临界值了 剪枝 
            }
        }

        //restriction 1: c == 1 时，周围九个格子都要满足条件
        if (c == 1) {
            for (auto[dx, dy] : dir) {
                int nx = x + dx, ny = y + dy;
                if (!inside(nx, ny)) continue;
                if (cnt[nx][ny] == -1) continue; // 没有数字
                if (cnt[nx][ny] == 0) return false; // 周围不能有0
            }
        }
        return true;
    };

    auto update = [&](int x, int y) {
        // update
        board[x][y] = '1';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (cnt[nx][ny] == -1) continue; // 没有数字
            cnt[nx][ny] --; 
        }
    };

    auto rollback = [&](int x, int y) {
        // rollback
        board[x][y] = '0';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (cnt[nx][ny] == -1) continue; // 没有数字
            cnt[nx][ny] ++; 
        }
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * m) return true;

        int x = pos / m, y = pos % m;
        if (can(x, y, 0)) { //check
            if (self(self, pos + 1)) return true;
        }
        if (can(x, y, 1)) {
            update(x, y); // update
            if (self(self, pos + 1)) return true;
            rollback(x, y); // rollback
        }

        return false;
    };
    traceback(traceback, 0);
    for (auto &line : board) cout << line << "\n";
}
```

**以下是常数级优化思路**
在`can`函数中，每一次都要判断`inside(x, y)` 和 `cnt[x][y] == -1`
这一部分可以预处理
修改部分主要在 `neb` `can` `update` `rollback`函数中
```cpp
vector<pair<int, int>> dir = {
    {-1, -1}, {-1, 0}, {-1, 1},
    {0, -1},  {0, 0},  {0, 1},
    {1, -1},  {1, 0},  {1, 1}
};

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto cnt = vector(n, vector(m, -1)); // -1 代表没有数字
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char ch; cin >> ch;
            if (isdigit(ch)) cnt[i][j] = ch - '0';
        }
    }

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m;
    };

    //
    auto limit = vector(n ,vector(m, vector<int>(9))); //每一个位置对应的临界值
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            for (int d = 0; d < 9; d ++) {
                auto [dx, dy] = dir[d];
                int nx = i + dx, ny = j + dy;
                if (!inside(nx, ny)) continue;

                int c = 0; // 记录当前格子能接受的最大数量
                //因为前面dir有一定顺序，且实际上每个格子的limit和这个方向确实有关，所以用dd代替d来进行遍历
                for (int dd = 9 - d; dd < 9; dd ++)  {
                    auto [ddx, ddy] = dir[dd];
                    int nnx = nx + ddx, nny = ny + ddy;
                    if (inside(nnx, nny)) c ++; 
                } // 写这个循环目的是为了计算当前格子指向的的格子周围8个格子里面有几个是在给定区域内的
                //也就是说，这层循环的主要作用就是特判边界格子
                limit[i][j][d] = c;
            }
        }
    }
    //

    vector<string> board(n, string(m, '0'));

    // 邻居数组
    auto neb  = vector(n, vector(m, vector<tuple<int ,int ,int>>()));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            for (int d = 0; d < 9; d ++) {
                auto [dx, dy] = dir[d];
                int nx = i + dx, ny = j + dy;
                if (!inside(nx, ny)) continue;
                if (cnt[nx][ny] == -1) continue; // 没有数字
                neb[i][j].emplace_back(nx, ny, limit[i][j][d]); // 记录邻居格子的位置和方向
            }
        }
    }

    auto can = [&](int x, int y, int c) {
        // check
        for (auto [nx, ny, limit] : neb[x][y]) {
            if (c == 0) {
                if (cnt[nx][ny] > limit) return false; //如果当前格子是0，那么它周围的数字格子就不能超过这个limit
            } else {
                if (cnt[nx][ny] == 0) return false; //如果当前格子是1，那么它周围的数字格子就必须至少有一个
            }
        }
        return true;
    };

    auto update = [&](int x, int y) {
        // update
        board[x][y] = '1';
        for (auto [nx, ny, limit] : neb[x][y]) {
            cnt[nx][ny] --; //如果当前格子是1，那么它周围的数字格子就必须至少有一个，所以每个数字格子的计数都要减1
        }
    };

    auto rollback = [&](int x, int y) {
        // rollback
        board[x][y] = '0';
        for (auto [nx, ny, limit] : neb[x][y]) {
            cnt[nx][ny] ++; //回退的时候每个数字格子的计数都要加1
        }
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * m) return true;

        int x = pos / m, y = pos % m;
        if (can(x, y, 0)) { //check
            if (self(self, pos + 1)) return true;
        }
        if (can(x, y, 1)) {
            update(x, y); // update
            if (self(self, pos + 1)) return true;
            rollback(x, y); // rollback
        }

        return false;
    };
    traceback(traceback, 0);
    for (auto &line : board) cout << line << "\n";
}
```

力竭咯

---

## 8.15 P12224 [蓝桥杯 2023 国 Java B] 数和游戏 lq17140
!!! : 类数独，解决如何映射的问题 以及定义结构体

### 题目描述

数和游戏是一种棋盘填数游戏。棋盘上分为白色和灰色两种类型的格子。游戏目标是通过在白色的格子里填入数字 $1 \dots 9$ 来满足游戏要求。

游戏当中有一个称作“条目”的概念，条目指的就是在水平方向或者垂直方向上所有连续出现的白色格子的集合。具体来说从灰色格子右方（下方）相邻的白色格子出发，一直向右方（下方）行走直到走出棋盘边界或遇到灰色格子才停止，途中经过的所有的白色格子组成的集合就称为条目。例如上图中，我们用 $(x, y)$ 表示格子坐标，坐标 $(1, 4)$ 下方的条目就是由坐标 $(2, 4)$ 和 $(3, 4)$ 的白色格子构成的；坐标 $(5, 1)$ 右方的条目是由坐标 $(5, 2)$、$(5, 3)$ 的白色格子构成的。但注意坐标 $(7, 2)$、$(7, 3)$、$(7, 4)$ 处的格子的集合并不是一个条目，在加入坐标 $(7, 5)$ 的格子后才是一个条目。

游戏具体要求如下：游戏在一个 $M \times N$ 大小的格子棋盘上进行，其中格子分为白色和灰色两种类型：
1) 白色格子，此种类型的格子应当填入一个 $1 \dots 9$ 范围内的整数并满足所有灰色格子的要求；
2) 灰色格子，此种类型的格子用一条对角线将格子分为了左下（用 $A$ 表示）和右上（用 $B$ 表示）两部分，若 $A$ 中有数字，则表示 $A$ 所在的格子下方条目中的数字之和应该等于 $A$ 中的数字；若 $B$ 中有数字，则表示 $B$ 所在的格子右方条目中的数字之和应该等于 $B$ 中的数字。

除此之外还有一个重要的约束条件：
每一个条目中不能出现重复的数字，即在每一个条目之中，$1 \dots 9$ 中的每个数字最多只能出现一次。我们保证游戏一定有一个唯一解。

![](https://cdn.luogu.com.cn/upload/image_hosting/3dkcy4vy.png)

上图是一个数和游戏的例子示意图，坐标 $(1, 4)$ 处是一个灰色格子，它的 $A$ 中的数字为 $4$，这意味它下方的条目（即坐标 $(2, 4)$、$(3, 4)$ 处的白色格子）中的数字之和应该为 $4$；坐标 $(5, 1)$ 处是一个灰色格子，它的 $B$ 中的数字是 $16$，这表示它右方的条目（即坐标 $(5, 2)$、$(5, 3)$ 处的白色格子）中的数字之和应该为 $16$。

### 输入格式

第一行输入两个正整数 $M$、$N$ 分别用来表示棋盘的高度和宽度。

接下来 $M$ 行，每行输入 $N$ 个格子的信息。对于白色格子，只需要输入一个整数 $1$；对于灰色格子，首先输入一个整数 $2$，接下来再输入两个正整数分别表示灰色格子中 $A$ 中的数字和 $B$ 中的数字，如果是 $-1$ 则表示 $A$ 或 $B$ 中没有数字。其中每一行输入的所有的相邻整数之间均用空格隔开。

### 输出格式

输出 $M$ 行，每行包含 $N$ 个格子的信息，如果当前位置是一个灰色格子则用一个 `_ `符号来表示；如果是一个白色格子，则用一个 $1 \dots 9$ 之间的整数来表示将要填入当前白色格子内的数字。每一行中，相邻格子之间的输出用一个空格分隔。

### 输入 

```
7 7
2 -1 -1 2 -1 -1 2 -1 -1 2 4 -1 2 14 -1 2 19 -1 2 11 -1
2 -1 -1 2 -1 -1 2 21 24 1 1 1 1
2 -1 -1 2 26 18 1 1 1 1 1
2 -1 12 1 1 2 -1 -1 2 -1 3 1 1
2 -1 16 1 1 2 17 -1 2 11 8 1 1
2 -1 28 1 1 1 1 1 2 -1 -1
2 -1 14 1 1 1 1 2 -1 -1 2 -1 -1
```

### 输出 

```
_ _ _ _ _ _ _
_ _ _ 3 9 7 5
_ _ 6 1 5 4 2
_ 8 4 _ _ 2 1
_ 9 7 _ _ 5 3
_ 7 3 9 8 1 _
_ 2 1 8 3 _ _
```

### 说明/提示

#### 样例说明

![](https://cdn.luogu.com.cn/upload/image_hosting/khg8k4ql.png)

此局游戏的答案如上图所示。

#### 评测用例规模与约定

- 对于 $30\%$ 的测试用例，$3 \leq M, N \leq 5$。
- 对于 $60\%$ 的测试用例，$3 \leq M, N \leq 10$。
- 对于 $100\%$ 的测试用例，$3 \leq M, N \leq 15$，$1 \leq$ 灰色格子中的数字 $\leq 50$。


### 题解
正如数独那道题中描述的，可以把当前`pos`对应的坐标映射到 行 列 宫 三个集合里面进行剪枝。
所以在本题中，需要找到一种方法，将当前`pos`对应的坐标映射到条目集合`item`里面进行剪枝

由此可以确定辅助状态如下：
- `item[sum, cnt, used[]]`
- `sum` 代表当前条目中最多能填入的数字之和
- `cnt` 代表当前条目中剩余的格子数量
- `used[]` 代表当前条目中已经使用了哪些数字
- `pos2item[][]` 代表当前格子对应的条目id

限制条件：
- 在每次填入一个数字时：
  -  `sum >= 0`
  -  `cnt >= 0`
  -  `used[i] <= 1`
-  在填入条目的最后一个数字时：
   -   `sum == 0`  
   -   `cnt == 0`
   -   `used[i] <= 1`

这一步检验不用放到最后才进行，而是每次填入一个数字时就进行检验，如果不满足条件就剪掉这个分支

**现在解决如何映射的问题**
可以注意到，每一个格子只属于两个条目，所以我们只需要建立一个`pos2item`数组，用来存储当前空白格子对应的条目id就可以了

在进行这一步之前，还需要先对输入进行处理，统计出条目的数量，并且建立`items`数组来存储每一个条目的信息
具体就是遍历整个棋盘，

```cpp
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m; cin >> n >> m;
    auto board = vector(n, vector<int>(m, -1)); // -1代表不可填入数字的灰色格子
    auto sums = vector(n, vector<pair<int, int>>(m));
    int itemSize = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            int type; cin >> type;
            if (type == 2) {
                cin >> sums[i][j].first >> sums[i][j].second;
                if (sums[i][j].first != -1) itemSize ++;
                if (sums[i][j].second != -1) itemSize ++;
            } else {
                board[i][j] = 0; // 0 代表可填入数字的白色格子
            }
        }
    }

    // struct Item
    // {
    //     int sum;
    //     int cnt;
    //     vector<int> used;
    // };

    // using itemInfo = tuple<int, int, vector<int>>;
    // vector<itemInfo> items(itemSize);

    // //以上两种方式都能实现这种功能
    // vector<tuple<int, int, vector<int>>> items;
    using itemInfo = tuple<int, int, vector<int>>;
    vector<itemInfo> items;
    using itemIds = vector<int>;
    auto pos2item = vector(n, vector(m, itemIds())); //一个点可能映射到两个item上

    //映射就是直接映射（
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            // 并不会重复哦，因为大于0的只有可能是唯一的黑色的格子
            // 纵向的
            if (sums[i][j].first > 0) { 
                int cnt = 0;
                for (int k = i+ 1; k < n && board[k][j] == 0; k ++) {
                    pos2item[k][j].push_back(items.size());
                    cnt ++;
                }
                items.emplace_back(sums[i][j].first, cnt, vector<int>(10, 0));
            }
            // 横向的
            if (sums[i][j].second > 0) {
                int cnt = 0;
                for (int k = j + 1; k < m && board[i][k] == 0; k ++) {
                    pos2item[i][k].push_back(items.size());
                    cnt ++;
                }
                items.emplace_back(sums[i][j].second, cnt, vector<int>(10, 0));
            }
        }      
    }
    
    auto can = [&](int x, int y, int d) {
        for (auto itemId : pos2item[x][y]) {
            auto &[sum, cnt, used] = items[itemId]; //必须加引用
            if (sum < d) return false;
            if (used[d]) return false;
            if (cnt == 1 && sum != d) return false;
        }
        return true;
    };

    auto update = [&](int x, int y, int d) {
        board[x][y] = d;
        for (auto itemId : pos2item[x][y]) {
            auto &[sum, cnt, used] = items[itemId]; //必须加引用
            sum -= d;
            cnt --;
            used[d] = 1;
        }
    };

    auto rollback = [&](int x, int y, int d) {
        board[x][y] = 0;
        for (auto itemId : pos2item[x][y]) {
            auto &[sum, cnt, used] = items[itemId]; //必须加引用
            sum += d;
            cnt ++;
            used[d] = 0;
        }
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * m) return true;

        int x = pos / m, y = pos % m;
        if (board[x][y] == -1) return self(self, pos + 1); //空格直接跳过

        for (int d = 1; d <= 9; d ++) {
            if (can(x, y, d)) {
                update(x, y, d);
                if (self(self, pos + 1)) return true;
                rollback(x, y, d);
            }
        }
        return false;
    };

    traceback(traceback, 0);

    for(auto row : board) {
        for (auto cell : row) {
            if (cell == -1) cout << "_ ";
            else cout << cell << " ";
        }
        cout << "\n";
    }
}
```

进一步优化：
可以注意到，对于一定的`cnt`的值，`sum`的最大值是最大的几个未被使用的的数字的和，可以利用这个进一步剪枝
代码略

---

## 8.16 lq2227 点亮
!!! : 类 n皇后 & 01游戏

### 问题描述

小蓝最近迷上了一款名为《点亮》的谜题游戏, 游戏在一个 $n \times n$ 的格子棋盘上进行, 棋盘由黑色和白色两种格子组成, 玩家在白色格子上放置灯泡, 确保任意两个灯泡不会相互照射, 直到整个棋盘上的白色格子都被点亮（每个谜题均为唯一解）。灯泡只会往水平和垂直方向发射光线, 照亮整行和整列, 除非它的光线被黑色格子挡住。黑色格子上可能有从 0 到 4 的整数数字, 表示与其上下左右四个相邻的白色格子共有几个灯泡; 也可能没有数字, 这表示可以在上下左右四个相邻的白色格子处任意选择几个位置放置灯泡。游戏的目标是选择合适的位置放置灯泡, 使得整个棋盘上的白色格子被点亮。

例如, 有一个黑色格子处数字为 4 , 这表示它周围必须有 4 个灯泡, 需要在他的上、下、左、右处分别放置一个灯泡; 如果一个黑色格子处数字为 2 , 它的上下左右相邻格子只有 3 个格子是白色格子, 那么需要从这三个白色格子中选择两个来放置灯泡; 如果一个黑色格子没有标记数字, 且其上下左右相邻格子全是白色格子, 那么可以从这 4 个白色格子中任选出 0 至 4 个来放置灯泡。

题目保证给出的数据是合法的, 黑色格子周围一定有位置可以放下对应数量的灯泡。且保证所有谜题的解都是唯一的。

现在, 给出一个初始的棋盘局面, 请在上面放置好灯泡, 使得整个棋盘上的白色格子被点亮。

### 输入格式

输入的第一行包含一个整数 $n$, 表示棋盘的大小。

接下来 $n$ 行, 每行包含 $n$ 个字符, 表示给定的棋盘。字符 `.` 表示对应的格子为白色, 数字字符 `0`、`1`、`2`、`3`、`4` 表示一个有数字标识的黑色格子, 大写字母 `X` 表示没有数字标识的黑色格子。

### 输出格式

输出 $n$ 行, 每行包含 $n$ 个字符, 表示答案。大写字母 `O` 表示对应的格子包含灯泡, 其它字符的意义与输入相同。

### 样例输入
```cpp
5
.....
.2.4.
..4..
.2.X.
.....
```
### 样例输出
```cpp
...O.
.2O4O
.O4O.
.2OX.
O....
```

### 评测用例规模与约定

对于所有评测用例, $2 \leq n \leq 5$, 且棋盘上至少有 $15\%$ 的格子是黑色格子。

### 运行限制

最大运行时间：5s
最大运行内存: 512M

### 题解
大杂烩这一块

```cpp
vector<pair<int, int>> dir = {
    {1, 0}, {0, 1}, {0, -1}, {-1, 0}
}; //提前确定顺序，方便绑定剩余数字

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector<string> board(n);
    for (auto &line : board) cin >> line;
    auto cnt = vector(n, vector(n, 0));
    auto lighted = vector(n, vector(n, 0));
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            if (isdigit(board[i][j])) {
                cnt[i][j] = board[i][j] - '0';
            }
        }
    }

    auto check = [&]() {
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < n; j ++) {
                // 如果这个格子是空格且没有被点亮了，说明不合法
                if (board[i][j] == '.' && lighted[i][j] == 0) return false; 

                if (isdigit(board[i][j]) && cnt[i][j] != 0) return false; 
            }
        }
        return true;
    };

    auto inside = [&](int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < n;
    };

    auto can = [&](int x, int y, int put) {
        if (put) {
            for (auto [dx, dy] : dir) {
                int nx = x + dx, ny = y + dy;
                if (!inside(nx, ny)) continue;
                if (isdigit(board[nx][ny]) && cnt [nx][ny] == 0) return false; //如果这个格子是数字格子且它的计数已经为0了，说明不合法

                while (inside(nx, ny)) {
                    if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
                    if (board[nx][ny] == 'O') return false; // 所有灯泡不能互相攻击
                    nx += dx; ny += dy;
                }
            }
        } else {
            for (int d = 0; d < 4; d ++) {
                int nx = x + dir[d].first, ny = y + dir[d].second;
                if (!inside(nx, ny)) continue;
                //这里有点像扫雷那个 画个图自己看看就好
                if (isdigit(board[nx][ny]) && cnt [nx][ny] >= 4 - d) return false; 
            }
        }
        return true;
    };

    auto update = [&](int x, int y) {
        board[x][y] = 'O';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (isdigit(board[nx][ny])) cnt[nx][ny] --; //如果这个格子是数字格子，那么它周围的灯泡数量就要减1
        }
        lighted[x][y] ++; //点亮这个格子
        for (auto [dx, dy] : dir) { //点亮能点亮的格子
            int nx = x + dx, ny = y + dy;
            while (inside(nx, ny)) {
                if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
                lighted[nx][ny] ++; //点亮这个格子
                nx += dx; ny += dy;
            }
        }
    };

    auto rollback = [&](int x, int y) {
        board[x][y] = '.';
        for (auto [dx, dy] : dir) {
            int nx = x + dx, ny = y + dy;
            if (!inside(nx, ny)) continue;
            if (isdigit(board[nx][ny])) cnt[nx][ny] ++; 
        }
        lighted[x][y] --; 
        for (auto [dx, dy] : dir) { 
            int nx = x + dx, ny = y + dy;
            while (inside(nx, ny)) {
                if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
                lighted[nx][ny] --; 
                nx += dx; ny += dy;
            }
        }
    };

    auto traceback = [&](auto &self, int pos) {
        if (pos == n * n) return check();

        int x = pos / n, y = pos % n;
        if (board[x][y] != '.') return self(self, pos + 1);
        
        if (can(x, y, 1)) {
            update(x, y);
            if (self(self, pos + 1)) return true;
            rollback(x, y);
        }

        if (can(x, y, 0)) {
            if (self(self, pos + 1)) return true;
        }
        return false;
    };

    traceback(traceback, 0);
    for (auto &line : board) cout << line << "\n";
}
```

可以看看老师是怎么debug的 主要就是cpp的那一堆脚本快速输出各种信息

--- 

## 8.17 P11047 [蓝桥杯 2024 省 Java B] LITS 游戏 lq19727

### 题目背景

备注：原题（Java）时间限制 3.0s，空间限制 512 MB。

### 题目描述

俄罗斯方块是一款风靡全球的游戏，在游戏中有多种方格图案，我们只关注这四个经典的方块图案：**LITS**，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/run4pn8d.png)

LITS 这四种方块都是由四个相同大小的小方块组成的。 
现在给出一副大小为 $N \times N$ 的格子图，每个格子上都有一个数字 $0/1$，如果格子处的数字为 $1$ 说明这个格子上有一个小方块，数字为 $0$ 则没有。 
你需要判断从这个格子图上是否可以找出 LITS 四个方块图案（每个方块图案之间都是独立的，不存在不同的图案公用同一个小方块的情况）。其中 LITS 方块的形状旋转任意个 $90^\circ$ 都是合法的，但不允许翻转。

### 输入格式

第一行一个整数 $T$，表示有 $T$ 组数据。 
每组数据的第一行包含一个整数 $N$，表示格子图大小。 
接下来输入 $N$ 行，每行 $N$ 个值为 $0/1$ 的整数，表示格子布局。

### 输出格式

对于每组数据，输出一行包含一个字符串。如果此组数据满足题意则输出 `Yes`，否则输出 `No`。


### 输入 

```
2
5
1 1 1 1 1
1 0 1 1 0
1 0 0 0 1
1 0 1 0 1
1 1 1 1 1
5
1 0 0 1 1
1 1 1 1 1
1 1 1 1 0
1 1 1 0 1
0 1 1 1 1
```

### 输出 

```
No
Yes
```

### 说明/提示

【样例解释】

对于样例中的第二个格子图，一种 LITS 的摆放方案如下：

```txt
1 0 0 1 1
L S T T T
L S S T 0
L L S 0 1
0 I I I I
```

【数据范围】

- 对于 $30 \%$ 的评测用例：$1 \leq N \leq 5$。
- 对于 $60 \%$ 的评测用例：$1 \leq N \leq 10$。
- 对于 $100 \%$ 的评测用例：$1 \leq T \leq 10$，$1 \leq N \leq 50$。

【特别备注】

由于讨论情况较多，本题部分其他平台的题解可能存在错误。

### 题解
思路还是比较简单的，由于每个字母只需要放一次，所以可以用一个`used`数组来记录每个字母是否被使用过了
在每个位置，如果可以放置，就枚举每个未使用字母的摆放方式，进行判断或剪枝

那么本题的难点在于处理每个字母的摆放方式，如何判断一个字母的摆放方式是否合法，以及如何枚举每个字母的摆放方式
以及如何处理快速用位运算判断某个图形是否被使用过

```cpp
int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<set<vector<string>>> patterns = { // 字母的初始版本 L S T I
        {
            {
                "111",
                "100",
            },
        },
        {
            {
                "1111",
            }
        },
        {
            {
                "111",
                "010"
            }
        },
        {
            {
                "011",
                "110"
            }
        }

    };
    //  旋转函数
    for (auto &pattern : patterns) { //生成不同的pattern的旋转版本
        auto type = *pattern.begin();
        for (int _ = 0; _ < 4; _ ++) {
            int n = type.size(), m  = type[0].size(); 
            //n 为原始的行数， m为原始的列数
            auto newType = vector(m, string(n, '0'));
            //旋转的过程就是把原来的行数变成列数，原来的列数变成行数
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < m; j ++) {
                    newType[j][n - i - 1] = type[i][j]; // 逆时针旋转90度 
                    // j 互相交换位置了直接换很好理解
                    // i 交换后 ，轴的方向反向了， 所以是 n - i - 1
                }
            }
            type = newType;
            pattern.insert(type);
        }
    }
    // 想看看旋转后长啥样?
    // for (auto &pattern : patterns) {
    //     cout << "pattern:\n";
    //     for (auto &line : *pattern.begin()) cout << line << "\n";
    //     cout << "rotations:\n";
    //     for (auto &type : pattern) {
    //         for (auto &line : type) cout << line << "\n";
    //         cout << "\n";
    //     }
    // }


    int T; cin >> T;
    while (T --) {
        int n; cin >> n;
        auto board = vector(n, vector(n, 0));
        for (auto &row : board) {
            for (auto &x : row) cin >> x;
        }

        //  注意加引用 ！！！
        // const 是因为 auto 获取到的是一个临时变量，不能修改它，所以加上const来保证它不会被修改
        // 即是说获得的 type本身就是 const修饰的，所以在形参列表中必须要加上const来匹配这个类型，否则编译器会报错

        auto can = [&](int x, int y, const vector<string> &type) {
            int xl = type.size(), yl = type[0].size();
            if (x + xl > n || y + yl > n) return false; //如果这个pattern放下去会超出board的范围了，说明不合法
            for (int i = 0; i < xl; i ++) {
                for (int j = 0; j < yl; j ++) {
                    if (type[i][j] == '1' && board[i + x][j + y] == 0) return false; //如果这个格子需要放一个棋子但是board上这个格子没有了，说明不合法
                }
            }
            return true;
        };

        auto update = [&](int x, int y, const vector<string> &type) {
            int xl = type.size(), yl = type[0].size();
            for (int i = 0; i < xl; i ++) {
                for (int j = 0; j < yl; j ++) {
                    if (type[i][j] == '1' ) board[i + x][j + y] = 0; //如果这个格子需要放一个棋子，那么board上这个格子就要被占用了，所以标记为0
                }
            }
        };

        auto rollback = [&](int x, int y, const vector<string> &type) {
            int xl = type.size(), yl = type[0].size();
            for (int i = 0; i < xl; i ++) {
                for (int j = 0; j < yl; j ++) {
                    if (type[i][j] == '1' ) board[i + x][j + y] = 1; //如果这个格子需要放一个棋子，那么board上这个格子就要被占用了，所以标记为0
                }
            }
        };
        // used 数组用二进制存，四个位每一位都有的话就是15咯
        auto traceback = [&](auto &self, int pos, int used) {
            if (used == 15) return true; 
            if (pos == n * n) return false;

            int x = pos / n, y = pos % n;
            for (int i = 0; i < 4; i ++) {
                if (used & (1 << i)) continue; //如果这个pattern已经用过了，就跳过

                for (auto &type : patterns[i]) {
                    if (can(x, y, type)) {
                        update(x, y, type);
                        if (self(self, pos + 1, used | (1 << i))) return true; //递归进入下一层，记得更新used
                        rollback(x, y, type);
                    }
                }
            }
            // 可以不摆哦，所以这样写 ！！！ 
            return self(self, pos + 1, used); //不放这个格子，直接进入下一层
        };

        if (traceback(traceback, 0, 0)) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}
```

同样，能过蓝桥杯的数据过不了洛谷上的数据，原因在于当 `N == 50` 时，需要判断两千余个格子的情况，此时若答案判定为 `No`，则需要遍历完整个搜索树才能得出结论

好消息是只靠剪枝也可以做到这个case，具体见下

---

## 8.18  case 加强版 P11047 [蓝桥杯 2024 省 Java B] LITS 游戏
题目描述见上题，直接进入思路部分

### 题解
主要的思路和 像素放置 中的优化思想很像：
在 `can` 函数中，每一次都要进行以及遍历和判断。这实际上会造成较大的重复计算。
这样的话，我们可以预先生成一个数组，用于计算每个 `pattern` 在某个方向上可以摆放的位置。
因为每一个 `pattern` 只需要用到一次，所以需要四层单独的遍历，当所有`pattern` 都使用过之后，就不需要再进行判断了，直接返回 `true` 就好了

需要注意的是，因为是4层循环，且各个循环的循环次数的数量级相差可能会很大，所以还需要按照可能的拜访情况的数量从小到大排序，这样才能保证在最外层循环的情况下，内层循环的数量级不会太大，从而达到剪枝的效果

```cpp
int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<set<vector<string>>> patterns = { // 字母的初始版本 L S T I
        {
            {
                "111",
                "100",
            },
        },
        {
            {
                "1111",
            }
        },
        {
            {
                "111",
                "010"
            }
        },
        {
            {
                "011",
                "110"
            }
        }

    };
    //  旋转函数
    for (auto &pattern : patterns) { //生成不同的pattern的旋转版本
        auto type = *pattern.begin();
        for (int _ = 0; _ < 4; _ ++) {
            int n = type.size(), m  = type[0].size(); 
            //n 为原始的行数， m为原始的列数
            auto newType = vector(m, string(n, '0'));
            //旋转的过程就是把原来的行数变成列数，原来的列数变成行数
            for (int i = 0; i < n; i ++) {
                for (int j = 0; j < m; j ++) {
                    newType[j][n - i - 1] = type[i][j]; // 逆时针旋转90度 
                    // j 互相交换位置了直接换很好理解
                    // i 交换后 ，轴的方向反向了， 所以是 n - i - 1
                }
            }
            type = newType;
            pattern.insert(type);
        }
    }
    // 想看看旋转后长啥样?
    // for (auto &pattern : patterns) {
    //     cout << "pattern:\n";
    //     for (auto &line : *pattern.begin()) cout << line << "\n";
    //     cout << "rotations:\n";
    //     for (auto &type : pattern) {
    //         for (auto &line : type) cout << line << "\n";
    //         cout << "\n";
    //     }
    // }


    int T; cin >> T;
    while (T --) {
        int n; cin >> n;
        auto board = vector(n, vector(n, 0));
        for (auto &row : board) {
            for (auto &x : row) cin >> x;
        }

        auto candidats = vector(4, vector<vector<int>>());
        for (int k = 0; k < 4; k++) {
            auto &pattern = patterns[k];
            for (auto & type : pattern) {
                int xl = type.size(), yl = type[0].size();
                for (int x = 0; x + xl <= n; x ++) {
                    for (int y = 0; y  + yl <= n; y ++) {
                        if ([&] () {
                            for (int i = 0; i < xl; i ++) {
                                for (int j = 0; j < yl; j ++) {
                                    if (type[i][j] == '1' && board[x + i][y + j] == 0) return false;
                                }
                            }
                            return true;
                        }()) {
                            vector<int> candidate;
                            for (int i = 0; i < xl; i ++) {
                                for (int j = 0; j < yl ;j ++) {
                                    if (type[i][j] == '1') {
                                        candidate.push_back((x + i) * n + y + j);
                                    }
                                }
                            }
                            candidats[k].push_back(candidate);
                        }
                    }
                }
            }
        }
        // 排序不要直接翻转vector！！！
        vector<int> order {0, 1, 2, 3};
        sort(order.begin(), order.end(), [&](int a, int b) {
            return candidats[a].size() < candidats[b].size();
        });

        vector<int> used(n * n);

        auto can = [&](const vector<int> &candidate) {
            for (auto &pos : candidate) {
                if (used[pos]) return false;
            }
            return true;
        };

        auto update = [&](const vector<int> &candidate) {
            for (auto &pos : candidate) {
                used[pos] = 1;
            }
        };

        auto rollback = [&](const vector<int> &candidate) {
            for (auto &pos : candidate) {
                used[pos] = 0;
            }
        };

        auto traceback = [&](auto &self, int step) -> bool {
            if (step == 4) return true;

            for (auto &candidate : candidats[order[step]]) {
                if (can (candidate)) {
                    update(candidate);
                    if (self(self, step + 1)) return true;
                    rollback(candidate);
                }
            }
            return false;
        };

        cout << (traceback(traceback, 0) ? "Yes\n" : "No\n");
    }
}
```

本章完结