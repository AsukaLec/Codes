//test  Part 1 1.4
// #include <bits/stdc++.h>
// using namespace std;

// vector<string> maze ={"111",
// "1111",
// "111111"};

// int main(){
//     cout << maze.size();
//     cout << endl << maze[1].size();
// }

// test Part 1 1.7

// #include <bits/stdc++.h>
// using namespace std;

// vector<int> digits = {5,6,8,6,9,1,6,1,2,4,9,1,9,8,2,3,6,4,7,7,5,9,5,0,3,8,7,5,8,1,5,8,6,1,8,3,0,3,7,9,2,7,0,5,8,8,5,7,0,9,9,1,9,4,4,6,8,6,3,3,8,5,1,6,3,4,6,7,0,7,8,2,7,6,8,9,5,6,5,6,1,4,0,1,0,0,9,4,8,0,9,1,2,8,5,0,2,5,3,3};

// bool subMatch(vector<int> &arr, vector<int> &target) {
//     size_t idx = 0; //size_t 是C++标准库中定义的一种无符号整数类型
//     for (auto &elem : arr) { //遍历arr中的每一个元素
//         if (elem == target[idx]) {
//             if (++idx == target.size()) {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// int main() {
//     vector<int> dayInMonthes = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//     int cnt = 0;
//     for (int month = 1; month <= 12; month ++) {
//         for (int day = 1; day <= dayInMonthes[month]; ++day) {
//             vector<int> target = {2, 0, 2, 3, month/10, month%10, day/10, day%10}; // 巧妙的表示日期的办法
//             cnt += subMatch(digits, target);
//         }
//     }
//     cout << cnt << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;
// int main(){
//     int n ;
//     cin >> n;
//     vector<int> a(n + 1);
//     for (int i = 1; i <= n; i ++) {
//         cin >> a[i];
//         a[i] ^= a[i - 1];
//     }//第一位是0 后面异或和

//     //统计数字出现的个数
//     unordered_map<int, int> cnt;
//     for (auto &x : a) cnt[x] ++;// auto &x 把 x当作迭代器
//     long long ans = 0;
//     for (auto &[_, c] : cnt) {// 字典 所以有两个位置uto &[_, c] 
//         ans += (long long)c * (c - 1) / 2;
//     }
//     cout << ans << endl;
// }

// part 1 2.8
// #include <bits/stdc++.h>
// using namespace std;
// int main()
// {
//   int N, K;
//   cin >> N >> K;
//   long long cnt = 0;
//   vector<long long> a (N);
//   for (int i = 0; i < N; i++) {
//     cin >> a[i];
//   }

//   vector<long long> sum (N);
//   partial_sum(a.begin(), a.end(), sum.begin());

//   for (int k = 0 ; k < N; k ++) {
//       long long current ;
//       current = a[k] ;
//       if (current % K == 0) {
//         cnt += 1;
//       }
//     }

  
//     for (int k = 0 ; k < N; k ++) {
//         long long current ;
//         current = sum[k] ;
//         if (current % K == 0) {
//         cnt += 1;
//         }
//     }
  

//   for (int i = 1; i < N - 1; i++) {
//     for (int k = i + 1; k < N; k ++) {
//       long long current ;
//       current = sum[k] - sum[max(i - 1, 0)];
//       if (current % K == 0) {
//         cnt += 1;
//       }
//     }
//   }
//   cout << cnt;
//   return 0;
// }

// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, k;
//     cin >> n >> k;

//     vector<int> a(n + 1);
//     for (int i = 1; i <= n; i ++) cin >> a[i];

//     vector<int> s (n + 1);
//     for (int i = 1; i <= n; i++) {
//         s[i] = (s[i] + a[i - 1]) % k;//前缀和 和取模可以同时进行
//     }
//     //统计个数
//     vector<int> cnt(k);//选用k的原因： 一个数模 k 可能的结果是 0 到 k - 1， 这里用来统计每个结果出现的次数。
//     for (auto &x :s) cnt[x] ++;

//     long long ans = 0;
//     for (auto &c : cnt) ans += (long long )c * (c - 1) / 2;
//     cout << ans << endl; 
// }

//part 1 2.10 拔河


// #include <bits/stdc++.h>
// #include <numeric>
// using namespace std;
// int main() {
//     int n;
//     cin >> n;

//     vector<long long> maze (n);
//     for (auto &x : maze) cin >> x;

//     vector<long long> prefix(n);
//     partial_sum(maze.begin(), maze.end(), prefix.begin());

//     long long num_min = 1e9 + 1;
//     for (int i = 0; i < n - 1 ; i++) {
//         for (int k = i + 1; k < n; k++) {
//             long long a = prefix[k] - prefix[i];
//             long long b = prefix[i];
//             long long ans = abs(a - b);
//             if (ans < num_min) num_min = ans;
//         }
        
//     }
//     cout << num_min << endl;

// }

// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n;
//     cin >> n;

//     vector<long long> a (n);
//     for (auto &x : a) cin >> x;

