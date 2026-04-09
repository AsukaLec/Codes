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

# <center>第九章 搜索</center>

## Lead In

### 图的基本概念
**点和边构成的图形**
**图论**即是对图形的各种性质进行研究的理论

<blockquote class="grey-quote">

$ G = (V, E) $
$G$ 是一个图，$V$ 是图中的点的集合，$E$ 是图中的边的集合
</blockquote>

#### 基础术语和形态
- 无向边：$(u, v)$ 代表点 $u$ 和点 $v$ 之间的无向边
- 有向边：$<u, v>$ 代表点 $u$ 和点
- 边的权值：$(u, v, c)$ 代表边 $(u, v)$ 的权值
- 点的权值：$(u, c)$ 代表点 $u$ 的权值
- 稀疏图：边的数量远小于点的数量的平方
- 稠密图：边的数量接近点的数量的平方
- 完全图：每对点之间都有边的图，边数为 $\frac{n(n-1)}{2}$
- 树：一个无环连通图，边数为$n-1$
    <blockquote class="grey-quote">
    树是一种特殊的图，有很多性质，具体见数据结构
    </blockquote>

#### 图的存储
<blockquote class="orange-quote">
存储的目的，是为了知道与另一个点相邻的邻居有哪些
这样才能方便探究一个点和另一个点之间的关系
</blockquote>

**按边单独存储**
不常用，一般题目这样给
``` cpp
1 1 2
2 1 3
3 1 5
...
n x y
```

**邻接矩阵**
``` cpp
0 1 2 3 4 5
1 1 0 1 0 1
2 0 1 0 1 0
3 0 0 1 0 1
4 0 1 0 1 0
5 1 0 1 0 1 
```


``` cpp 
//建图
auto matrix = vector(n, vector(n, 0));
for (int i = 0; i < m, i++) {
    int u, v;
    cin >> u >> v;
    matrix[u][v] = matrix[v][u] = 1; // 无向图
}

//遍历邻居
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (matrix[i][j] == 1) {
            // i 和 j 是邻居
        }
    }
}
```

<blockquote class="red-quote">

如果图很大，节点个数多，内存开不下哦
</blockquote>

**邻接表**

**对于稀疏图**只记录每个点的邻居，节省空间
**如果是稠密图，还是邻接矩阵更好，利用率更高**

``` cpp
1 1:[2, 3, 5]
2 2:[1, 4]
3 3:[1, 5]
...
n n:[x, y, z]
```

``` cpp
auto graph = vector(n, vector<int>());
for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u); // 无向图
}
//遍历邻居
for (int i = 0; i < n; i++) {
    for (int neighbor : graph[i]) {
        // i 和 neighbor 是邻居
    }
}
```

**前向星**
<blockquote class="grey-quote">
过时的存储方式

自己维护一个变长数组而不使用vector
本质是一个链表，但是存储时提前申请的
</blockquote>

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\搜索0.1.png " width="500"/>
  </div>
</div>

#### 图的遍历
##### Depth First Search 深度优先搜索
一条路走到黑，走的时候标记这条路走过来，如不能走，就回到上次的路径点，继续走下一条路
<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\搜索0.2.png " width="500"/>
  </div>
</div>

```cpp
auto dfs = [&](auto &dfs, int u) {
    for (auto v :graph[u]) {
        if (visited[v]) continue; // 已访问过，跳过
        visited[v] = true; // 标记为已访问
        dfs(dfs, v); // 继续访问邻居
        // 不用回退，因为 visited 已经标记了
        // 回退的话就变成回溯了
    }
}
visited[0] = true; // 从点0开始访问
dfs(dfs, 1);
```
```cpp
//栈的写法
stack<pairint, int> st;
st.emplace(1, 0); // 从点1开始访问，父节点为0
visited[1] = true; // 标记为已访问
while (!st.empty()) {
    auto &[u, id] = st.top();
    if (id < graph[u].size()) {
        int v = graph[u][id++]; // 获取下一个邻居
        if (!visited[v]) {
            visited[v] = true; // 标记为已访问
            st.emplace(v, 0); // 将邻居入栈，父节点为u
        }
    } else {
        st.pop(); // 没有更多邻居，回退
    }
}
```

##### Breadth First Search 广度优先搜索
一层一层地访问，先访问完当前层的所有节点，再访问下一层的节点

**具体实现的时候，这个看起来像层次序遍历，主要就是维护一个队列，每次访问队列的头结点，并把其邻居加入队列**

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\搜索0.3.png " width="500"/>
  </div>
</div>


```cpp
auto bfs = [&](int start) {
    queue<int> q;
    q.push(start); // 从点start开始访问
    visited[start] = true; // 标记为已访问
    while (!q.empty()) {
        int u = q.front();
        q.pop(); // 访问队列头结点
        for (auto v : graph[u]) { // 遍历邻居
            if (visited[v]) continue; // 已访问过，跳过
            visited[v] = true; // 标记为已访问
            q.push(v); // 将邻居入队

        }
    }
}
```
#### 图和状态
<blockquote class="blue-quote">

