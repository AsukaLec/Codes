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