//     vector<long long> sum(n + 1);
//     partial_sum(a.begin(), a.end(), sum.begin() + 1);

//     auto ans = LLONG_MAX;

//     set<long long> s; //分析得出这个数据结构的过程十分关键
    
//     for (int l2 = n - 1; l2 >= 1 ; l2--) {
//         for (int r2 = l2 + 1; r2 <= n; r2++) {
//             s.insert(sum[r2] - sum[l2]);
//         }// 枚举右区间 注意枚举方式 打断点看看 枚举的是前缀和数组

//         for (int l1 = 1; l1 <= l2; l1 ++) {
//             auto target = sum[l2] - sum[l1 - 1]; // 枚举方式 同上 打断点看看 实际上只枚举了中间的那个点

//             auto iter = s.lower_bound(target); //对于set或map,lower_bound的功能是返回一个迭代器，指向集合中第一个 大于或等于 指定值（ target ）的元素。
//             //此处判断

//             //iter != s.end() 说明可以找到这样的一个数
//             if (iter != s.end()) ans = min(ans, *iter - target);

            
//             if (iter != s.begin()) {
//                 -- iter;
//                 ans = min(ans, target - * iter);
//             }

//             //如果iter不等于s.begin(),说明iter当前指向的元素不是集合中的第一个元素。此时， iter  可以安全地进行自减操作（ --iter ），因为集合中至少还有一个元素位于  iter  之前。
//             //如果iter等于  s.begin(),说明iter指向集合的第一个元素。此时，如果再对  iter  进行自减操作，会导致迭代器越界（undefined behavior），因此需要避免。
//         }
//     }
//     cout << ans << endl;

// }



// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     set <int> s = {1, 2, 3, 4, 5};
//     auto iter = s.end();
//     --iter;
//     cout << *iter << endl;
//     iter = s.begin();
//     cout << *iter;

// }


// part 1 3.1 
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m;
//     cin >> n >> m;
//     auto colors = vector(3, vector<int>(n + 2));
//     while(m -- ) {
//         int l, r, c;
//         cin >> l >> r >> c;
//         colors[c - 1][l] ++;
//         colors[c - 1][r + 1] --;
//     }
//     for (auto &color : colors ) {
//         partial_sum(color.begin(), color.end(), color.begin());
//     }
//     int ans = 0;
//     for (int i = 1; i <= n; i++) {
//         if (colors[0][i] && colors[1][i] && !colors[2][i]) ans ++;
//     }
//     cout << ans;
// }

// part 1 3.2
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m;
//     cin >> n >> m;
//     auto maze = vector(n + 2, vector(n + 2, 0));
//     while (m--) {
//         int x1, y1, x2, y2;
//         cin >> x1 >> y1 >> x2 >> y2;
//         maze[x1][y1]++;
//         maze[x1][y2+1]--;
//         maze[x2+1][y1]--;
//         maze[x2+1][y2+1]++;
//     }//见上图

//     for (int i = 1; i <= n; i++ ) {
//         partial_sum(maze[i].begin(), maze[i].end(), maze[i].begin());//形式一
//         for (int j = 1; j <= n; j ++) {
//             maze[i][j] += maze[i -1][j];//形式二
//             cout << (maze[i][j] & 1);//快速判断奇偶性， 至于为什么是奇偶，前面每次操作加的都是一
//         }
//         cout << endl;
//     }
// }

//part 1 3.3 lq2128
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m;
//     cin >> n;
//     vector<long long > a(n);
//     for (auto & x : a) cin >> x;
//     vector<long long > sum (n + 1);
//     partial_sum(a.begin(), a.end(), sum.begin() + 1);

//     cin >> m;
//     long long total = 0; //未排序前的区间和
//     vector<long long> diff (n + 2);
//     while (m--) {
//         int l, r;
//         cin >> l >> r;

//         diff[l] ++;
//         diff [r + 1]--;

//         total += sum[r] - sum[l - 1];
//     }
//     partial_sum(diff.begin(), diff.end(), diff.begin());
//     sort(diff.begin(), diff.end(), greater<long long>());
//     //当传入greater<T>时，会按**降序（从大到小）**排列元素。若未指定第三个参数，默认行为相当于传递了 less<T>()，结果为升序。
//     sort(a.begin(), a.end(), greater<long long>());

//     long long ans = 0;
//     for (int i = 0; i < n; i ++) {
//         ans += a[i] * diff[i];
//     }
//     cout << ans - total << endl;
// }

// part 1 3.4 lq 19716
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<pair<int, int>> range (m);
//     vector<long long> cnt(n + 2);
//     for (auto &[f, s] : range ) {
//         cin >> f >> s;
//         cnt[f] ++;
//         cnt[s + 1] --;
//     }//范围循环快速输入
//     partial_sum(cnt.begin(), cnt.end(), cnt.begin());
//     vector<int> ones(n + 2);
//     int zero = 0;
//     partial_sum(cnt.begin(), cnt.end() - 1, ones.begin(), [&](int prev, int cur) {
//         if (cur == 0) zero ++;
//         if (cur == 1) return prev + 1;
//         return prev;
//     });// cnt.end() - 1: 最后一个位置不需要计数。
//     for (auto &[f, s] : range) {
//         cout << ones[s] - ones[f - 1] + zero << endl;
//     }
// }

