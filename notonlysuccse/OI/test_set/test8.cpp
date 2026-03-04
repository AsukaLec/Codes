#include <bits/stdc++.h>
#include <format>
using namespace std;

// 81. 组合总和
// class Solution {
// public:
//     vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
//         vector<vector<int>> ans;
//         vector<int> comb;
//         auto traceback = [&](auto &self, int lower, int sum) {
//             if (sum == target) {
//                 ans.push_back(comb);
//                 return;
//             }

//             for (int i = lower; i < candidates.size(); i++) {
//                 if (sum + candidates[i] > target) continue;
//                 comb.push_back(candidates[i]);
//                 self(self, i, sum + candidates[i]);
//                 comb.pop_back();
//             }
//         };
//         traceback(traceback, 0, 0);
//         return ans;
//     }
// };

// 82.组合总和II
// class Solution {
// public:
//     vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
//         sort(candidates.begin(), candidates.end()); //
//         vector<vector<int>> ans;
//         vector<int> comb;
//         auto traceback = [&](auto &self, int lower, int sum) {
//             if (sum == target) {
//                 ans.push_back(comb);
//                 return;
//             }

//             int last = 0; //

//             for (int i = lower; i < candidates.size(); i++) {
//                 if (sum + candidates[i] > target) continue;

//                 if (last == candidates[i]) continue; //
//                 last = candidates[i]; //


//                 comb.push_back(candidates[i]);
//                 self(self, i + 1, sum + candidates[i]); //
//                 comb.pop_back();
//             }
//         };
//         traceback(traceback, 0, 0);
//         return ans;
//     }
// };

// 17. 电话号码的字母组合
// class Solution {
// public:
//     vector<string> letterCombinations(string digits) {
//         vector<string> phone = {
//             "",
//             "",
//             "abc",
//             "def",
//             "ghi",
//             "jkl",
//             "mno",
//             "pqrs",
//             "tuv",
//             "wxyz"
//         };
//         vector<string> ans;
//         string comb;
//         auto traceback = [&](auto &self) {
//             if (comb.size() == digits.size()) {
//                 if (comb.size() != 0) ans.push_back(comb);
//                 return;
//             }

//             int d = digits[comb.size()] - '0';
//             for (char c : phone[d]) {
//                 comb += c;
//                 self(self);
//                 comb.pop_back();
//             }
//         };
//         traceback(traceback);
//         return ans;
//     }
// };

// 87. 复原IP地址
// class Solution {
// public:
//     vector<string> restoreIpAddresses(string s) {
//         vector<string> ans;
//         vector<int> ip;
//         auto traceback = [&](auto &self, size_t pos) {
//             if (pos == s.size()) { 
//                 if (ip.size() == 4) { // 用int快速判断，最后一起放到string里面
//                     ans.push_back("" + to_string(ip[0]) + "." + to_string(ip[1]) + "." + to_string(ip[2]) + "." + to_string(ip[3]));
//                 }
//                 return;
//             }

//             //单独成一组
//             if (ip.size() < 4) {
//                 ip.push_back(s[pos] - '0');
//                 self(self, pos + 1);
//                 ip.pop_back();
//             }
//             //和前一个数字成一组
//             if (ip.size() && ip.back() != 0) {
//                 int next = ip.back() * 10 + s[pos] - '0';
//                 if (next <= 255) {
//                     ip.back() = next;
//                     self(self, pos + 1);
//                     ip.back() /= 10;
//                 }
//             }
//         };
//         traceback(traceback, 0);
//         return ans;
//     }
// };

// int main() {
//     Solution sol;
//     string s = "111111111111";
//     auto ans = sol.restoreIpAddresses(s);
//     for (auto &s : ans) {
//         cout << s << endl;
//     }
// }


// 87. 解数独
// class Solution {
// public:
//     void solveSudoku(vector<vector<char>>& board) {
//         int rows[9][9] = {};
//         int cols[9][9] = {};
//         int grids[3][3][9] = {};
        
