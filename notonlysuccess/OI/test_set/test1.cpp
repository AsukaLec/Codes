#include<bits/stdc++.h>
using namespace std;
// 6.1
// int  main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     vector<vector<int>> intervals;
//     int n, m;
//     cin >> n >> m;  
//     intervals.resize(n, vector<int>(m));

//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < m; j++) {
//             cin >> intervals[i][j];
//         }
//     }

//     //按照第二个元素进行排序
//     sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
//         return a[1] < b[1]; //升序
//     });
    
//     int ans = 0;
//     int right = -5e4; //初始化右端点 无限靠近左侧

//     for (auto &interval : intervals) {
//         if (interval[0] >= right) {
//             right = interval[1];
//             ans ++;
//         }   
//     }
    
//     cout << intervals.size() - ans << "\n";
// }

// 6.2

// int main() {
//     int T;
//     cin >> T;
//     while (T--) {
//         int n;
//         cin >> n;
//         vector<pair<int, int>> arr(n);
//         int maxD = 0;
//         for (int i = 0; i < n; i++) {
//             cin >> arr[i].first;
//             maxD = max(maxD, arr[i].first);
//         }
//         int total = 0;
//         for (int i = 0; i < n; i++) {
//             cin >> arr[i].second;
//             total += arr[i].second;
//         }

//         vector<vector<int>> scores(maxD + 1);

//         for (auto &[d, s] : arr) scores[d].push_back(s);

//         priority_queue<int> pq;
//         for (int i = maxD; i >= 1; i--) {
//             for (auto &s : scores[i]) pq.push(s);

//             if (pq.size()) { //防止为空
//                 total -= pq.top();
//                 pq.pop();
//             }
//         }
//         cout << total << endl;
//     }
// }


//6.3


// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };


// class Solution {
// public:
//     ListNode* mergeKLists(vector<ListNode*>& lists) {
//         using node = ListNode;
//         node *dummy = new node(); //用一个空节点方便遍历
//         node *tail = dummy;
        
//         struct Cmp {
//             bool operator()(node* a, node* b) {
//                 return a -> val > b -> val; //小顶堆
//             }
//         };
//         priority_queue<node*, vector<node*>, Cmp> pq;
//         //或者
//         auto cmp = [](node* a, node* b) {
//             return a -> val > b -> val;
//         };
//         priority_queue<node*, vector<node*>, decltype(cmp)> pqq(cmp);
//         //

//         for (auto list : lists) {
//             if (list) pq.push(list); //防止空链表
//         }
//         while (pq.size()) {
//             auto s = pq.top();
//             pq.pop();
//             tail -> next = s;
//             tail = tail -> next;
//             if (s -> next) pq.push(s -> next);
//         }

//         return dummy -> next;
//     }
// };


//6.4

// int main() {
//     int n;
//     cin >> n;
//     vector<int> a(n);
//     for (auto &x : a) cin >> x;

//     vector<int> sub(n/2);
//     for (int i = 0; i < n/2; i++) {
//         sub[i] = a[n - i - 1] - a[i];
//     }

//     long long  count = 0;
//     for(int i = 0;i < n / 2; i++) {
//         if (i + 1 < n) { //判断符号是否相同
//             if (1ll * sub [i] * sub[i + 1] > 0) { //开 long long 防止溢出
//                 int min_abs = min(abs(sub[i]), abs(sub[i + 1]));
//                 count += min_abs;
//                 if (sub[i] > 0) {
//                     sub[i] -= min_abs;
//                     sub[i + 1] -= min_abs;
//                 } else {
//                     sub [i] += min_abs;
//                     sub[i + 1] += min_abs;
//                 }
//             }
//         } 
//         count += abs(sub[i]);
//     }
//     cout << count;
//     //for(auto &x : sub) cout << x << " ";
// }


//6.5

// int main() {
//     int n;
//     cin >> n;
//     vector<vector<int>> a(10);
//     for(int i = 0; i < n ; i ++) {
//         int x, value;
//         cin >> x >> value;
//         a[x].push_back(value);
//     }

//     for (auto &vec : a) {
//         sort(vec.begin(), vec.end(), greater<int>());
//     }

//     int times = n / 10;
//     long long ans = 0;

//     for (int i = 0; i < 10; i ++) {
//         if(a[i].size() != 0) for (size_t j = times; j < a[i].size(); j++) ans += a[i][j];
//     }

//     cout << ans << endl;
// }

//6.6

// int main () {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL);
//     cout.tie(NULL);

//     int T;
//     cin >> T;
//     while (T--) {
//         int a2, a3, a4, b4, b6;
//         cin >> a2 >> a3 >> a4 >> b4 >> b6;

//         int ans = 0;
//         // int b4_cap = 4, b6_cap = 6;