//part 1 3.6 p4231
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<long long> diff(n + 3);
//     while (m --) {
//         int l, r, s, e;
//         cin >> l >> r >> s >> e;
//         int d = (e - s) / (r - l);
//         diff[l] += s;
//         diff[l + 1] += d - s;
//         diff[r + 1] -= e + d;
//         diff[r +2] += e;
//     }
//     partial_sum(diff.begin(), diff.end(), diff.begin());
//     partial_sum(diff.begin(), diff.end(), diff.begin());

//     cout << accumulate(diff.begin(), diff.end(), 0ll, [](long long prev, long long cur) {return prev ^ cur; });
//     //求和函数 匿名函数
//     cout << ' ' << *max_element(diff.begin(), diff.end());

// }

// part 1 3.7 P10266
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n = 9, m = 9;

//     int arr[n][m] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
//                      {0, 1, 1, 1, 1, 1, 1, 1, 0},
//                      {0, 1, 4, 4, 4, 4, 4, 1, 0},
//                      {0, 1, 4, 9, 9, 9, 4, 1, 0},
//                      {0, 1, 4, 9, 16, 9, 4, 1, 0},
//                      {0, 1, 4, 9, 9, 9, 4, 1, 0},
//                      {0, 1, 4, 4, 4, 4, 4, 1, 0},
//                      {0, 1, 1, 1, 1, 1, 1, 1, 0},
//                      {0, 0, 0, 0, 0, 0, 0, 0, 0},};

//     int ans [n][m] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0}};

//     for (int i = 1; i < n; i++) {
//         for (int j = 1; j < m; j ++) {
//             ans[i][j] = arr[i][j] + arr[i - 1][j - 1] - arr[i - 1][j] - arr[i][j - 1];
//         }
//     }

//     for (int i = 1; i <n; i++){
//         for (int j = 1; j < m ; j++) {
//             if (j + i == 9) ans[i][j] = 0;
//         }
//     }

//     int ans1 [n + 1][m + 1] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
//     for (int i = 1; i < n + 1; i++) {
//         for (int j = 1; j < m + 1; j ++) {
//             if(i == j) ans1[i][j] = ans[i][j] - ans[i - 1][j - 1] - ans[i - 1][j] - ans[i][j - 1];
//         }
//     }

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cout <<arr[i][j] << ' ';
//         }
//         cout << endl;
//     }
//     cout << endl;

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cout <<ans[i][j] << ' ';
//         }
//         cout << endl;
//     }
//     cout << endl;
//     for (int i = 0; i < n + 1; i++) {
//         for (int j = 0; j < m + 1; j++) {
//             cout <<ans1[i][j] << ' ';
//         }
//         cout << endl;
//     }
// }

// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     ios :: sync_with_stdio(false);
//     //解绑 scanf 缩短时间
//     cin.tie(0);

//     const int N = 3000 + 10;
//     int offset = 1000 +5;
//     int n, m, k;
//     cin >> n >> m >> k;
//     auto origin = vector(n, vector<long long> (m));
//     for (auto & row : origin) {
//         for (auto & x : row) cin >> x;
//     }    

//     auto diag = vector(N, vector<long long> (N));
//     auto back_diag = vector(N, vector<long long> (N));

//     while (k --) {
//         int x, y, p;
//         cin >> x >> y >>p;
//         x += offset;
//         y += offset;

//         diag[x+1][y+1] -= 2;
//         diag[x+2][y+2] -= 2;
//         diag[x-p+1][y-p+1] += 1;
//         diag[x-p+2][y-p+2] += 1;
//         diag[x+p+1][y+p+1] += 1;
//         diag[x+p+2] [y+p+2]+= 1;