//         for (int i = 0; i < 9; i ++) {
//             for (int j = 0; j < 9; j ++) {
//                 if (board[i][j] == '.') continue;
//                 int d = board[i][j] - '1';
//                 rows[i][d] = 1;
//                 cols[j][d] = 1;
//                 grids[i / 3][j / 3][d] = 1;
//             }
//         }

//         auto traceback = [&](auto &self, int pos) -> bool { // 一维记录 pos
//             if (pos == 81) return true;
//             int x = pos / 9,  y = pos % 9;

//             if (board[x][y] != '.') return self(self, pos + 1);

//             for (int d = 0; d < 9; d ++) {
//                 if (rows[x][d] || cols[y][d] || grids[x / 3][y / 3][d]) continue;

//                 board[x][y] = d + '1';
//                 rows[x][d] = 1;
//                 cols[y][d] = 1;
//                 grids[x / 3][y / 3][d] = 1;

//                 if (self(self, pos + 1)) return true;

//                 board[x][y] = '.';
//                 rows[x][d] = 0;
//                 cols[y][d] = 0;
//                 grids[x / 3][y / 3][d] = 0;                
//             }
//             return false;
//         };
//         traceback(traceback, 0);
//     }
// };


// 51 . N 皇后
// class Solution {
// public:
//     vector<vector<string>> solveNQueens(int n) {
//         vector<vector<string>> ans;
//         vector<string> board(n, string(n, '.'));
//         vector<int> col(n, 0), dg(2 * n - 1, 0), bdg(2 * n - 1, 0);

//         auto traceback = [&](auto &self, int row) {
//             if (row == n) {
//                 ans.push_back(board);
//                 return;
//             }

//             for (int i = 0; i < n; i ++) {
//                 //判定是否合法，注意反斜线的映射关系
//                 if (col[i] || dg[row + i] || bdg[row - i + n - 1]) continue;
//                 board[row][i] = 'Q';
//                 col[i] = dg[row + i] = bdg[row - i + n - 1] = 1;
//                 self(self, row + 1);
//                 board[row][i] = '.';
//                 col[i] = dg[row + i] = bdg[row - i + n - 1] = 0;
//             }
//         };
//         traceback(traceback, 0);
//         return ans;
//     }
// };

// 679 . 24 点游戏
// class Solution {
// public:
//     bool judgePoint24(vector<int>& cards) {
//         vector<double> nums(4);
//         for (int i = 0; i < 4; i ++) nums[i] = cards[i];
//         vector<int> used(4, 0);

//         auto calc = [&](double a, double b, char op) {
//             if (op == '+') return a + b;
//             if (op == '-') return a - b;
//             if (op == '*') return a * b;
//             return a / b;
//         };


//         auto traceback = [&](auto &self) {
//             if (nums.size() == 7) {
//                 return abs(24 - nums.back()) < 1e-6;
//             }

//             for (int i = 0; i < nums.size(); i ++) {
//                 if (used[i]) continue;
//                 for (int j = 0; j < nums.size(); j ++) {
//                     if (used[j] || j == i)  continue;

//                     used[i] = used[j] = 1;

//                     for (char op : "+-*/") {
//                         nums.push_back(calc(nums[i], nums[j], op));
//                         used.push_back(0);

//                         if (self(self)) return true;

//                         nums.pop_back();
//                         used.pop_back();
//                     }
//                     used[i] = used[j] = 0;
//                 }
//             }
//             return false;
//         };
//         return traceback(traceback);
//     }
// };


//8.10

//method 1
// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int T; cin >> T;
//     while (T --) {
//         int n; cin >> n;
//         vector<tuple<int, int, int>> planes(n);
        
//         for (auto &[t, d, l] : planes) cin >> t >> d >> l;
        
//         auto can_land = [&]() {
//             int last = 0;
//             for (auto &[t, d, l] : planes) {
//                 if (t + d < last) return false;
//                 last = max(last, t) + l;
//             }
//             return true;
//         };

//         auto check = [&]() {
//             sort(planes.begin(), planes.end());
//             do {
//                 if (can_land()) return true;
//             } while (next_permutation(planes.begin(), planes.end()));
//             return false;
//         };
//         cout << (check() ? "YES" : "NO") << "\n";
//     }
// }