//         //用 a3 + a3填 b6
//         while (a3 >= 2 && b6) {a3 -= 2; b6--; ans += 6;}

//         // 用 a4 + a2 填 b6
//         while (a4 && a2 && b6) {a4 -- ; a2 --; b6--; ans += 6;}

//         // 用 a2 + a2 + a2 填 b6
//         while (a2 >= 3 && b6) {b6 --; a2 -= 3; ans += 6;}

//         // 用 a3 + a2 填 b6 
//         while (a2 && a3 && b6) {a2 --; a3 --; b6 --; ans += 5;}

//         // 用 a4 填 b6 
//         while (a4 && b6) {b6 --; a4 --; ans += 4;}
//         // 用 a2 + a2 填 b6
//         while (a2 >= 2 && b6) {a2 -= 2; b6 --; ans += 4;}

//         // 用a3填 b6
//         while (a3 && b6) {a3 --; b6 --; ans += 3;}
//         // 用 a2 填 b6
//         while (a2 && b6) {a2 --; b6 --; ans += 2;}



//         // 处理 b4部分 不需要判定 b4 剩余的空间是否够塞多一组人
//         // 用 a4 填 b4
//         while (a4 && b4) {a4 --; b4 --; ans += 4;}
//         // 用 a2 + a2 填 b4
//         while (a2 >= 2 && b4) {b4 --; a2 -= 2; ans += 4;}

//         // 用 a3 填 b4
//         while (a3 && b4) {a3 --; b4 --; ans += 3;}

//         // 用 a2 填 b4
//         while (a2 && b4) {a2 --; b4 --; ans += 2;}
        
//         cout << ans << "\n";
//     }
// }

// int main () {
//     int q;
//     cin >> q;
//     while (q--) {
//         int a2, a3, a4, b4, b6;
//         cin >> a2 >> a3 >> a4 >> b4 >> b6;
//         vector<tuple<int, int, int, int>> patterns = {
//             {0, 2, 0, 6}, // a3 + a3 
//             {1, 0, 1, 6}, // a4 + a2 
//             {3, 0, 0, 6}, // a2 + a2 + a2 
//             {1, 1, 0, 5}, // a3 + a2 
//             {0, 0, 1, 4}, // a4 
//             {2, 0, 0, 4}, // a2 + a2 
//             {0, 1, 0, 3}, // a3 
//             {1, 0, 0, 2}, // a2 
//         };

//         vector<int> boards(b6, 6);
//         boards.insert(boards.end(), b4, 4);

//         int total = 0;
//         for (auto &board : boards) {
//             for (auto &[need_a2, need_a3, need_a4, score] : patterns) {
//                 if (a2 >= need_a2 && a3 >= need_a3 && a4 >= need_a4 && board >= need_a2 * 2 + need_a3 * 3 + need_a4 * 4) {
//                     a2 -= need_a2;
//                     a3 -= need_a3;
//                     a4 -= need_a4;
//                     total += score;
//                     break;
//                 }
//             }
//         }
//         cout << total << "\n";
//     }
// }


// int main () {
//     int n ;
//     cin >> n;
//     vector<vector<int>> abc(n, vector<int>(3));

//     vector<long long> start(3, 0);

//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < n; j++) {
//             cin >> abc[j][i];
//             start[i] += abc[j][i];
//         }
//     }

//     int ans = 0;

//     for (int i = 0; i < 3; i ++) {
//         sort(abc.begin(), abc.end(), [i](auto &a, auto &b) {
//             if (a[i] != b[i]) return a[i] < b[i];
//             else return a[(i + 1) % 3] + a[(i + 2) % 3] >= b[(i + 1) % 3] + b[(i + 2) % 3];
//         });

//         // sort(abc.begin(), abc.end(), [i](auto &a, auto &b) {
//         //     return (a[i] - a[(i + 1) % 3] - a[(i + 2) % 3]) < (b[i] - b[(i + 1) % 3] - b[(i + 2) % 3]);
//         // });

//         // cout << "\n" << "i = " << i << "\n";
//         // for (auto &vec : abc) {
//         //     for (auto &x : vec) cout << x << " ";
//         //     cout << "\n";
//         // }

//         vector<long long> curr = start;

//         for (int x = 0; x < n; x++) {
//             if (curr[i] < curr[(i + 1) % 3] + curr[(i + 2) % 3]) {
//                 curr[i] -= abc[x][i];
//                 curr[(i + 1) % 3] -= abc[x][(i + 1) % 3];
//                 curr[(i + 2) % 3] -= abc[x][(i + 2) % 3];
//                 continue;
//             } else {
//                 ans = max(ans, n - x);
//                 break;
//             }
//         }
//     }

//     cout << ans << "\n";
// }