//         back_diag[x+1][y] += 2;
//         back_diag[x+2][y - 1] += 2;
//         back_diag[x+1+p][y-p] -= 1;
//         back_diag[x+2+p][y-p-1] -= 1;
//         back_diag[x+1-p][y+p] -= 1;
//         back_diag[x+2-p][y+p-1] -= 1;
//         // 0 0 0 0 0 0 0 0 0 
//         // 0 1 1 1 1 1 1 1 0
//         // 0 1 4 4 4 4 4 1 0
//         // 0 1 4 9 9 9 4 1 0
//         // 0 1 4 9 16 9 4 1 0 **y
//         // 0 1 4 9 9 9 4 1 0
//         // 0 1 4 4 4 4 4 1 0
//         // 0 1 1 1 1 1 1 1 0
//         // 0 0 0 0 0 0 0 0 0
//         //         *x
//         // 0 0 0 0 0 0 0 0 0
//         // 0 1 0 0 0 0 0 0 0
//         // 0 0 3 0 0 0 0 0 0
//         // 0 0 0 5 0 0 0 0 0
//         // 0 0 0 0 7 0 0 0 0 **y
//         // 0 0 0 0 0 7 0 0 0
//         // 0 0 0 0 0 0 5 0 0
//         // 0 0 0 0 0 0 0 3 0
//         // 0 0 0 0 0 0 0 0 1
//         //         *x
//         // 0 0 0 0 0 0 0 0 0 0
//         // 0 1 0 0 0 0 0 0 0 0
//         // 0 0 2 0 0 0 0 0 0 0
//         // 0 0 0 2 0 0 0 0 0 0
//         // 0 0 0 0 2 0 0 0 0 0**y
//         // 0 0 0 0 0 0 0 0 0 0
//         // 0 0 0 0 0 0 -2 0 0 0
//         // 0 0 0 0 0 0 0 -2 0 0
//         // 0 0 0 0 0 0 0 0 -2 0
//         // 0 0 0 0 0 0 0 0 0 -1
//         //         *x
//         // 0 0 0 0 0 0 0 0 0 0 0
//         // 0 1 0 0 0 0 0 0 0 0 0
//         // 0 0 1 0 0 0 0 0 0 0 0
//         // 0 0 0 0 0 0 0 0 0 0 0
//         // 0 0 0 0 0 0 0 0 0 0 0**y
//         // 0 0 0 0 0 -2 0 0 0 0 0
//         // 0 0 0 0 0 0 -2 0 0 0 0
//         // 0 0 0 0 0 0 0 0 0 0 0
//         // 0 0 0 0 0 0 0 0 0 0 0
//         // 0 0 0 0 0 0 0 0 0 1 0
//         // 0 0 0 0 0 0 0 0 0 0 1
//         //         *x

        

//     }
//     auto diag_sum = [&](auto &diag) {
//         for (int i = 1; i < diag.size(); i ++) {
//             for (int j = 1; j < diag.size(); j ++) {
//                 diag[i][j] += diag[i - 1][j - 1];
//             }
//         }
//     };

//     auto back_diag_sum = [&](auto &diback_diagag) {
//         for (int i = 1; i < back_diag.size(); i ++) {
//             for (int j = back_diag.size() - 1; j > 0; j --) {
//                 back_diag[i][j] += back_diag[i - 1][j + 1];
//             }
//         }
//     };

//     //两次调用
//     diag_sum(diag);
//     diag_sum(diag);
//     back_diag_sum(back_diag);
//     back_diag_sum(back_diag);

//     auto total = vector(N, vector(N, 0ll));
//     for (int i = 0; i < N; i ++) {
//         for (int j = 0; j < N; j ++) {
//             total[i][j] = diag[i][j] + back_diag[i][j];
//         }
//     }

//     for (int i = 0; i < N; i ++) {
//         partial_sum(total[i].begin(),total[i].end(), total[i].begin());
//         for (int j = 0; j < N; j ++) {
//             total[i][j] = total[i - 1][j];
//         }
//     }

//     for (int i = 0; i < n; i ++) {
//         for (int j = 0; j < m; j ++) {
//             origin[i][j] -= total[i + 1 + offset][j + 1 + offset];
//             if (origin[i][j] < 0) origin[i][j] = 0;
//             cout << origin[i][j] << ' ';
//         }
//         cout << endl;
//     }
// }


// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     while (true) {int k; 
//         cin >> k;
//         vector<int> a = {1, 4, 9, 16, 25, 36, 49 , 0, 0, 0, 0, 0};
//             while (k--) {
//                 adjacent_difference(a.begin(), a.end(), a.begin());
//             }
//             for (int i = 0; i < 12; i ++) {
//                 cout << a[i] << ' ' ;    
//             }
//             cout << endl;
//         }
// }


// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int a, b, c, d;
//     cin >> a >> b >> c >> d;
    
//     vector <int> ans;

//     for (int i = 1; i <= 6; ++i) {  
//         ans.push_back(a * i * i * i + b * i * i + c * i + d);
//     }
//     for (int i = 1; i <= 4; ++i) {  
//         ans.push_back(0);
//     }

//     for (int i = 0; i < 10; i ++) {
//             cout << ans[i] << ' ' ;    
//     }
//     cout << endl;

//     while (true) {
//         int k; 
//         cin >> k;
        
//         vector <int> ans1(10, 0);
//         adjacent_difference(ans.begin(), ans.end(), ans1.begin());
        
//         if (k >= 2) {
//             while (k-- && k > 0) {
//                 adjacent_difference(ans1.begin(), ans1.end(), ans1.begin());
//                 }

//             for (int i = 0; i < 10; i ++) {
//                 cout << ans1[i] << ' ' ;    
//                 }
//             cout << endl;
//         }
//         else {
//             for (int i = 0; i < 10; i ++) {
//                 cout << ans1[i] << ' ' ;    
//                 }
//             cout << endl;
//         }
        
//     }
//     return 0;
// }

// 1 7 2 3
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

// part 1  3. 8 P 4552

// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int k;
//     cin >> k;
//     vector <int> maze;
//     for (int i = 0; i < k; i ++) {
//         long long a;
//         cin >> a;
//         maze.push_back(a);
//     }

//     adjacent_difference(maze.begin(), maze.end(), maze.begin());

//     long long pos = 0, neg = 0;

//     for (int i = 1; i < k; i ++) {
//         if (maze[i] > 0) pos += maze[i];
//         else neg  += - maze[i];
//     }


//     long long op = max(pos, neg);
//     long long posible =  abs(pos + neg) + 1;

//     cout << op << endl;
//     cout << posible << endl;
// }


//part 1 3.9 P6070
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n, m, t;
//     cin >> n >> m >> t;
//     auto maze = vector(n + 2, vector<long long> (n + 2, 0));
//     auto ans = vector(n + 2, vector<long long> (n + 2, 0));
//     while (m--) {
//         int x, y, z;
//         cin >> x >> y >> z;
//         maze[x ][y] += z;
//     }
    
//     for (int i = 1; i <= n + 1; i ++) {
//         for (int k = 1; k <= n + 1 ; k ++) {
//             ans[i][k] += maze[i][k] + maze[i - 1][k - 1] - maze[i - 1][k] - maze[i][k - 1];

//         }
//     }

//     for (int i = 0; i <= n + 1; i ++) {
//         for (int k = 0; k <= n + 1; k ++) {
//             cout << ans[i][k] << ' ';
            
//         }
//         cout << endl;
//     }

//     long long total = 0;
//     for (int i = 0; i <= n + 1 - t; i ++) {
//         for (int k = 0; k <= n + 1 -t ; k ++) {
//             if (ans[i][k] != 0) {
//                 total += abs(ans[i][k]);
                
//                 ans[i][k + t] += ans[i][k];
//                 ans[i + t][k] += ans[i][k];
//                 ans[i + t][k + t] -= ans[i][k];

//                 ans[i][k] -= ans[i][k];
//             }
            
//         }
//     }

//     for (int i = 0; i <= n + 1; i ++) {
//         for (int k = 0; k <= n + 1 ; k ++) {
//             if (ans[i][k] != 0) {
//                 cout << -1 << endl;
//                 return 0;
//             }
            
//         }
//     }

//     cout << total << endl;
//     return 0;

// }




// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n ;
//     cin >> n ;
//     vector <int> arr(n + 1, 0);
//     for (auto &x : arr) cin >> x;

//     adjacent_difference(arr.begin(), arr.end(), arr.begin());

//     for (int i = 0;i < n; i ++) cout << arr[i] << ' ' ;

//     while (true) {
        
//         int l, r, delta;
//         cin >> l >> r >> delta;
//         arr[l] += delta;   
//         arr[r + 1] -= delta;
//         for (int i = 0;i < n; i ++) cout << arr[i] << ' ' ;
//     }
// }

// // part 1  3. 10 
// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (auto & x: a) cin >> x;
//     vector <long long > diff (n + 2);
//     adjacent_difference (a.begin(), a.end(), diff.begin() + 1);
//     vector <long long> leftsum (n + 2), rightsum (n + 2);

//     partial_sum(diff.begin(), diff.end(), leftsum.begin(), [](long long prev, long long cur) {
//         if (cur > 0) return prev;
//         return prev + (1 - cur);
//     });
//     //后缀和 .rbegin()
//     partial_sum(diff.rbegin(), diff.rend(), rightsum.rbegin(), [](long long prev, long long cur) {
//         if (cur < 0) return prev;
//         return prev + (1 + cur);
//     });

//     long long ans = LLONG_MAX;
//     for (int i = 1; i <= n; i ++) {
//         ans = min (ans, max(leftsum[i], rightsum[i + 1]));
//     }
//     cout << ans << endl;

// }

// #include <bits/stdc++.h>
// using namespace std;
// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     if (l < r && match(l, r - 1)) {
//         update (l, r - 2);
//         remove (l ++, r);
//     } else if (r <= e) {
//         insert (l, r ++);
//     } else {
//         update(l, r - 1);
//         remove(l ++, r);
//     }
//   }  
// }

// int main() {
//     int start, end;
//     increseEnumerate ( start, end,
//         [&](int l, int r) {

//         },
//         [&](int l, int r) {

//         },
//         [&](int l, int r) {

//         },
//         [&](int l, int r) {

//         });
// }


// #include <bits/stdc++.h>
// using namespace std;

// // 条件 t[r] - t[l] >= d
// // 不符合条件的区间， 是否有 >= k

// int main() {
//     int n, d, k;
//     cin >> n >> d >>k;
//     auto logs = vector<pair<int, int>>(n);
//     for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
//     sort(logs.begin(), logs.end());

//     // for (int i = 0; i < n; i++) {
//     //     cout << logs[i].first << ' ' << logs[i].second << endl;
//     // }

//     vector<int> cnt (100001);
//     set<int> ans;
//     for (int l = 0, r = 0; r < n; ) {
//         while (r < n && logs[r].first - logs[l].first < d) {
//             int id = logs[r++].second;
//             cnt[id] ++;
//             if (cnt[id] == k) ans.insert(id);
//         }
//         cnt[logs[l].second]--;
//     }
//     for (auto x: ans) cout << x << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;