**状态是点，状态转移是边**
</blockquote>

---

### 搜索
#### 定义
<blockquote class="green-quote">
在多项式复杂度个数的状态中，从一个状态，经过状态转移

- 最少转移代价，到目标状态
- 找到所有可以转移的状态
</blockquote>

<blockquote class="red-quote">
何为多项式复杂度？

多项式 $f(x) = ax + bx^2 + cx^3 + ...$
非多项式(NP)复杂度 $O(2^n)$ $O(n!)$ 
</blockquote>

回溯的题基本上都是非多项式复杂度，即基本都是NP问题，但是可以通过剪枝来优化，减少搜索空间
但是搜索没有剪枝这一步，如果状态数量很多，那就炸了

#### 例一 leetcode 1926 迷宫中离入口最近的出口
<blockquote class="yellow-quote">
给你一个地图，以及起始点，每步可以上下左右走一格，找到离七点最近的出口
如果格子是"+"，代表填，不能走
出口的定义是：在地图的边界上，且不是起点

<div style="display:flex; gap:2em; justify-content:center;">
  <div style="text-align:center;">
    <img src="photos\搜索0.4.jpg" width="300"/>
  </div>
</div>
</blockquote>

- 状态：人物坐标 $(x, y)$
- 总状态数：$O(mn)$ 注：如果结果非常大，那么代表搜索是失效的
- 转移：四个方向移动，切不越界
> 如何计算最近？
> bfs天然带有会的最短路的能力，因为是从初始状态向四周扩展，所以第一个扩展到的出口就是答案

**将步数进和状态一起记录**
```cpp
class solution {
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int nearestExit (vector<vector<char>> &maze, vector<int> & entrance) {
        int n = maze.size(), m = maze[0].size();
        auto visited = vector(n, vector(m, 0));
        int sx = entrance[0], sy = entrance[1];
        visited[sx][sy] = 1;
        queue<tuple<int, int, int>> que;
        que.emplace(sx, sy, 0); //起点横坐标，起点纵坐标，步数
        while (!que.empty()) {
            auto [x, y, step] = que.front();
            que.pop();
            if (x != sx || y != sy) {
                if (x == 0 || x == n - 1 || y == 0 || y == m - 1) return step;
            }

            for (auto [dx, dy]: dir) {
                int nx = x + dx, ny = y + dy;
                // 以下都不算剪枝哦，因为没有状态回退
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue; // 越界
                if (maze[nx][ny] == "+" ) continue; //有墙
                if (visited[nx][ny]) continue; // 已访问过
                visited[nx][ny] = true;
                que.emplace(nx, ny, step + 1);
            }
        }
        return -1; // 没有出口
    }
};
```

**Visited数组记录步数**
类似二维上bfs吧，体会一下记录的方法

```cpp
class Solution {
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size(), m = maze[0].size();
        auto min_dist = vector(n, vector(m, INT_MAX)); //起点到这个点的最短路径
        int sx = entrance[0], sy = entrance[1];
        min_dist[sx][sy] = 0; //初始步数为0
        queue<pair<int, int>> que;
        que.emplace(sx, sy);
        while (!que.empty()) {
            auto [x, y] = que.front();
            que.pop();
            int step = min_dist[x][y]; // 
            if (x != sx || y != sy) {
                if (x == 0 || x == n - 1 || y == 0 || y == m - 1) return step;
            }
            for (auto [dx, dy]: dir) {
                int nx = x + dx, ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                if (maze[nx][ny] == '+') continue;
                if (min_dist[nx][ny] <= step + 1) continue; //点之前被走过了
                min_dist[nx][ny] = step + 1; // 下一层
                que.emplace(nx, ny);
            }
        }
        return -1;
    }
};
```

**一层层遍历**
```cpp
class Solution {
    vector<pair<int, int>> dir = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int n = maze.size(), m = maze[0].size();
        auto visited = vector(n, vector(m, 0));
        int sx = entrance[0], sy = entrance[1];
        visited[sx][sy] = 1;
        queue<pair<int, int>> que;
        que.emplace(sx, sy);
        int step = 0;
        while (!que.empty()) {
            int cnt = que.size();
            while (cnt--) {
                auto [x, y] = que.front();
                que.pop();
                if (x != sx || y != sy) {
                    if (x == 0 || x == n - 1 || y == 0 || y == m - 1) return step;
                }
                for (auto [dx, dy]: dir) {
                    int nx = x + dx, ny = y + dy;
                    if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
                    if (maze[nx][ny] == '+') continue;
                    if (visited[nx][ny]) continue;
                    visited[nx][ny] = true;
                    que.emplace(nx, ny);
                }
            }
            step++;
        }
        return -1;
    }
};
```