// int main () {
//     int n;
//     cin >> n;
//     using xyz = tuple<int, int, int>;
    
//     // 输入，注意占位符的使用
//     vector<xyz> arr(n);
//     for (auto &[x, _, __] : arr) cin >> x;
//     for (auto &[_, y, __] : arr) cin >> y;  
//     for (auto &[_, __, z] : arr) cin >> z;

//     int ans = -1;
    
//     //匿名函数 用于计算
//     auto calc = [&]() {
//         // 转换原来的不等式为一个值排序的问题
//         auto getV = [](xyz &t) {
//             auto [a, b, c] = t;
//             return a - b - c;
//         };
//         // 排序依据，先排正值，再排负值
//         sort (arr.begin(), arr.end(), [&](xyz &a, xyz &b) {
//             return getV(a) > getV(b);
//         });
        
//         // 次数从0开始累加
//         long long v = 0;
//         int cnt = 0;
//         for (auto x: arr) {
//             v += getV(x);
//             cnt += (v > 0);
//         }
//         ans = max(ans, cnt);
//     };

//     calc();
//     // 高效的交换
//     for (auto &[x, y, z] : arr) swap(x, y);
//     calc();
//     for (auto &[x, y, z] : arr) swap(x, z);
//     calc();
//     cout << ans << "\n";
// }


// int main() {
//     int n; cin >> n;
//     int m; cin >> m;
    
//     // vector<vector<long long>> items(m, vector<long long>(4));
//     // for (auto &item : items) {
//     //     cin >> item[0] >> item[1];
//     // }

//     // for (auto &item : items) {
//     //     int cur = item[1] / (2 * (- item[0]));
//     //     if ((item[0] * cur * cur + item[1] * cur) > (item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1))) {
//     //         item[2] = cur;
//     //         item[3] = item[0] * cur * cur + item[1] * cur;
//     //     } else {
//     //         item[2] = cur + 1;
//     //         item[3] = item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1);
//     //     }
//     // }

//     vector<vector<long long>> items(m, vector<long long>(2));  // 只初始化 2 个元素
//     for (auto &item : items) {
//         cin >> item[0] >> item[1];
//     }

//     for (auto &item : items) {
//         long long cur = item[1] / (2 * (-item[0]));
//         long long cost1 = item[0] * cur * cur + item[1] * cur;
//         long long cost2 = item[0] * (cur + 1) * (cur + 1) + item[1] * (cur + 1);
//         if (cost1 > cost2) {
//             item.push_back(cur);
//             item.push_back(cost1);
//             item.push_back(item[0] * cur + item[1]);
//         } else {
//             item.push_back(cur + 1);
//             item.push_back(cost2);
//             item.push_back(item[0] * (cur + 1) + item[1]);
//         }   
//     }

//     sort(items.begin(), items.end(), [](auto &a, auto &b) {
//         // if (a[3] != b[3]) return a[3] > b[3];
//         // else return a[2] < b[2];
//         if (a[4] != b[4]) return a[4] > b[4];
//         else return a[2] < b[2];
//     });

//     // for (auto &item : items) {
//     //     for (auto &x : item) cout << x << " ";
//     //     cout << "\n";
//     // }
//     long long ans = 0;

//     for (int i = 0; i < m; i ++) {
//         if (n >= items[i][2]) {
//             ans += items[i][3];
//             n -= items[i][2];
//         } else if (n != 0){
//             ans += items[i][0] * n * n + items[i][1] * n;
//         }
//     }
//     cout << ans << endl;
// }

// int main() {
//     int n; cin >> n;
//     int m; cin >> m;

//     vector<tuple<int, long long, int>> a;

//     for (int i = 0; i < m; i ++) {
//         long long ki; int bi;
//         cin >> ki >> bi;
//         int count = 1;
//         long long cost = ki * count + bi;
//         while (cost > 0) {
//             a.push_back({count, cost * count, i});
//             count ++;
//             cost = ki * count + bi;
//         } 
//     } 

//     sort(a.begin(), a.end(), [](auto &x, auto &y) {
//         return get<1>(x) > get<1>(y);
//     });

//     // for (auto &[count, cost] : a) {
//     //      cout << count << " " << cost << "\n";
//     // }
//     bool used[m] = {false};

//     long long ans = 0;
//     for (int i = 0; n != 0 && i < a.size(); i ++) {
//         if (n >= get<0>(a[i]) && !used[get<2>(a[i])]) {
//             n -= get<0>(a[i]);
//             ans += get<1>(a[i]);
//             used[get<2>(a[i])] = true;
//         } else {
//             continue;
//         }
//     }
//     cout << ans << "\n";
// }