// // 条件 t[r] - t[l] >= d
// // 不符合条件的区间， 是否有 >= k



// int main() {
//     int n, d, k;
//     cin >> n >> d >>k;
//     auto logs = vector<pair<int, int>>(n);
//     for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
//     sort(logs.begin(), logs.end());

//     // for (int i = 0; i < n; i++) {
//     //     cout << logs[i].first << ' ' << logs[i].second << endl;
//     // }
//     vector<int> cnt (100001);
//     set<int> ans;
//     increseEnumerate (0, n - 1,
//         [&](int l, int r) {
//             return logs[r].first - logs[r].first >= d;
//         },
//         [&](int l, int r) {
//             cnt[logs[r].second] ++;
//         },
//         [&](int l, int r) {
//             cnt[logs[l].second] --;
//         },
//         [&](int l, int r) {
//             if (cnt[logs[l].second] >= k)  ans.insert(logs[l].second);
//         });
    
//     for (auto x: ans) cout << x << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;


// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
//     if (match(l, r - 1)) update(l, r - 2);
//     else update(l, r - 1);
//     remove(l ++, r);
//     }
// }

// int main() {
//     int n, m, k;
//     cin >> n >> m >> k;
//     auto maze = vector(n, vector<int>(m));
//     for (auto &row : maze) {
//         for (auto &x : row) cin >> x;
//     }
    
//     long long ans = 0;
//     for (int x1 = 0; x1 < n; x1 ++) {
//         vector<int> sum(m);
//         for (int x2 = x1; x2 < n; x2 ++) {
//             for (int y =0; y < m; y ++) sum[y] += maze[x2][y];

//             int total = 0;

//             increseEnumerate (0, m - 1,
//             [&](int l, int r) {
//                 return total > k;
//             },
//             [&](int l, int r) {
//                 total += sum[r];
//             },
//             [&](int l, int r) {
//                 total -= sum[l];
//             },
//             [&](int l, int r) {
//                 ans += r - l + 1;
//             });
//         }
//     }
//     cout << ans << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n ,m ,limit;
//     cin >> n >> m;
//     auto maze = vector(n, vector<int>(m));
//     for (auto &row : maze) {
//         for (auto &x : row) cin >> x;
//     }

//     cin >> limit;
//     int ans = 0;
//     for (int x1 = 0; x1 < n; x1 ++) {
//         vector<int> mmin(m, INT_MAX);
//         vector<int> mmax(m, INT_MIN);
//         // insert [x1, x2] max, min
//         for (int x2 = x1; x2 < n; x2 ++) {
//             for (int i = 0; i < m; i++) {
//                 mmin[i] = min(mmin[i], maze[x2][i]);
//                 mmax[i] = max(mmax[i], maze[x2][i]);
//             }
//             multiset<int> s;
//             for (int l = 0, r = 0; l < m; ) {
//                 while (r < m && (s.empty() || *s.rbegin() - *s.begin() <= limit)) {
//                     s.insert(mmin[r]);
//                     s.insert(mmax[r++]);
//                 }

//                 if (!(s.empty() || *s.rbegin() - *s.begin() <= limit)) {
//                     ans = max(ans, (x2 - x1 + 1) * (r - l + 1));
//                 } else {
//                     ans = max(ans, (x2 - x1 + 1) * (r - l));
//                 }
//                 s.erase(s.find(mmin[l]));
//                 s.erase(s.find(mmax[l++]));
//             }
//         }
//     }
//     cout << ans << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n ,m ,limit;
//     cin >> n >> m;
//     auto maze = vector(n, vector<int>(m));
//     for (auto &row : maze) {
//         for (auto &x : row) cin >> x;
//     }

//     cin >> limit;

//     int ans = 0;
//     for (int x1 = 0; x1 < n; x1 ++) {
//         vector<int> mmin(m, INT_MAX);
//         vector<int> mmax(m, INT_MIN);
//         // insert [x1, x2] max, min
//         for (int x2 = x1; x2 < n; x2 ++) {
//             for (int i = 0; i < m; i++) {
//                 mmin[i] = min(mmin[i], maze[x2][i]);
//                 mmax[i] = max(mmax[i], maze[x2][i]);
//             }
//             multiset<int> s;
//             for (int l = 0, r = 0; l < m; ) {
//                 while (r < m && (s.empty() || *s.rbegin() - *s.begin() <= limit)) {
//                     s.insert(mmin[r]);
//                     s.insert(mmax[r++]);
//                 }

//                 if (!(s.empty() || *s.rbegin() - *s.begin() <= limit)) {
//                     ans = max(ans, (x2 - x1 + 1) * (r - l - 1));
//                 } else {
//                     ans = max(ans, (x2 - x1 + 1) * (r - l));
//                 }
//                 s.erase(s.find(mmin[l]));
//                 s.erase(s.find(mmax[l++]));
//             }
//         }
//     }
//     cout << ans << endl;
// } 