//method 2
// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int T; cin >> T;
//     while (T --) {
//         int n; cin >> n;
//         vector<tuple<int, int, int>> planes(n);
        
//         for (auto &[t, d, l] : planes) cin >> t >> d >> l;
        
//         vector<int> used(n);

//         auto traceback =[&](auto &self, int cnt, int last) {
//             if (cnt == n) return true;

//             for (int i = 0; i < n; i ++) {
//                 if (used[i]) continue;
//                 auto [t, d, l] = planes[i];
//                 if (t + d < last) continue; // 剪枝
//                 used[i] = true;
//                 if (self(self, cnt + 1, max(last, t) + l)) return true; 
//                 used[i] = false;
//             }
//             return false;
//         };

//         cout << (traceback(traceback, 0, 0) ? "YES" : "NO") << "\n";
//     }
// }

// vector<pair<int, int>> dir = {
//     {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}
// };

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n, k; cin >> n >> k;
//     vector(n, vector<int>(n));

//     auto maze = vector(n * 2, vector(n * 2, 0));
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < n; j ++) {
//             cin >> maze[i * 2][j * 2];
//         }
//     }
//     auto vis = vector(n * 2, vector(n * 2, 0));
//     string ans ;

//     auto inside = [&](int x, int y) { // 迷宫问题基本都需要这个，判断是否还在迷宫中
//         return x >= 0 && x < n * 2 && y >= 0 && y < n * 2;
//     };

//     auto traceback = [&](auto &self, int x, int y) {
//         if (x == n * 2 - 2 && y == n * 2 - 2) {
//             if ((int)ans.size() == n * n - 1) return true;
//             return false;
//         }

//         for (int d = 0; d < 8; d ++) {
//             auto [dx, dy] = dir[d];
//             int nx = x + dx, ny = y + dy; //next_x, next_y 但是要走两步
//             //同时 nx和 ny 也是必要的，因为要判断是否交叉
//             int nnx = nx + dx, nny = ny + dy; //next_next_x, next_next_y
            
//             if (!inside(nnx, nny)) continue; //只需要nnx和nny判断是否越界，因为nx和ny在两点之间，越界了就不合法
//             if (vis[nx][ny] || vis[nnx][nny]) continue; //判断是否交叉，nx和ny在两点之间，nnx和nny在要去的点上
//             if (maze[nnx][nny] != (maze[x][y] + 1) % k) continue; //判断数字是否满足要求
//             vis[nx][ny] = vis[nnx][nny] = true;
//             ans += d + '0'; //字符串

//             if (self(self, nnx, nny)) return true;

//             //还原
//             ans.pop_back();
//             vis[nx][ny] = vis[nnx][nny] = false;
//         }
//         return false;
//     };

//     vis[0][0] = true; //起点
//     if (traceback(traceback, 0, 0) && maze[0][0] == 0) {
//         cout << ans << "\n";
//     } else {
//         cout << -1 << "\n";
//     }
// }


//8.12
// vector<pair<int, int>> dir = {
//     {-1, 0}, {0, 1}, {1, 0}, {0, -1}
// };

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n; cin >> n;
//     vector<int> col(n), row(n);
//      int total = 0; //用 accumulate 替代 
//     //accumulate(col.begin(), col.end(), 0)
//     for (int i = 0; i < n; i ++) {cin >> col[i]; total += col[i];}
//     for (int i = 0; i < n; i ++) {cin >> row[i];}
//     vector<int>ans;
//     auto maze = vector(n, vector<int>(n, 0));

//     auto inside = [&](int x, int y) {
//         return x >= 0 && x < n && y >= 0 && y < n;
//     };

//     auto traceback = [&](auto &self, int x, int y) {
//         if (x == n - 1 && y == n - 1) {
//             if ((int)ans.size() == total && ans.back() == n * n - 1) return true;
//             return false;
//         } // check

//         // if (x == n - 1 && y == n - 1) {
//         //     if (accumulate(row.begin(), row.end(), 0) == 0 && 
//         //         accumulate(col.begin(), col.end(), 0) == 0) return true;
//         //     return false;
//         // }

//         for (int d = 0; d < 4; d ++) {
//             auto [dx, dy] = dir[d];
//             int nx = x + dx, ny = y + dy;

//             //限制条件
//             if (!inside(nx, ny)) continue;
//             if (maze[nx][ny]) continue;
//             if (!row[nx] || !col[ny]) continue; // check

//             //状态转移
//             maze[nx][ny] = 1;
//             row[nx] --; col[ny] --; 
//             ans.push_back(nx * n + ny); // 记录路径

//             //进入下一层
//             if (self(self, nx, ny)) return true;

//             //回溯
//             ans.pop_back();
//             maze[nx][ny] = 0;
//             row[nx] ++; col[ny] ++; 
//         }
//         return false;
//     };

//     //起点特判
//     maze[0][0] = 1;
//     col[0] --; row[0] --;
//     ans.push_back(0); //注意这一步是必须的，不然在trace back里面pushback的始终会少一个

//     if (traceback(traceback, 0, 0)) {
//         for (int i : ans) cout << i << " " ;
//     } else {
//         cout << -1 << "\n";
//     }
// }

// vector<pair<int, int>> dir = {
//     {-1, 0}, {0, 1}, {1, 0}, {0, -1}
// };

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n; cin >> n;
//     int target = n * n - 1;
//     vector<int> col(n), row(n);
//      int total = 0; //用 accumulate 替代 
//     //accumulate(col.begin(), col.end(), 0)
//     for (int i = 0; i < n; i ++) {cin >> col[i]; total += col[i];}
//     for (int i = 0; i < n; i ++) {cin >> row[i];}
//     vector<int>ans;
//     auto maze = vector(n, vector<int>(n, 0));

//     auto inside = [&](int x, int y) {
//         return x >= 0 && x < n && y >= 0 && y < n;
//     };

//     auto traceback = [&](auto &self, int x, int y) {
//         if (x == n - 1 && y == n - 1) {
//             if ((int)ans.size() == total && ans.back() == target) return true;
//             return false;
//         } // check

//         // if (x == n - 1 && y == n - 1) {
//         //     if (accumulate(row.begin(), row.end(), 0) == 0 && 
//         //         accumulate(col.begin(), col.end(), 0) == 0) return true;
//         //     return false;
//         // }

//         for (int d = 0; d < 4; d ++) {
//             auto [dx, dy] = dir[d];
//             int nx = x + dx, ny = y + dy;

//             //限制条件
//             if (!inside(nx, ny)) continue;
//             if (maze[nx][ny]) continue;
//             if (!row[nx] || !col[ny]) continue; // check
//             // 附加剪枝条件
//             if (row[nx] == 1 && accumulate(row.begin(), row.begin() + nx, 0) != 0) continue;
//             if (col[ny] == 1 && accumulate(col.begin(), col.begin() + ny, 0) != 0) continue;

//             //状态转移
//             maze[nx][ny] = 1;
//             row[nx] --; col[ny] --; 
//             ans.push_back(nx * n + ny); // 记录路径

//             //进入下一层
//             if (self(self, nx, ny)) return true;

//             //回溯
//             ans.pop_back();
//             maze[nx][ny] = 0;
//             row[nx] ++; col[ny] ++; 
//         }
//         return false;
//     };

//     //起点特判
//     maze[0][0] = 1;
//     col[0] --; row[0] --;
//     ans.push_back(0); //注意这一步是必须的，不然在trace back里面pushback的始终会少一个

//     if (traceback(traceback, 0, 0)) {
//         for (int i : ans) cout << i << " " ;
//     } else {
//         cout << -1 << "\n";
//     }
// }



// 8.13

// vector<pair<int, int>> dir = {
//     {0, 1}, {0, -1}, {1, 0}, {-1, 0}
// };
// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n; cin >> n;
//     vector<string> board(n);
//     for (auto &line : board) cin >> line;

//     auto inside = [&](int x, int y) {
//         return x >= 0 && x < n && y >= 0 && y < n;
//     };
    
//     // 满足每一行和每一列都不同的条件，说明每一行和每一列的1的分布都不同了
//     auto check = [&]() {
//         set<int> rows, cols; //集合存储每一行每一列
//         // 行检验
//         for (int i = 0; i < n; i ++) {
//             int row = 0; 
//             for (int j = 0; j < n; j ++) {
//                 if (board[i][j] == '1') row |= (1 << j); //重点
//                 // 这里不开数组来存，用row的二进制表达下的某一位来表示这一列是否有1
//             }
//             if (rows.find(row) != rows.end()) return false; //如果这个row已经存在了，说明这一行和之前的某一行重复了
//             rows.insert(row);
//         }
//         // 列检验
//         for (int j = 0; j < n; j ++) {
//             int col = 0;
//             for (int i = 0; i < n; i ++) {
//                 if (board[i][j] == '1') col |= (1 << i); //同样的，col的二进制表达下的某一位来表示这一行是否有1
//             }
//             if (cols.find(col) != cols.end()) return false; //如果这个col已经存在了，说明这一列和之前的某一列重复了
//             cols.insert(col);
//         }
//         return true;
//     };

//     // 剩下两个限制条件，重复不超过两次和不超过半数
//     auto can = [&](int x, int y, int c) {
//         // 不超过两次
//         for (auto [dx, dy] : dir) {
//             int nx = x + dx, ny = y + dy;
//             int cnt = 0;
//             while (inside(nx, ny) && board[nx][ny] == c) {
//                 cnt++;
//                 if (cnt >= 2) return false; //重复不超过两次
//                 nx += dx; ny += dy;
//             }
//         }
//         // 不超过半数
//         // 行
//         if (x == n - 1) {
//             int cntZero = c == '0' ? 1 : 0;
//             for (int i = 0; i < n - 1; i ++) {
//                 if (board[i][y] == '0') cntZero++;
//             }
//             if (cntZero * 2 != n) return false; //不超过半数
//         }
//         //列
//         if (y == n - 1) {
//             int cntZero = c == '0' ? 1 : 0;
//             for (int j = 0; j < n - 1; j ++) {
//                 if (board[x][j] == '0') cntZero++;
//             }
//             if (cntZero * 2 != n) return false; //不超过半数
//         }

//         return true;
//     };

//     auto traceback = [&](auto &self, int pos) {
//         if (pos == n * n) return check(); //check函数来判断当前的board是否合法

//         int x = pos / n, y = pos % n;
//         if (board[x][y] != '_') {
//             if (!can(x, y, board[x][y])) return false; //处理特殊情况
//             return self(self, pos + 1);
//         }

//         //剩下两个限制条件，重复不超过两次和不超过半数
//         for (char c : {'0', '1'}) {
//             if (can(x, y, c)) {
//                 board[x][y] = c;
//                 if (self(self, pos + 1)) return true;
//                 board[x][y] = '_';
//             }
//         }
//         return false;
//     };
//     traceback(traceback, 0);
//     for (auto &line : board) cout << line << "\n";
// }

// 8.14
// vector<pair<int, int>> dir = {
//     {-1, -1}, {-1, 0}, {-1, 1},
//     {0, -1},  {0, 0},  {0, 1},
//     {1, -1},  {1, 0},  {1, 1}
// };

// int main(){
//     cin.tie(0) -> sync_with_stdio(0);
//     int n, m; cin >> n >> m;
//     auto cnt = vector(n, vector(m, -1)); // -1 代表没有数字
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             char ch; cin >> ch;
//             if (isdigit(ch)) cnt[i][j] = ch - '0';
//         }
//     }

//     auto inside = [&](int x, int y) {
//         return x >= 0 && x < n && y >= 0 && y < m;
//     };

//     //
//     auto limit = vector(n ,vector(m, vector<int>(9))); //每一个位置对应的临界值
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             for (int d = 0; d < 9; d ++) {
//                 auto [dx, dy] = dir[d];
//                 int nx = i + dx, ny = j + dy;
//                 if (!inside(nx, ny)) continue;

//                 int c = 0; // 记录当前格子能接受的最大数量
//                 //因为前面dir有一定顺序，且实际上每个格子的limit和这个方向确实有关，所以用dd代替d来进行遍历
//                 for (int dd = 9 - d; dd < 9; dd ++)  {
//                     auto [ddx, ddy] = dir[dd];
//                     int nnx = nx + ddx, nny = ny + ddy;
//                     if (inside(nnx, nny)) c ++; 
//                 } // 写这个循环目的是为了计算当前格子指向的的格子周围8个格子里面有几个是在给定区域内的
//                 //也就是说，这层循环的主要作用就是特判边界格子
//                 limit[i][j][d] = c;
//             }
//         }
//     }
//     //

//     vector<string> board(n, string(m, '0'));

//     // 邻居数组
//     auto neb  = vector(n, vector(m, vector<tuple<int ,int ,int>>()));
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             for (int d = 0; d < 9; d ++) {
//                 auto [dx, dy] = dir[d];
//                 int nx = i + dx, ny = j + dy;
//                 if (!inside(nx, ny)) continue;
//                 if (cnt[nx][ny] == -1) continue; // 没有数字
//                 neb[i][j].emplace_back(nx, ny, limit[i][j][d]); // 记录邻居格子的位置和方向
//             }
//         }
//     }

//     auto can = [&](int x, int y, int c) {
//         // check
//         for (auto [nx, ny, limit] : neb[x][y]) {
//             if (c == 0) {
//                 if (cnt[nx][ny] > limit) return false; //如果当前格子是0，那么它周围的数字格子就不能超过这个limit
//             } else {
//                 if (cnt[nx][ny] == 0) return false; //如果当前格子是1，那么它周围的数字格子就必须至少有一个
//             }
//         }
//         return true;
//     };

//     auto update = [&](int x, int y) {
//         // update
//         board[x][y] = '1';
//         for (auto [nx, ny, limit] : neb[x][y]) {
//             cnt[nx][ny] --; //如果当前格子是1，那么它周围的数字格子就必须至少有一个，所以每个数字格子的计数都要减1
//         }
//     };

//     auto rollback = [&](int x, int y) {
//         // rollback
//         board[x][y] = '0';
//         for (auto [nx, ny, limit] : neb[x][y]) {
//             cnt[nx][ny] ++; //回退的时候每个数字格子的计数都要加1
//         }
//     };

//     auto traceback = [&](auto &self, int pos) {
//         if (pos == n * m) return true;

//         int x = pos / m, y = pos % m;
//         if (can(x, y, 0)) { //check
//             if (self(self, pos + 1)) return true;
//         }
//         if (can(x, y, 1)) {
//             update(x, y); // update
//             if (self(self, pos + 1)) return true;
//             rollback(x, y); // rollback
//         }

//         return false;
//     };
//     traceback(traceback, 0);
//     for (auto &line : board) cout << line << "\n";
// }


// 8. 15

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n, m; cin >> n >> m;
//     auto grid = vector(n, vector(m, vector<int>(2)));
//     auto ans = vector(n, vector(m, 0));
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             int x; cin >> x;
//             if (x == 2) {
//                 cin >> grid[i][j][0] >> grid[i][j][1];
//                 ans[i][j] = -1;
//             } else {
//                 grid[i][j][0] = grid[i][j][1] = 0;
//             }
//         }
//     }
    
//     auto check = [&](int x, int y) {
//         return false;
//     };

//     auto can = [&](int x, int y, int c) {
//         // 横向
//         int y0 = y, x0 = x; 
//         while (grid[x][y][0]) {
//            y --; 
//         }
//         if (grid[x][y][0] < c) return false;
//         y = y0;
//         // 纵向
//         while (grid[x][y][0]) {
//             x --;
//         }
//         if (grid[x][y][1] < c) return false;

//         return true;
//     };


//     auto traceback = [&](auto &self, int pos) {
//         if (pos == n * m) return true;

//         int x = pos / m, y = pos % m;
//         if (check(x, y)) return false;

//         for (int i = 1; i < 10; i ++) {
//             if (can(x, y, i)) {
//                 ans[x][y] = i;
//                 if (self(self, pos + 1)) return true;
//             } else {
//                 break;
//             }
//         }
//         return false;
//     };

//     traceback(traceback, 0);


//     for(auto row : ans) {
//         for (auto cell : row) {
//             if (cell == -1) cout << "_ ";
//             else cout << cell << " ";
//         }
//         cout << "\n";
//     }
// }


// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n, m; cin >> n >> m;
//     auto board = vector(n, vector<int>(m, -1)); // -1代表不可填入数字的灰色格子
//     auto sums = vector(n, vector<pair<int, int>>(m));
//     int itemSize = 0;
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             int type; cin >> type;
//             if (type == 2) {
//                 cin >> sums[i][j].first >> sums[i][j].second;
//                 if (sums[i][j].first != -1) itemSize ++;
//                 if (sums[i][j].second != -1) itemSize ++;
//             } else {
//                 board[i][j] = 0; // 0 代表可填入数字的白色格子
//             }
//         }
//     }

//     // struct Item
//     // {
//     //     int sum;
//     //     int cnt;
//     //     vector<int> used;
//     // };

//     // using itemInfo = tuple<int, int, vector<int>>;
//     // vector<itemInfo> items(itemSize);

//     // //以上两种方式都能实现这种功能
//     // vector<tuple<int, int, vector<int>>> items;
//     using itemInfo = tuple<int, int, vector<int>>;
//     vector<itemInfo> items;
//     using itemIds = vector<int>;
//     auto pos2item = vector(n, vector(m, itemIds())); //一个点可能映射到两个item上

//     //映射就是直接映射（
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             // 并不会重复哦，因为大于0的只有可能是唯一的黑色的格子
//             // 纵向的
//             if (sums[i][j].first > 0) { 
//                 int cnt = 0;
//                 for (int k = i+ 1; k < n && board[k][j] == 0; k ++) {
//                     pos2item[k][j].push_back(items.size());
//                     cnt ++;
//                 }
//                 items.emplace_back(sums[i][j].first, cnt, vector<int>(10, 0));
//             }
//             // 横向的
//             if (sums[i][j].second > 0) {
//                 int cnt = 0;
//                 for (int k = j + 1; k < m && board[i][k] == 0; k ++) {
//                     pos2item[i][k].push_back(items.size());
//                     cnt ++;
//                 }
//                 items.emplace_back(sums[i][j].second, cnt, vector<int>(10, 0));
//             }
//         }      
//     }
    
//     auto can = [&](int x, int y, int d) {
//         for (auto itemId : pos2item[x][y]) {
//             auto &[sum, cnt, used] = items[itemId]; //必须加引用
//             if (sum < d) return false;
//             if (used[d]) return false;
//             if (cnt == 1 && sum != d) return false;
//         }
//         return true;
//     };

//     auto update = [&](int x, int y, int d) {
//         board[x][y] = d;
//         for (auto itemId : pos2item[x][y]) {
//             auto &[sum, cnt, used] = items[itemId]; //必须加引用
//             sum -= d;
//             cnt --;
//             used[d] = 1;
//         }
//     };

//     auto rollback = [&](int x, int y, int d) {
//         board[x][y] = 0;
//         for (auto itemId : pos2item[x][y]) {
//             auto &[sum, cnt, used] = items[itemId]; //必须加引用
//             sum += d;
//             cnt ++;
//             used[d] = 0;
//         }
//     };

//     auto traceback = [&](auto &self, int pos) {
//         if (pos == n * m) return true;

//         int x = pos / m, y = pos % m;
//         if (board[x][y] == -1) return self(self, pos + 1); //空格直接跳过

//         for (int d = 1; d <= 9; d ++) {
//             if (can(x, y, d)) {
//                 update(x, y, d);
//                 if (self(self, pos + 1)) return true;
//                 rollback(x, y, d);
//             }
//         }
//         return false;
//     };

//     traceback(traceback, 0);

//     for(auto row : board) {
//         for (auto cell : row) {
//             if (cell == -1) cout << "_ ";
//             else cout << cell << " ";
//         }
//         cout << "\n";
//     }
// }


// 8.16

// vector<pair<int, int>> dir = {
//     {1, 0}, {0, 1}, {0, -1}, {-1, 0}
// }; //提前确定顺序，方便绑定剩余数字

// int main() {
//     cin.tie(0)->sync_with_stdio(0);
//     int n; cin >> n;
//     vector<string> board(n);
//     for (auto &line : board) cin >> line;
//     auto cnt = vector(n, vector(n, 0));
//     auto lighted = vector(n, vector(n, 0));
//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < n; j ++) {
//             if (isdigit(board[i][j])) {
//                 cnt[i][j] = board[i][j] - '0';
//             }
//         }
//     }

//     auto check = [&]() {
//         for (int i = 0; i < n; i ++) {
//             for (int j = 0; j < n; j ++) {
//                 // 如果这个格子是空格且没有被点亮了，说明不合法
//                 if (board[i][j] == '.' && lighted[i][j] == 0) return false; 

//                 if (isdigit(board[i][j]) && cnt[i][j] != 0) return false; 
//             }
//         }
//         return true;
//     };

//     auto inside = [&](int x, int y) {
//         return x >= 0 && x < n && y >= 0 && y < n;
//     };

//     auto can = [&](int x, int y, int put) {
//         if (put) {
//             for (auto [dx, dy] : dir) {
//                 int nx = x + dx, ny = y + dy;
//                 if (!inside(nx, ny)) continue;
//                 if (isdigit(board[nx][ny]) && cnt [nx][ny] == 0) return false; //如果这个格子是数字格子且它的计数已经为0了，说明不合法

//                 while (inside(nx, ny)) {
//                     if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
//                     if (board[nx][ny] == 'O') return false; // 所有灯泡不能互相攻击
//                     nx += dx; ny += dy;
//                 }
//             }
//         } else {
//             for (int d = 0; d < 4; d ++) {
//                 int nx = x + dir[d].first, ny = y + dir[d].second;
//                 if (!inside(nx, ny)) continue;
//                 //这里有点像扫雷那个 画个图自己看看就好
//                 if (isdigit(board[nx][ny]) && cnt [nx][ny] >= 4 - d) return false; 
//             }
//         }
//         return true;
//     };

//     auto update = [&](int x, int y) {
//         board[x][y] = 'O';
//         for (auto [dx, dy] : dir) {
//             int nx = x + dx, ny = y + dy;
//             if (!inside(nx, ny)) continue;
//             if (isdigit(board[nx][ny])) cnt[nx][ny] --; //如果这个格子是数字格子，那么它周围的灯泡数量就要减1
//         }
//         lighted[x][y] ++; //点亮这个格子
//         for (auto [dx, dy] : dir) { //点亮能点亮的格子
//             int nx = x + dx, ny = y + dy;
//             while (inside(nx, ny)) {
//                 if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
//                 lighted[nx][ny] ++; //点亮这个格子
//                 nx += dx; ny += dy;
//             }
//         }
//     };

//     auto rollback = [&](int x, int y) {
//         board[x][y] = '.';
//         for (auto [dx, dy] : dir) {
//             int nx = x + dx, ny = y + dy;
//             if (!inside(nx, ny)) continue;
//             if (isdigit(board[nx][ny])) cnt[nx][ny] ++; 
//         }
//         lighted[x][y] --; 
//         for (auto [dx, dy] : dir) { 
//             int nx = x + dx, ny = y + dy;
//             while (inside(nx, ny)) {
//                 if (isdigit(board[nx][ny]) || board[nx][ny] == 'X') break; //如果遇到了数字或者墙，就停止  
//                 lighted[nx][ny] --; 
//                 nx += dx; ny += dy;
//             }
//         }
//     };

//     auto traceback = [&](auto &self, int pos) {
//         if (pos == n * n) return check();

//         int x = pos / n, y = pos % n;
//         if (board[x][y] != '.') return self(self, pos + 1);
        
//         if (can(x, y, 1)) {
//             update(x, y);
//             if (self(self, pos + 1)) return true;
//             rollback(x, y);
//         }

//         if (can(x, y, 0)) {
//             if (self(self, pos + 1)) return true;
//         }
//         return false;
//     };

//     traceback(traceback, 0);
//     for (auto &line : board) cout << line << "\n";
// }

//8.17
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