// int main() {
//     int n, m;
//     cin >> n >> m;
//     priority_queue<tuple<long long, int, int, int>> pq; //收益，行，列，当前选取的数量
//     for (int i = 0; i < m; i ++) {
//         int k, b;
//         cin >> k >> b;
//         pq.emplace(b + k, k, b, 1);
//     }

//     long long ans = 0;

//     while (n --) {
//         auto [delta_price, k, b, x] = pq.top();
//         pq.pop();
//         if (delta_price <= 0) break;

//         ans += delta_price;
//         long long price = 1ll * (b + k * x) * x;
//         long long next_price = 1ll * (b + k * (x + 1)) * (x + 1);
//         pq.emplace(next_price - price, k, b, x + 1);
//     }

//     cout << ans << endl;
// }

// 6.9
// int main() {
//     int days, n;
//     cin >> days >> n;

//     // 单价 保质期 数量
//     vector<vector<int>> chocolates(n, vector<int>(3));
//     for (auto &choc : chocolates) {
//         cin >> choc[0] >> choc[1] >> choc[2];
//     }

//     sort(chocolates.begin(), chocolates.end(), [](auto &a, auto &b) {
//         return a[1] > b[1];
//     });

//     long long cost = 0;
//     using pii = pair<int, int>; //划重点，你就学吧
//     priority_queue<pii, vector<pii>, greater<pii>> pq; //只用存单价
//     int idx = 0;
//     while (days) {
//         while (idx < n && chocolates[idx][1] >= days) {
//             pq.emplace(chocolates[idx][0], chocolates[idx][2]);
//             idx ++;
//         }

//         if (pq.size()) {
//             auto [price, count] = pq.top();
//             pq.pop();
//             cost += price;
//             if (count > 1) {
//                 pq.emplace(price, count - 1);
//             }
//             days --;
//         } else {
//             cout << -1 << "\n";
//             return 0;
//         }
//     }
//     cout << cost << "\n";
// }


//6.10
// int main() {
//     int n,m;
//     cin >> n >> m;
//     // 商品编号， 原始价格， 打折开始日期， 打折结束日期， 折扣率
//     using object = tuple<int, int, int, int, int>;
//     vector<object> goods;

//     int maxD = -1;
//     for (int i = 0; i < m; i ++) {
//         int s, t, p, c; cin >> s >> t >> p >> c;
//         maxD = max(maxD, t);
//         for (int j = 0; j < c; j ++) {
//             int a, b;
//             cin >> a >> b;
//             goods.emplace_back(a, b, s, t, p);
//         }
//     }

//     // for (auto &object : goods) {
//     //     cout << get<0>(object) << " " << get<1>(object) << " " << get<2>(object) << " " << get<3>(object) << " " << get<4>(object) << "\n";
//     // }
//     vector<int> days(maxD + 1, 0); //记录某一天重复出现的次数
//     for (auto &object : goods) {
//         auto [id, price, start, end, discount] = object;
//         days[start]++; days[end + 1]--;
//     }
//     partial_sum(days.begin(), days.end(), days.begin());

//     for (auto &x : days) {
//         cout << x << " ";
//     }

//     // vector<int> off_days;
//     // for (int i = 1; i <= maxD; i ++) {
//     //     if (days[i] >)
//     // }
// }


// int main() {
//     int n, m; cin >> n >> m;

//     vector<tuple<int, int, int, int>> actions; // 时间，折扣信息，商品原价，商品类型
//     vector<multiset<int>> prices(n + 1); // 每种商品的当前价格集合
//     // 数据预处理
//     for (int i = 0; i < m; i ++) {
//         int start, end, discount, cnt;
//         cin >> start >> end >> discount >> cnt;
//         while (cnt--) {
//             int type, baseprice;
//             cin >> type >> baseprice;
//             prices[type].insert(baseprice);
//             actions.emplace_back(start, discount, type, baseprice); // 折扣开始，价格降低
//             actions.emplace_back(end + 1, -discount, type, baseprice); // 折扣结束，价格恢复
//         }
//     }

//     // 遍历统计最小值
//     sort(actions.begin(), actions.end()); // 按时间排序（默认按第一个元素升序）

//     long long total = 0;
//     for (int i = 1; i <= n; i ++) {
//         total += *prices[i].begin(); // 初始总价为每种商品的最低价之和
//     }
//     long long ans = total;

//     for (auto [time, discount, type, baseprice] : actions) {
//         int currentPrice = *prices[type].begin();//当前最低价
//         if (discount > 0) {
//             prices[type].insert( 1ll * baseprice * discount / 100); // 插入折扣价
//         } else {
//             prices[type].erase(prices[type].find(1ll * baseprice * (-discount) / 100)); // 移除折扣价
//         } //multiset 的 erase 只能删除所有相同值，需用 find 定位到具体元素再删除