// #include <bits/stdc++.h>
// using namespace std;

// // 条件 t[r] - t[l] >= d
// // 不符合条件的区间， 是否有 >= k

// int main() {
//     int n, d, k;
//     cin >> n >> d >>k;
//     auto logs = vector<pair<int, int>>(n);
//     for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
//     sort(logs.begin(), logs.end());

//     for (int i = 0; i < n; i++) {
//         cout << logs[i].first << ' ' << logs[i].second << endl;
//     }

//     vector<int> cnt (100001);
//     set<int> ans;
//     for (int l = 0, r = 0; r < n; ) {
//         while (r < n && logs[r].first - logs[l].first < d) {
//             int id = logs[r++].second;
//             cnt[id] ++;
//             if (cnt[id] == k) ans.insert(id);
//         }
//         cnt[logs[l++].second]--;
//     }
//     for (auto x: ans) cout << x << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
// // 1 1 4 5 1 4
// // 1 1 1 4 4 5
// // [1 max] [min 5]
// // max - 1 = 5 - min
// // max + min = 5 + 1
// // a + b = target
//     int T, id;
//     cin >> T >> id;
//     while (T--) {
//         int n;
//         cin >> n;
//         vector<int> a(n);
//         for (auto &x : a) cin >> x;
//         sort(a.begin(), a.end());
//         int target = a[0] + a[n - 1];
//         cout << [&](){
//             for (int l = 1, r = n - 2; l < r;) {
//                 if (a[l] + a[r] > target) {
//                     r--;
//                 } else if (a[l] + a[r] < target) {
//                     l++;
//                 } else {
//                     return "Yes";
//                 }
//             }
//             return "No";
//         }() << endl;
//     }
// }


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n , g ;
//     cin >> n >> g;
//     auto line = vector<int>(n);
//     for (auto &x : line) cin >> x;
    
//     long long ans = 0;

//     if (g != 1) {
//         for (int i = 0 ; i < n; i ++) line[i] = line[i] % g;

//         int current = 0;
//         for (int l = 0, r = 0; r < n; ) {
//             if (!line[r] ) {
//                 ++ r;
//             } else if (line[r] && !current) {
//                 current ++;
//                 r++;
//             } else if (line[r] && current) {
//                 ans += r - l - 1;
//                 ++ l;
//                 r = l;
//                 current = 0;
//             }
            
//         }
//     }

//     if (g == 1) ans = n * (n - 1) / 2;
    
//     cout << ans << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n , g ;
//     cin >> n >> g;
//     auto line = vector<int>(n);
//     for (auto &x : line) cin >> x;
    
//     long long ans = 0;

//     for (int i = 0 ; i < n; i ++) {
//             line[i] = line[i] % g;
//             if (line[i] != 0) line[i] = 1;
//     }
        
//     int current = 0;
//     for (int l = 0, r = 0; l < n; ) {
//         while(r < n && current < 2) {
//             current += line[r++];
//         }
        
//         if (current >= 2) {
//             ans += (r - 2) - (l + 1) + 1;
//         } else {
//             ans += (r - 1) - (l + 1) + 1;
//         }

//         current -= line[l++];
//     }
        

//     cout << ans << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;

// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
//     if (match(l, r - 1)) update(l, r - 2);
//     else update(l, r - 1);
//     remove(l ++, r);
//     }
// }

// int main () {
//     int n, x;
//     cin >> n >> x;
//     n--;
//     vector<int> arr(n);
//     for (auto & x : arr) cin >> x;

//     x <<= 1;
//     int sum = 0; 
//     int ans = 0;

//     increseEnumerate (0, n - 1,
//         [&](int l, int r) { //match
//             return sum >= x;
//         },
//         [&](int l, int r) { //insert
//             sum += arr[r];
//         },
//         [&](int l, int r) { //remove
//             sum -= arr[l];
//         },
//         [&](int l, int r) { //update
//             ans = max(ans, r - l + 1);
//         });

//     cout << ans + 1 << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     string s;
//     cin >> s;
//     int k;
//     cin >> k;

//     int ans = 0;
//     for (int x = 1; x <= 26; x ++) {
//         int cnt[128] = {};
//         int typecnt = 0;
//         int matchcnt = 0;
//         for (int l = 0, r = 0; l < s.size();) {
//             while (r < s.size() && typecnt <= x) {
//                 char c = s[r++];
//                 if (cnt[c] == 0) typecnt ++;
//                 cnt[c]++;
//                 if (cnt[c] == k) matchcnt ++;
//             }
//             //[l, r - 1] 最大匹配情况
//             if (matchcnt == x) {
//                 if (typecnt > x) {
//                     //[l, r - 1] 满足
//                     //[l, r - 2] 不满足
//                     ans = max(ans, r - 2 -l + 1);
//                 } else {
//                     ans = max(ans, r - 1 - l + 1);
//                 }
//             }
//             char c = s[l ++];
//             if (cnt[c]-- == k ) matchcnt--;
//             if (cnt[c] == 0) typecnt --;
//         }
//     }
//     cout << ans << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;

// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
//     if (match(l, r - 1)) update(l, r - 2);
//     else update(l, r - 1);
//     remove(l ++, r);
//     }
// }

// int main() {
//     string s;
//     cin >> s;
//     int k;
//     cin >> k;

//     int ans = 0;
//     for (int x = 1; x <= 26; x ++) {
//         int cnt[128] = {};
//         int typecnt = 0;
//         int matchcnt = 0;
//     increseEnumerate (0, s.size() - 1,
//         [&](int l, int r) { //match
//             return typecnt > x;
//         },
//         [&](int l, int r) { //insert
//             char c = s[r];
//             if (cnt[c]++ == 0) typecnt++;
//             if (cnt[c] == k) matchcnt++;
//         },
//         [&](int l, int r) { //remove
//             char c = s[l];
//             if (cnt[c]-- == k) matchcnt--;
//             if (cnt[c] == 0) typecnt--;
//         },
//         [&](int l, int r) { //update
//             if (matchcnt == x) {
//                 ans = max(ans, r - l + 1);
//             }
//         });
//     }
//     cout << ans << endl;
// }


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     int n;
//     cin >> n;
//     vector <int> height (n);
//     for (auto &x : height) cin >> x;

//    int ans = 0;
//     for (int l = 0, r = height.size() - 1; l < r;) {
//         ans = max(ans, min(height[l], height[r]) * (r - l));
//         if (height[l] < height[r]) l++;
//         else r--;
//     }
//     cout << ans << endl;
// }

// #include <bits/stdc++.h>
// using namespace std;

// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
//     if (match(l, r - 1)) update(l, r - 2);
//     else update(l, r - 1);
//     remove(l ++, r);
//     }
// }

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<pair<int, int>> arr;
//     arr.reserve(n * m);

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             int h;
//             cin >> h;
//             arr.push_back({h, i});
//         }
//     }

//     sort(arr.begin(), arr.end());

//     vector<int> cnt(n);
//     int classCnt = 0;
//     int ans = INT_MAX;

//     increseEnumerate(0, n * m - 1,
//         [&](int l, int r) {
//             return classCnt == n;
//         },
//         [&](int l, int r) {
//             if (cnt[arr[r++].second]++ == 0) classCnt++;
//         },
//         [&](int l, int r) {
//             if (--cnt[arr[l++].second] == 0) classCnt--;
//         },
//         [&](int l, int r) {
//             // [l, r+1]
//             if (r + 1 == n * m) return;
//             ans = min(ans, arr[r + 1].first - arr[l].first);
//         });
//     cout << ans << endl;
// }/



// #include <bits/stdc++.h>
// using namespace std;

// template < typename M, typename I, typename R, typename U>
// void increseEnumerate(int s, int e,
//                       const M& match,
//                       const I& insert,
//                       const R& remove,
//                       const U& update) {
// for (int l = s, r = s; l <= e; ) {
//     while(l == r || r <= e && !match(l, r - 1)) insert (l, r ++);
//     if (match(l, r - 1)) update(l, r - 2);
//     else update(l, r - 1);
//     remove(l ++, r);
//     }
// }

// int main() {
//     int n, m, k;
//     cin >> n >> m >> k;
//     vector<string> maze(n);
//     for (auto &row : maze) cin >> row;
//     int ans = 0;
//     tuple<char, int, int, int, int> res;

//     auto func = [&](int B, int G, int P) {
//         vector<int> v(128);
//         v['B'] = B;
//         v['G'] = G;
//         v['P'] = P;

//         for (int x1 = 0; x1 < n; x1++) {
//             vector<int> sum(m);
//             for (int x2 = x1; x2 < n; x2++) {
//                 for (int i = 0; i < m; i++) {
//                     sum[i] += v[maze[x2][i]];
//                 }
           

//             int total = 0;
//             increseEnumerate(0, m - 1,
//                 [&](int l, int r) {
//                     return total > k;
//                 },
//                 [&](int l, int r) {
//                     total += sum[r];
//                 },
//                 [&](int l, int r) {
//                     total -= sum[l];
//                 },
//                 [&](int l, int r) {
//                     int temp = (x2 - x1 + 1) * (r - l + 1);
//                     if (temp > ans) {
//                         ans = temp;
//                         char c = 'p';
//                         if (B == 0) c = 'B';
//                         else if (B == 1) c = 'G';
//                         res = {c, x1, x2, l, r};
//                     }
//                 });
//             } 
//         }
//     };

//     func(0, 1, k + 1);
//     func(1, 0, k + 1);
//     func(k + 1, k + 1, 0);

//     auto [c, x1, x2, y1, y2] = res;
//     for (int x = x1; x <= x2; x++) {
//         for (int y = y1; y <= y2; y++) {
//             maze[x][y] = c;
//         }
//     }

//     cout << ans << endl;
//     for (auto row : maze) cout << row << endl;

// }


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