//         int price = *prices[type].begin();
//         int delta = price - currentPrice;
//         total += delta;
//         ans = min(ans, total);
//     }
//     cout << ans << "\n";
// }


// 7.1
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);

//     int n, m; 
//     cin >> n >> m;
//     vector<int> vec(n);
//     for (auto &x : vec) cin >> x;

//     int target;

//     auto match = [&](int mid) {
//         return vec[mid] >= target;
//     };

//     while (m --) {
//         cin >> target;
//         int idx = get_first_match<int, decltype(match)>(0, n -1, match);
//         cout << (target == vec[idx] ? idx + 1 : -1) << " ";
//     }
// }




// 7.2 
// int main () {
//     cin.tie(0)->sync_with_stdio(false);
//     cout.tie(0)->sync_with_stdio(false);

//     int n, k;
//     cin >> n >> k;
//     vector<int> nums(n);
//     for (auto &x : nums) cin >> x;

//     int lo = *max_element(nums.begin(), nums.end());
//     int hi = accumulate(nums.begin(), nums.end(), 0);

//     vector<int> PartialSum(n);
//     partial_sum(nums.begin(), nums.end(), PartialSum.begin());

//     // for (auto &x: PartialSum) {
//     //     cout << x << " ";
//     // }

//     auto match = [&](int mid) {
//         int l = 0, r = 0;
//         int count = 0;
//         while (r < n) {
//             while (r < n && PartialSum[r] - (l == 0 ? 0 : PartialSum[l - 1]) <= mid) {
//                 r ++;
//             }
//             count ++;
//             l = r;
//         }
//         return count <= k;
//     };

//     int x = get_first_match(lo, hi, match);
//     cout << x << "\n";
// }

//  7.3

// int  main() {
//     cin.tie(0)->sync_with_stdio(false);
//     cout.tie(0)->sync_with_stdio(false);

//     int n; cin >> n;
//     long long  m; cin >> m;
//     vector<int> a(n), b(n);
//     for (auto &x : a) cin >> x;
//     for (auto &x : b) cin >> x;

//     auto match = [&](int mid) {
//         long long cur = 0;
//         for (int i = 0; i < n; i ++) {
//             if (a[i] < mid) {
//                 if (b[i] < mid - a[i]) return true;
//                 cur += mid - a[i];
//             } 

//             if (cur > m) return true;
//         }
//         return false;
//     };

//     int lo = 0;
//     int hi = 1e9;
//     int ans = get_first_match(lo, hi, match);

//     cout << ans - 1 << "\n";
// }

// 7.4

// int main() {
//     int l, n, m;
//     cin >> l >> n >> m;
//     vector<int> stones (n + 2, 0);
//     for (int i = 1; i <= n; i ++) {cin >> stones[i];}
//     stones[n + 1] = l;

//     int lo = 0;
//     int hi = l + 1;
//     auto match = [&](int mid) {
//         int cnt = 0;
//         int interval = 0;

//         for (int i = 1; i < n + 2; i ++) {
//             interval += stones[i] - stones[i - 1];
//             if (interval >= mid) {
//                 interval = 0;
//                 continue;
//             } else {
//                 cnt ++;
//             }
//             if  (cnt > m) return true;
//         }
//         return false;
//     };

//     int ans = get_first_match(lo, hi, match);
//     cout << --ans << "\n";
// }

// 7.5 

// const double eps = 1e-6;
// double lo = -3, hi = 3;
// while (lo + eps < hi) {
//     double mid = (lo + hi) / 2;
//     if (match(mid)) hi = mid;
//     else lo = mid;
// }
// return lo; // 或 hi
// //return hi 也许



// int main() {
//     double a, b, c, d;
//     cin >> a >> b >> c >> d;
//     double lo = -100.0, hi = 100.0;
//     double ans1, ans2, ans3;
//     double eps = 1e-6;

//     while (lo + eps < hi) {
//         double mid = (lo + hi) / 2;
//         double fhi = a * hi * hi * hi + b * hi * hi + c * hi + d;
//         double flo = a * lo * lo * lo + b * lo * lo + c * lo + d;
//         double fmid = a * mid * mid * mid + b * mid * mid + c * mid + d;

//         if (fhi * fmid < 0) {
//             lo = mid;
//         } else if (flo * fmid < 0) {
//             hi = mid;
//         }
//     }
//     ans1 = lo;

//     lo = ans1 + 1;
//     hi = 100.0;
//     while (lo + eps < hi) {
//         double mid = (lo + hi) / 2;
//         double fhi = a * hi * hi * hi + b * hi * hi + c * hi + d;
//         double flo = a * lo * lo * lo + b * lo * lo + c * lo + d;
//         double fmid = a * mid * mid * mid + b * mid * mid + c * mid + d;

//         if (fhi * fmid < 0) {
//             lo = mid;
//         } else if (flo * fmid < 0) {
//             hi = mid;
//         }
//     }
//     ans2 = hi;

//     lo = ans1 + 1;
//     hi = ans2 - 1;
//     while (lo + eps < hi) {
//         double mid = (lo + hi) / 2;
//         double fhi = a * hi * hi * hi + b * hi * hi + c * hi + d;
//         double flo = a * lo * lo * lo + b * lo * lo + c * lo + d;
//         double fmid = a * mid * mid * mid + b * mid * mid + c * mid + d;

//         if (fhi * fmid < 0) {
//             lo = mid;
//         } else if (flo * fmid < 0) {
//             hi = mid;
//         }
//     }
//     ans3 = hi;

//     cout << fixed << setprecision(2) << ans1 << "\n" << ans2 << "\n" << ans3 << "\n";

// }

// // 7.5
// const double eps = 1e-6;
// int main() {
//     cin.tie(0)->sync_with_stdio(false);
//     cout.tie(0)->sync_with_stdio(false);

//     double a, b, c, d;
//     cin >> a >> b >> c >> d;
//     auto f = [&](double x) {
//         return a * pow(x, 3) + b * pow(x, 2) + c * x + d;
//     };

//     vector<double> roots;
//     //处理整数的情况
//     for (int x = -100; x <= 100; x ++) if(abs(f(x)) < eps) roots.push_back(x);


//     for (int x = -100; x <= 99; x ++) {
//         double f1 = f(x);
//         double f2 = f(x + 1);
//         if (f1 * f2 > -eps) continue;
//         double lo = x, hi = x + 1;
//         while (lo + eps < hi) {
//             double mid = (lo + hi) / 2;
//             if (f(mid) * f1 > 0) lo = mid;
//             else hi = mid;
//         }
//         roots.push_back(lo);
//     }

    
//     sort(roots.begin(), roots.end());
//     cout << fixed << setprecision(2);
//     for (auto &x : roots) cout << x << " ";
// }


// 7.6



// int main() {
//     cin.tie(0)->sync_with_stdio(false);
//     cout.tie(0)->sync_with_stdio(false);
//     int n, m, k;
//     cin >> n >> m >> k;

//     vector<int> a(n);
//     vector<int> b(m);
//     for (auto &x : a) cin >> x;
//     for (auto &x : b) cin >> x;
//     sort(a.begin(), a.end());
//     sort(b.begin(), b.end());

//     auto match = [&](int mid) {
//         int cnt = 0;
//         for (auto A: a) {
//             cnt += (upper_bound(b.begin(), b.end(), mid - A) - b.begin());
//         }
//         return cnt >= k; 
//     };

//     int ans = get_first_match(a[0] + b[0], a[n - 1] + b[m - 1], match);
//     cout << ans << "\n";
// }



// 7.7

// int main() {
//     int n, m;
//     cin >> n >> m;
//     vector<int> b(n);
//     priority_queue<pair<int, int>> pq;

//     for (int i = 0; i < n; i ++) {
//         int x; cin >> x;
//         pq.push({x, i});
//         cin >> b[i];
//     }

//     // while(!pq.empty()) {
//     //     cout << pq.top().first << " " << pq.top().second << endl;
//     //     pq.pop();
//     // }

//     // 越大越不可能，所以两极性是反过来的
//     auto match = [&](long long mid) {
//         priority_queue<pair<int, int>> temp_pq = pq;
//         int cnt = 0; long long cur = 0;
//         while(!temp_pq.empty() && cnt < m) {
//             auto [price, idx] = temp_pq.top();
//             temp_pq.pop();
//             cur += price * 1ll; cnt ++;
            
//             if (price - b[idx] > 0) {
//                 temp_pq.push({price - b[idx], idx});
//             }
//         }
//         if (cur <mid) return true;
//         else return false;
//     };

//     long  long ans = get_first_match(0ll, (long long)1e15, match);
//     cout << ans - 1 << "\n";
// }

// int main() {
//     cin.tie(0)->sync_with_stdio(false);
//     cout.tie(0)->sync_with_stdio(false);
//     int n, m;
//     cin >> n >> m;
//     vector<pair<int, int>> skills(n);
//     for (auto &[a, b] : skills) cin >> a >> b;
    
//     auto match = [&](int x) {
//         long long cnt = 0;
//         for (auto &[a, b] :skills) {
//             if (a < x) continue;
//             cnt += (a - x) / b + 1;
//         }
//         return cnt <= m;
//     };
//     int maxSkills = get_first_match(1, 1000000000, match);

//     cout << maxSkills << "\n";

//     long long sum = 0;
//     int totalCnt = 0;
//     for (auto &[a, b] : skills) {
//         if (a < maxSkills) continue;
//         int cnt = (a - maxSkills) / b + 1;
//         sum += (a + (a - (cnt - 1) * b)) * 1ll * cnt / 2;
//         totalCnt += cnt;
//     }

//     if (totalCnt < m) {
//         sum += (long long)(maxSkills - 1) * (m - totalCnt);
//     }
//     cout << sum << "\n";
// }


//7.8

// int main() {
//     cin.tie(0)->sync_with_stdio(false);

//     int A, B, C, m;
//     cin >> A >> B >> C >> m;
//     // 层 列 行
//     auto hp = vector(A + 2, vector(B + 2, vector<int>(C + 2)));
//     for (int i = 1; i <= A; i ++) {
//         for (int j = 1; j <= B; j ++) {
//             for (int k = 1; k <= C; k ++) {
//                 cin >> hp[i][j][k];
//             }
//         }
//     }
//     //每一次攻击用元组存下来
//     vector<tuple<int, int, int, int, int, int, int>> attacks(m);
//     for (auto &[a, b, c, d, e, f, g] : attacks) {
//         cin >> a >> b >> c >> d >> e >> f >> g;
//     }

//     auto match = [&](int mid) {
//         auto diff = vector(A + 2, vector(B + 2, vector<long long>(C + 2)));
//         for (int i = 0; i < mid; i ++) {
//             auto [la, ra, lb, rb, lc, rc, d] = attacks[i];
//             //接下来是三维差分 类比想想一维，左边的加，右边的减
//             // 三个都在左边，加 d
//             diff[la][lb][lc] += d;
//             // 两个在左边，一个在右边，减 d
//             diff[la][lb][rc + 1] -= d;
//             diff[la][rb + 1][lc] -= d;
//             diff[ra + 1][lb][lc] -= d;
//             // 一个在左边，两个在右边，加 d
//             diff[la][rb + 1][rc + 1] += d;
//             diff[ra + 1][lb][rc + 1] += d;
//             diff[ra + 1][rb + 1][lc] += d;
//             // 三个都在右边，减 d
//             diff[ra + 1][rb + 1][rc + 1] -= d;
//         }
//         // 三维前缀和
//         for (int i = 1; i <= A; i ++) {
//             for (int j = 1; j <= B; j ++) {
//                 for (int k = 1; k <= C; k ++) {
//                     diff[i][j][k] += diff[i][j][k-1]
//                                   +  diff[i][j-1][k]
//                                   +  diff[i-1][j][k]
//                                   -  diff[i-1][j-1][k]
//                                   -  diff[i-1][j][k-1]
//                                   -  diff[i][j-1][k-1]
//                                   +  diff[i-1][j-1][k-1];
//                     if (diff[i][j][k] > hp[i][j][k]) return true;
//                 }
//             }
//         }
//         return false;
//     };
//     int ans = get_first_match(1, m, match);
//     cout << ans << endl;
// }

// int main(){
//     // int ans = 0;
//     // auto match =[&](int mid) {return false;};
//     // ans = get_first_match(0, 100, match);
//     // cout << ans << "\n";

//     int n, m;
//     cin >> n >> m;
//     vector<int> rooms(n);
//     for (auto &x : rooms) cin >> x;

//     vector<tuple<int, int, int>> rent(m);
//     for (auto & [d, s, t] : rent) cin >> d >> s >> t;

//     int mid = m / 2;

//     vector<int> diff(n + 1, 0);
//     for (int i = 0; i < mid; i ++) {
//         auto &[d, s, t] = rent[i];
//         diff[s] += d;
//         diff[t + 1] -= d;
//     }
//     partial_sum(diff.begin(), diff.end(), diff.begin());
//     for (auto &x : diff) cout << x << " "; 
// }

// int main() {
//     int  n, m;
//     cin >> n >> m;
//     vector<int> rooms(n);
//     for (auto &x : rooms) cin >> x;

//     vector<tuple<int, int, int>> rent(m);
//     for (auto & [d, s, t] : rent) cin >> d >> s >> t;

//     auto match = [&](int mid) {
//         vector<long long> diff(n + 2, 0); // 差分的小trick 要开大两格，分别在首尾，避免越界
//         for (int i = 0; i < mid; i ++) {
//             auto &[d, s, t] = rent[i];
//             diff[s] += d;
//             diff[t + 1] -= d;
//         }
//         for (int i = 1; i <= n; i ++) { //在尾部开多的那一格在前缀和的时候不用考虑
//             diff[i] += diff[i - 1];
//             if (diff[i] > rooms[i - 1]) return true;
//         }
//         return false;
//     };

//     int ans = get_first_match(0, m, match);
//     if (ans == m + 1) cout << 0 << endl; //注意越界条件，二分找不到的时候（即全false，输出的是m + 1）
//     else cout << -1 << endl << ans << endl;
// }


// //7.10
// int main() {
//     int n, m;
//     long long s;
//     cin >> n >> m >> s;
//     vector<pair<int, int>> stones(n + 1);
//     int maxW = 0;
//     for (int i = 1; i < n + 1; i ++){
//         cin >> stones[i].first >> stones[i].second;
//         maxW = max(maxW, stones[i].first);
//     }
//     vector<pair<int, int>> segs(m);
//     for (auto &[a, b] : segs) cin >> a >> b;

//     auto calc = [&](int w) {
//         vector<int> cnt (n + 1);
//         vector<long long> val (n + 1);
//         for (int i = 1; i <= n; i ++) {
//             cnt[i] = cnt[i - 1] + (stones[i].first >= w);
//             val[i] = val[i - 1] + (stones[i].first >= w) * stones[i].second;
//         }
//         long long total = 0; 
//         for (auto &[l, r]: segs) {
//             total += (cnt[r] - cnt[l - 1]) * (val[r] - val[l - 1]) * 1ll;
//         }
//         return total;
//     };

//     auto match = [&](int mid) {
//         return calc(mid) < s;
//     };

//     int minW = get_first_match(1, maxW, match);

//     long long sub1 = abs(calc(minW) - s);
//     long long sub2 = abs(calc(minW - 1) - s);

//     cout << (sub1 < sub2 ? sub1 : sub2) << "\n";

// }

//7.11

// int main() {
//     long long n, len;
//     cin >> n >> len;
//     vector<pair<int, int>> sges(n);
//     for (auto &[l, s] : sges) cin >> l >> s;

//     auto match = [&](long long mid) {
//         vector<long long> pipe(len + 2, 0);
//         for (auto &[l, s] :sges) {
//             if (mid >= s) {
//                 pipe[max(l - (mid - s), 1ll )] += 1;
//                 pipe[min(l + (mid - s) + 1, len + 1)] -= 1;
//             }  
//         }
//         for (int i = 1; i <= len; i ++) {
//             pipe[i] += pipe[i - 1];
//             if (pipe[i] == 0) return false;
//         }
//         return true;
//     };

//     int ans = get_first_match(1ll, (long long)1000000000, match);
//     cout << ans << endl;
// }



// int main() {
//     cin.tie(0)->sync_with_stdio(false);
//     int n, len;
//     cin >> n >> len;
//     vector<pair<int, int>> pipes(n);
//     for (auto &[x, s] : pipes) cin >> x >> s;

//     auto match = [&](int time) {
//         vector<pair<int, long long>> segs;
//         for (auto &[x, s] :pipes) {
//             int delta = time - s;
//             if (delta < 0) continue;
//             segs.emplace_back(x- delta, x + delta);
//         }
//         sort(segs.begin(), segs.end());
//         long long maxRight = 0;
//         for (auto &[l, r] : segs) {
//             if (l <= maxRight + 1) {
//                 maxRight = max(maxRight, r);
//             } else {
//                 return false;
//             }
//         }
//         return maxRight >= len;
//     };

//     int ans = get_first_match(1, INT_MAX, match);
//     cout << ans << "\n";
// }

// int main() {
//     cin.tie(0)->sync_with_stdio(false);
//     int n, len;
//     cin >> n >> len;
//     vector<pair<int, int>> pipes(n);
//     for (auto &[x, s] : pipes) cin >> x >> s;

//     sort(pipes.begin(), pipes.end(), [](auto &a, auto &b) {
//         return a.first + a.second < b.first + b.second; // 按照 s 升序排序
//     });

//     auto match = [&](int time) {
//         vector<pair<int, long long>> segs;
//         for (auto &[x, s] :pipes) {
//             int delta = time - s;
//             if (delta < 0) continue;
//             segs.emplace_back(x- delta, x + delta);
//         }
//         long long maxRight = 0;
//         for (auto &[l, r] : segs) {
//             if (l <= maxRight + 1) {
//                 maxRight = max(maxRight, r);
//             } else {
//                 return false;
//             }
//         }
//         return maxRight >= len;
//     };

//     int ans = get_first_match(1, INT_MAX, match);
//     cout << ans << "\n";
// }

// 7.12

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
    int n, k, T;
    cin >> n >> k >> T;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    auto match = [&](int mid) {
        vector<int> b(a.begin(), a.begin() + mid);
        sort(b.begin(), b.end());
        vector<long long> sum(mid + 1), sum2(mid + 1);
        for (int i = 1; i <= mid; i ++){
            sum[i] = sum[i - 1] + b[i - 1];
            sum2[i] = sum2[i - 1] + 1ll * b[i - 1] * b[i - 1];
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