[TOC]
# <center> 算法思想
## Part 1 枚举
### 一、枚举算法
***
#### 1.1 lq19709 匿名函数&判断奇偶
>一个整数如果按从低位到高位的顺序，奇数位 (个位、百位、万位 ) 上的数字是奇数，偶数位 (十位、千位、十万位) 上的数字是偶数，我们就称之为 “好数”。
给定一个正整数 N,请计算从 1 到 N 一共有多少个好数。 
输入格式 一个整数 N
输出格式 一个整数代表答案。
>> ~~这里是一些格式~~  *不* **要** ***看*** 哦  <mark>very important words</mark>
依旧 
- * - * -
- [x] 111
- [ ] 111
``` c++
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if([](int x){
            for (int index = 1; x; index ^= 1, x /= 10) {
                if (x % 2 != index) return false;
            }
            return true;
        }(i)) cnt++
    }
    cout << cnt << endl;
}
// 要点一： 匿名函数的运用
// 要点二： 快速判断奇数位上的数字是不是奇数（偶数同理）
// index 异或 1 保持 index在 0 和 1 之间跳转， index = 1 - index 也有同样效果
```
***

#### 1.2 lq3491 匿名函数&幸运数
>小蓝认为如果一个数含有偶数个数位，并且前面一半的数位之和等于后面一半的数位之和，则这个数是他的幸运数字。例如2314 是一个幸运数字,因为它有4个数位,并且2+3-1 +4。现在请你帮他计算从1至 100000000之间共有多少个不同的幸运数字。
``` c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int cnt = 0;
    for (int i = 1; i<= 100000000; ++i) {
        int digitcnt = [](int x) { // 要枚举的数的位数
            int cnt = 0;
            for (; x; x /= 10, cnt++);
            return cnt;
        }(i);

        if (digitcnt % 2 = 1 ) continue; //或者 digitcnt & 1 位运算

        if ([](int x, int digitcnt) {
            int half = digitcnt >> 1;//位运算 等效于 /= 2
            int sumLeft = 0, sumRight = 0;
            for (int i = 0; x; x /= 0, i++) {
                if (i < half ) sumLeft += x % 10;
                else sumRight += x % 10;
            }
            return sumLeft = sumRight;
        }(i, digitcnt)) cnt++;
    }
    cout << cnt << endl;
}
```
---

#### 1.3 lq1443 运用vector建立类似字典的效果
>小蓝有很多数字卡片，每张卡斤上都是数字0到9。小蓝准备用这些卡片来拼一些数，他想从1开始拼出正整数每拼一个，就保存起来，卡片就不能用来拼其它数了。
小蓝想知道自己能从 1 拼到多少。例如，当小蓝有 30 张卡片，其中0到9各3张，则小蓝可以并出1到 10，但是拼 11 时卡片 1已经只有一张了，不够拼出 11.现在小蓝手里有 0 到9的卡片各 2021 张，共 20210 张，请司小蓝可以从 1拼到多少?
``` c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> cards(10, 2021);
    for (int i = 1; ; i ++) {
        if ([&](int x){ //[=] 传递的是变量的值 [&] 传递的是变量的引用，可以改表外部变量的值 [] 表示不捕获外部变量
            for (; x; x /= 10) {
                int digit = x % 10;
                if (cards[digit] == 0) return true;
                cards[digit]--;
            }
            return false;
        }(i)) {
            cout << i - 1 << endl;
            break;
        }
    }
}
//总的来说还是暴力算法，但是用了vector减少代码量
```
---


#### 1.4 lq1065 标准化输入&枚举判断
>小蓝有一个数字矩阵，里面只包含数字 0 和 2。小蓝很喜欢 2020，他想找 到这个数字矩阵中有多少个 2020 。 小蓝只关注三种构成2020 的方式：
同一行里面连续四个字符从左到右构成 2020。
同一列里面连续四个字符从上到下构成 2020。
在一条从左上到右下的斜线上连续四个字符，从左上到右下构成 2020。
例如，对于下面的矩阵：
220000
000000
002202
000000
000022
002020
一共有 5 个 2020。其中 1 个是在同一行里的，1 个是在同一列里的，3 个 是斜线上的。
小蓝的矩阵比上面的矩阵要大，如下给出了小蓝的矩阵。(略)

``` c++
#include <bits/stdc++.h>
using namespace std;
//这道题输入十分恶心，输入的小方法记得回看视频。 下面程序中数组用空数组代替。
//还是用枚举

vector<stirng> maze = {};

int main() {
    auto match = [](char a, char b, char c, char d) {
        return a == '2' && b == '2' && c == '2' && d == '2';
    }; //匿名函数，用于判断一个四位数是不是2020，统一了输入格式。

    int cnt = 0 ;// maze.size()返回的是行数，maze[i].size()返回的是列数，具体vector的输入格式可以看test.cpp test 1.4
    for (int i = 0; i < maze.size(); i ++) {
        for (int j = 0; j + 3 < maze[i].size(); j ++) {
            cnt += match(maze[i][j], maze[i][j+1], maze[i][j+2], maze[i][j+3])
        }
    }//行判断

    for (int i = 0; i + 3 < maze.size(); i ++) {
        for (int j = 0; j < maze[i].size(); j ++) {
            cnt += match(maze[i][j], maze[i+1][j], maze[i+2][j], maze[i+3][j])
        }
    }//列判断

    for (int i = 0; i + 3 < maze.size(); i ++) {
        for (int j = 0; j + 3 < maze[i].size(); j ++) {
            cnt += match(maze[i][j], maze[i+1][j+1], maze[i+2][j+2], maze[i+3][j+3])
        }
    }//斜判断
    cout << cnt << endl;
}
```
---

#### 1.5 lq19732 反弹问题 按时间枚举
>有一长方形，长为343720 单位长度，宽为 233333 单位长度。在其内部左上角顶点有一小球 (无视其体积)，其初速度如图所示且保持运动速率不变，分解到长宽两个方向上的速率之比为 dx:dy=15:17。小球碰到长方形的边框时会发生反弹，每次反弹的入射角与反射角相等，因此小球会改变方向且保持速率不变（如果小球刚好射向角落，则按入射方向原路返回）。从小球出发到其第一次回到左上角顶点这段时间里，小球运动的路程为多少单位长度？答案四舍五入保留两位小数。
 <img src="photos\1.5.png" width="50%" height="50%">

!!! ! 反弹问题，理解为镜像镜像原点只会出现在 $(x * 2n_1, y *2n_2)$ ， $n_1,n_2$ 均为自然数 的地方。

``` c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int dx = 15, dy = 17;
    int width = 343720 * 2, height = 233333 * 2;//保证镜像原点符合条件
    for (int t = 1; ; t ++) {
        if (t * dx % width == 0 %% t * dy % height == 0) {
            cout.precision(2);
            cout << fixed;
            cout << hypot(dx * t, dy * t) << endl;//勾股定理函数 
            break;
        }
    }
}
```
---

#### 1.6 lq3495 闰年判断 注意有坑
>记一个日期为yy年mm月dd 日，统计从 2000年1月1日(含)到 2000000年1月1日(含)，有多少个日期满足年份 yy 是月份 mm 的倍数，同时也是 dd 的倍数。
当年份是 4 的倍数而不是 100 的倍数或者年份是 400 的倍数时，这一年是闰年，其他的年份都不是闰年。
``` c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int dayInMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    auto isLeapYear = [](int year) {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    };

    int cnt = 1;//题目年份有个坑，两百万年的时候只有一天
    for (int year = 2000; year < 2000000; year ++) {
        for (int month = 1; month <= 12; ++month) {
            int dayInMonth = dayInMonth[month];
            if (isLeapYear(year) && month == 2) dayInMonth += 1;
            for (int day = 1; day <= dayInMonth; ++day) {
                if (year % month ==0 && year % day == 0) {
                    cnt ++;
                }
            }
        }
    };
    cout << cnt << endl;
}
```
***

#### 1.7 lq3492 子串匹配枚举 有函数可以用
>小蓝现在有一个长度为 100 的数组，数组中的每个元素的值都在 0 到 9的范围之内。数组中的元素从左至右如下所示:
```
5 6 8 6 9 1 6 1 2 4 9 1 9 8 2 3 6 4 7 7 5 9 5 0 3 
8 7 5 8 1 5 8 6 1 8 3 0 3 7 9 2 7 0 5 8 8 5 7 0 9 
9 1 9 4 4 6 8 6 3 3 8 5 1 6 3 4 6 7 0 7 8 2 7 6 8 
9 5 6 5 6 1 4 0 1 0 0 9 4 8 0 9 1 2 8 5 0 2 5 3 3
```
>现在他想要从这个数组中寻找一些满足以下条件的子序列:
1.子序列的长度为 8;
2.这个子序列可以按照下标顺序组成一个yyyymmdd 格式的日期，并且要求这个日期是 2023 年中的某一天的日期，例如 20230902，20231223。yyyy 表示年份mm 表示月份，dd 表示天数，当月份或者天数的长度只有一位时需要一个前导零补充。
请你帮小蓝计算下按上述条件一共能找到多少个不同的 2023年的日期。对于相同的日期你只需要统计一次即可。

!!! ! 思路：先枚举出2023年的每一天，然后把每一天和数组中的数字进行子串匹配枚举 。

``` c++
#include <bits/stdc++.h>
using namespace std;

vector<int> digits = {5,6,8,6,9,1,6,1,2,4,9,1,9,8,2,3,6,4,7,7,5,9,5,0,3,8,7,5,8,1,5,8,6,1,8,3,0,3,7,9,2,7,0,5,8,8,5,7,0,9,9,1,9,4,4,6,8,6,3,3,8,5,1,6,3,4,6,7,0,7,8,2,7,6,8,9,5,6,5,6,1,4,0,1,0,0,9,4,8,0,9,1,2,8,5,0,2,5,3,3};

//子串匹配枚举 
bool subMatch(vector<int> &arr, vector<int> &target) {
    size_t idx = 0; //size_t 是C++标准库中定义的一种无符号整数类型
    for (auto &elem : arr) { //遍历arr中的每一个元素
        if (elem == target[idx]) {
            if (++idx == target.size()) {
                return true;
            }
        }
    }
    return false;
} //好细化 多看 ！！！ 

int main() {
    vector<int> dayInMonthes = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int cnt = 0;
    for (int month = 1; month <= 12; month ++) {
        for (int day = 1; day <= dayInMonthes[month]; ++day) {
            vector<int> target = {2, 0, 2, 3, month/10, month%10, day/10, day%10}; // 巧妙的表示日期的办法
            cnt += subMatch(digits, target);
        }
    }
    cout << cnt << endl;
}
```
***

#### 1.8 lq19730 大模拟 向下取整
>小蓝发现了一个神奇的闹钟，从纪元时间（1970 年 1 月 1 日 
00：00：00）开始，每经过 x 分钟，这个闹钟便会触发一次闹铃 (纪元时间也会响铃)。这引起了小蓝的兴趣，他想要好好研究下这个闹钟。
对于给出的任意一个格式为 уууу-MM-ddHH:mm:ss 的时间，小蓝想要知道在这个时间点之前 (包含这个时间点) 的最近的一次闹铃时间是哪个时间?
注意，你不必考虑时区问题。
输入格式
输入的第一行包含一个整数 T，表示每次输入包含 T 组数据。
接下来依次描述 T 组数据。
每组数据一行，包含一个时间（格式为 уууу-MM-ddHH:mm:ss）和一个整数 x，其中 x 表示闹铃时间间隔（单位为分钟）。
输出格式
输出 T 行，每行包含一个时间（格式为 уууу-MM-ddHH:mm:ss），依次表示每组数据的答案。
对于所有评测用例，1≤T≤10,1≤x≤1000，保证所有的时间格式都是合法的。

```
2
2016-09-07 18:24:33 10
2037-01-05 01:40:43 30

2016-09-07 18:20:00
2037-01-05 01:30:00
```
!!! ! 类似向下取整的感觉
```c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int dayInMonths[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    auto isLeapYear = [](int year) {
        return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
    };
    auto dateToTimestamp = []{int y, int m, int d, int h, int mm, int s} {
        long long res = 0;
        int secondInDay = 24 * 60 * 60;
        for (int i = 1970; i < y; i ++) {
            res += (365 + isLeapYear(i)) * secondInDay;
        }
        for (int i = 1; i < m; i ++) {
            res += (dayInMonth[i] + (i == 2 && isLeapYear(y))) * secondInDay;
        } 
        res += (d - 1) * secondInDay;
        res += h * 60 * 60;
        res += mm * 60;
        res += s;
        return res;
    };
    auto timestampToDate = [](long long  timestamp) {
        int secondInDay = 24 * 60 * 60;
        int s = timestamp % 60;
        int mm = timestamp % 3600 / 60;
        int h = timestamp % (3600 * 24) / 3600 ;
        int days = timestamp / secondInDay;
        
        int y = 1970, m = 1;
        for (;; y ++) {
            int dayInYear = 365 + isLeapYear(y);
            if (days >= dayInYear) days -= dayInYear;
            else break;
        }
        for (;; m++) {
            int dayInMonth = dayInMonths[m] + (m == 2 && isLeapYear(y));
            if (days >= dayInMonth) days -= dayInMonth;
            else break;
        }
        int d = days + 1;
        printf ("%04d-%02d-%02d %02d:%02d:%02d\n", y, m, d, h, mm, s);
    };

    int T;
    cin >> T;
    while(T--) {
        int y, m, d, h, mm, s, x;
        scanf("%d-%d-%d %d:%d:%d %d", &y, &m, &d, &h, &mm, &s, &x)//格式化输入，省的字符串切片大师
        x *= 60;//转化成秒数

        int timestamp = dateToTimestamp(y, m, d, h, mm, s);
        timestamp = timestamp / x * x;//时间戳，取整，实现向下取整
        timestampToDate(Timestamp);
    }
}
```
***

#### 1.9 P1179
>请统计某个给定范围[L,R] 的所有整数中，数字2 出现的次数。
比如给定范围[2,22]，数字2 在数 2 中出现了 1 次，在数 12 中出现 1 次，在数 20 中出现 1 次，在数 21 中出现 1 次，在数 22 中出现 2 次，所以数字 2 在该范围内一共出现了 6 次。
输入格式2 个正整数 L 和 R，之间用一个空格隔开。
输出格式
数字 2 出现的次数。
输入输出样例
输入#1 2 22 输出#1 6
输入#2 2 100 输出#2 20
说明/提示1≤L≤R≤100000。

!!! ! 匿名函数很方便
``` c++
#include <bits/stdc++.h>
using namespace std;

int main(){
    int L,R;
    cin >> L >> R;
    int cnt = 0;
    for (int i = L; i<= R; i++) {
        cnt += [](int x) {
            int ret = 0;
            for (; x; x /= 10) {
                if (x % 10 == 2)ret ++;
            }
            return ret;
        }(i);
    }
    cout << cnt << endl;
}
```
***

#### 1.10 P1149 火柴棒 粗略判断上界
>题目描述
给你 n 根火柴棍，你可以拼出多少个形如 A+B=C 的等式？等式中的 A、B、C 是用火柴棍拼出的整数（若该数非零，则最高位不能是 0）。用火柴棍拼数字 0∼9 的拼法如图所示：a[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}
注意：
加号与等号各自需要两根火柴棍；如果 A≠B，则 A+B=C 与 B+A=C 视为不同的等式（A,B,C≥0）；n 根火柴棍必须全部用上。
输入格式
一个整数n(1≤n≤24)。
输出格式
一个整数，能拼成的不同等式的数目。

!!! ! 粗略判断上界，不然必越界： n <= 24 ,可用于数字的只有20 根，分成三组， 一组极限7根左右。 假设第一组为 1111 （数尽可能大） 后面构造不成立，基本确定 1111 为上界（非上确界）。 1111 用于枚举的边界条件。 
!!! ! 假设算法复杂度异常大，打表 
``` c++
#include <bits/stdc++.h>
using namespace std;

int main() {
    int digits[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}
    auto cnt = [&](int x) {
        if (x == 0) return digits[0];
        int ret = 0;
        for (; x; x /= 10) {
            ret += digits[x % 10];
        }
        return ret; 
    };

    int limit = 1111;
    int n;
    cin >> n;
    n -= 4;
    int ans = 0;

    for (int a = 0; a <= limit; a++) {
        for (int b = 0; b <= limit; b++) {
            int c = b + a;
            if (cnt(a) + cnt(b) == cnt(c)) {
                ans++; 
            }
        }
    }
    cout << ans << endl;
}
```
***
***

### 二、前缀和

#### Lead In
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

#### 前缀和的变种
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

#### 2.1 lq17142 弹珠摆放 iota函数
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

#### 2.2 P5638 城市间寻路 
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

#### 2.3 p2004 领地选择 注意负数 注意二维vector的定义 处理边界问题
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

#### 2.4 接雨水 前置最大值及后缀最大值

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

#### 2.5 lq19717 挖矿 枚举求子区间和的最大值 确定行走方式
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

#### 2.6 lq17110 抓娃娃  记得看数据要求
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

#### 2.7 P9533 区间翻转区间异或和 区间异或和 有结论 见“前缀和的变种” 组合数
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

#### 2.8 lq97 K倍区间 取模 组合数 
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

#### 2.9 P8865 种花  好题 分析何处用前缀和 可以先用暴力的方式写 然后拆分出来
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

#### 2.10 P10429
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
***

### 三、差分
#### Lead In
<mark>快速处理区间加减</mark>
<mark>前缀和的逆运算</mark>
差分往往和前缀和同时出现

$$ 前缀和 \quad s_i =
\left \{
\begin{aligned}
&a_i, &i = 0\\
&a_i + a_{i - 1}, &i > 0
\end{aligned}
\right.
$$

$$ 差分 \quad d_i =
\left \{
\begin{aligned}
&a_i, &i = 0\\
&a_i - a_{i - 1}, &i > 0
\end{aligned}
\right.
$$

**实现方式**
``` cpp
for (int i = n - 1; i >= 0; i --) {
    if ( i == 0) d[i] = a[i];
    else d[i] = a[i] - a[i - 1];
}
//标准库
adjacent_difference(a.begin(), a.end(), d.begin());
```
**推论们**
**1. 前缀和 与 差分 互为逆运算**
```cpp 
1 1 1 1 1
//前缀和
1 2 3 4 5 
// 差分
1 1 1 1 1 //反之亦然
```
**2. $a[l,r] + k \Leftrightarrow d[l] + k, d[r+1] - k $**
``` cpp
 1  2  3  4  5    >> 差分  1   1   1   1   1  -5
+2 +2 +2 +2               +2          -2
 3  4  5  6  5             3   1   1   1  -1  -5  
   -6 -6 -6 -6                -6              +6
 3 -2 -1  0 -1    <<前置和  3  -5   1   1  -1   1  
时间复杂度 O(n * m)        时间复杂度 O(n + m)
```
**3. 二维差分**
``` cpp
//第一种 先对列进行差分 再对行进行差分
auto d = vector(n + 1, vector<int>(m + 1));
for (int i = n; i >= 1; i--) {
    for (int j = m; j >= 1; j--) {
        d[i][j] = a[i][j] - a[i - 1][j];
    }
    adjacent_difference(d[i].begin(), d[i].end(), d[i].begin());
}
```
```cpp
//第二种 d当前元素 减 左 减 上 加 左上
for (int i = m; i >= 1; i--) {
    for (int j = m; j >= 1l j--) {
        d[i][j] = a[i][j] - a[i - 1][j] - a[i][j - 1] + a[i - 1][j - 1]; 
    }
}
```

快速区间加减 
<img src="photos\part 1 差分 1.png" width="100%" height="100%"> 

时间复杂度 $ O(n^2) \rightarrow O(1) $

**4.异或差分及乘法取模差分**
<img src="photos\part 1 差分 2.png" width="100%" height="100%"> 

**5. 有规律的累加 等价于 多重差分**
首先需要观察 两项之差的函数的最高次为几次：
朴素形式 $add_x = a + bx + cx^2 + dx^3 + ...$
经过 最高次 + 1 次差分 得到 一个 常数级的修改方案
<mark>注意 差分数组的项数 要多出差分次数个项</mark>
eg.
<img src="photos\part 1 差分 3.png" width="100%" height="100%"> 
<img src="photos\part 1 差分 4.png" width="100%" height="100%"> 
统一修改 $add_x = a $ 一次差分就够了
等差数列 $add_x = a + bx $ 两次差分
平方数列 $add_x = a + bx + cx^2 $ 三次差分
eg.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    
    vector <int> ans;

    for (int i = 1; i <= 6; ++i) {  
        ans.push_back(a * i * i * i + b * i * i + c * i + d);//更高此数也能实现， 系数问题
    }
    for (int i = 1; i <= 4; ++i) {  
        ans.push_back(0);
    }

    for (int i = 0; i < 10; i ++) {
            cout << ans[i] << ' ' ;    
    }
    cout << endl;

    while (true) {
        int k; 
        cin >> k;
        
        vector <int> ans1(10, 0);
        adjacent_difference(ans.begin(), ans.end(), ans1.begin());
        
        if (k >= 2) {
            while (k-- && k > 0) {
                adjacent_difference(ans1.begin(), ans1.end(), ans1.begin());
                }

            for (int i = 0; i < 10; i ++) {
                cout << ans1[i] << ' ' ;    
                }
            cout << endl;
        }
        else {
            for (int i = 0; i < 10; i ++) {
                cout << ans1[i] << ' ' ;    
                }
            cout << endl;
        }
        
    }
    return 0;
}

// 0 7 2 3
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
```
<mark>所以啊， 对于一组看似无规律的数据 对它使用差分吧 规律可能蕴含在高维空间中</mark>


**6. 差分数组的正负性可以反映原数组的增减性**
<img src="photos\part 1 差分 5.png" width="100%" height="100%"> 
eg.
给定一个数组和目标数组 对数组内任意区间进行加一或减一的操作 问需要多少次操作才能把原数组变为目标数组
<img src="photos\part 1 差分 6.png" width="50%" height="100%"> 
<img src="photos\part 1 差分 7.png" width="100%" height="100%"> 
答案是整数总和和负数总和的绝对值取两者最大值
***

#### 3.1 P9094 差分模板
**题目描述**
Byteasar 正准备给栅栏涂漆。他已经准备了 $n$ 罐白色油漆，他把这些油漆排列成一排，从 $1$ 到 $n$ 编号。他想用这些油漆，但他不想把栅栏涂成白色。他委托了调色专家，调色专家有三种颜料：黄色、蓝色和红色。专家进行了 $m$ 次操作，其中第 $i$ 次操作是向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的所有罐子中加入某种颜料。

油漆的最终颜色取决于被添加到其中的颜料。添加的颜料按照下表和图示进行混合。

|        颜料        | 颜色 |
| :----------------: | :--: |
|         无         | 白色 |
|        黄色        | 黄色 |
|        蓝色        | 蓝色 |
|        红色        | 红色 |
|    黄色 + 蓝色     | 绿色 |
|    黄色 + 红色     | 橙色 |
|    蓝色 + 红色     | 紫色 |
| 黄色 + 蓝色 + 红色 | 棕色 |

![](https://cdn.luogu.com.cn/upload/image_hosting/zow92g6w.png)

Byteasar 想要给栅栏涂成一种颜色。思来想去，他选择了绿色，因为绿色代表了你常会在算法竞赛中看到的 Accepted。他想知道现在有多少罐油漆是绿色的，请帮他数数。

**输入格式**

第一行两个整数 $n,m$，分别表示油漆的罐数和专家进行的操作数。

接下来 $m$ 行，每行三个整数 $l_i,r_i,k_i$，表示在第 $i$ 次操作中向编号在 $l_i$ 到 $r_i$ 之间（包括两端）的罐子中加入颜料。加入的颜料是黄色（$k_i=1$），蓝色（$k_i=2$）或红色（$k_i=3$）中的一种。

**输出格式**

输出一行一个整数，表示在所有操作之后绿色油漆的罐数。

**输入输出样例 #1**
**输入 #1**

```
9 5
2 8 1
4 5 2
6 7 3
5 6 2
1 2 2
```
**输出 #1**

```
3
```

**样例 1 解释**

操作结束后，这些油漆分别是蓝色、绿色、黄色、绿色、绿色、棕色、橙色、黄色和白色的。因此，只有三罐油漆是绿色。

**数据范围**
对于 $100\%$ 的数据，保证 $1\le n,m\le 10^6$，$1\le l_i\le r_i\le n$，$1\le k_i\le 3$。

!!! : 二编： 本体符合 “快速对一个区间内的数进行加减运算”的特征，故需用到差分 

!!! : 本题用到的是推论二，若按题意暴力枚举判断会导致时间复杂度过高， 用差分可把修改的过程改为 $O(1) $

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    auto colors = vector(3, vector<int>(n + 2));
    while(m -- ) {
        int l, r, c;
        cin >> l >> r >> c;
        colors[c - 1][l] ++;
        colors[c - 1][r + 1] --;
    }
    for (auto &color : colors ) {
        partial_sum(color.begin(), color.end(), color.begin());
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (colors[0][i] && colors[1][i] && !colors[2][i]) ans ++;
    }
    cout << ans;
}
```

---

#### 3.2 lq 3533 棋盘 二维差分模板
**问题描述**
小蓝拥有 $ n×n $ 大小的棋盘，一开始棋盘上全都是白子。小蓝进行了$m$ 次操作，每次操作会将棋盘上某个范围内的所有棋子的颜色取反（也就是白色棋子变为黑色，黑色棋子变为白色）。请输出所有操作做完后棋盘上每个棋子的颜色。

**输入格式**
输入的第一行包含两个整数 n，m，用一个空格分隔，表示棋盘大小与操作数。
接下来 m 行每行包含四个整数 
$x_1, y_1, x_2, y_2$
 ，相邻整数之间使用一个空格分隔，表示将在
$x_1 $至 $x_2 $行,$ y_1 $至 $y_2$列中的棋子颜色取反。

**输出格式**
输出 n 行，每行 
n 个 0 或 1 表示该位置棋子的颜色。如果是白色则输出 0，否则输出 1。

**样例输入**
```
3 3
1 1 2 2
2 2 3 3
1 1 3 3
```
**样例输出**
```
001
010
100
```
**评测用例规模与约定**
对于 30% 的评测用例， $n,m \leqslant 50$
对于 所有评测用例， $1 \leqslant n,m \leqslant 2000, 1 \leqslant x_1 \leqslant x_2 \leqslant n, 1 \leqslant y_1 \leqslant y_2 \leqslant m $

!!! : <img src="photos\part 1 差分 1.png" width="100%" height="100%">每次翻转为原来的数组都加上1， 最后判断奇偶即可判断正反。

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    auto maze = vector(n + 2, vector(n + 2, 0));
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        maze[x1][y1]++;
        maze[x1][y2+1]--;
        maze[x2+1][y1]--;
        maze[x2+1][y2+1]++;
    }//见上图

    for (int i = 1; i <= n; i++ ) {
        partial_sum(maze[i].begin(), maze[i].end(), maze[i].begin());//形式一
        for (int j = 1; j <= n; j ++) {
            maze[i][j] += maze[i -1][j];//形式二
            cout << (maze[i][j] & 1);//快速判断奇偶性， 至于为什么是奇偶，前面每次操作加的都是一
        }
        cout << endl;
    }
}

```
---

#### 3.3 lq 2128 重新排序  关注如何对区间进行排序以及匹配
**问题描述**
给定一个数组 $A$ 和一些查询 $L_i, R_i$, 求数组中第$L_i$ 至第 $R_i$ 个元素之和。
小蓝觉得这个问题很无聊, 于是他想重新排列一下数组, 使得最终每个查 询结果的和尽可能地大。小蓝想知道相比原数组, 所有查询结果的总和最多可以增加多少?

**输入格式**
输入第一行包含一个整数 n 。
第二行包含 n 个整数 $A_1,A_2,⋯,A_n​$, 相邻两个整数之间用一个空格分隔。
第三行包含一个整数 m 表示查询的数目。
接下来 m 行, 每行包含两个整数 $L_i、R_i$, 相邻两个整数之间用一个空格分 隔。

**输出格式**
输出一行包含一个整数表示答案。

**样例输入**
```
5
1 2 3 4 5
2
1 3
2 5
```

**样例输出**
```
4
```

**样例说明**
原来的和为 6+14=20, 重新排列为 (1,4,5,2,3) 后和为 10+14=24, 增 加了 4。

!!! ： 初始思路：先对原数组进行排序。某个位置重复计算的次数越多，就给这个位置填上尽可能大的数(<mark>主要优化点</mark>)。 计算某个位置的重复计算次数， 先进行m次差分， 最后进行一次前缀和。
!!! : 正确思路 :前半部分相同， 填数字的地方， 对目标数组也进行排序，然后和排好序的原数组一一相乘即可 。 至于怎么求没排序前的和， 输入的时候顺手用前缀和运算即可。

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n;
    vector<long long > a(n);
    for (auto & x : a) cin >> x;
    vector<long long > sum (n + 1);
    partial_sum(a.begin(), a.end(), sum.begin() + 1);

    cin >> m;
    long long total = 0; //未排序前的区间和
    vector<long long> diff (n + 2);
    while (m--) {
        int l, r;
        cin >> l >> r;

        diff[l] ++;
        diff [r + 1]--;

        total += sum[r] - sum[l - 1];
    }
    partial_sum(diff.begin(), diff.end(), diff.begin());
    sort(diff.begin(), diff.end(), greater<long long>());
    //当传入greater<T>时，会按**降序（从大到小）**排列元素。
    //若未指定第三个参数，默认行为相当于传递了 less<T>()，结果为升序。
    sort(a.begin(), a.end(), greater<long long>());

    long long ans = 0;
    for (int i = 0; i < n; i ++) {
        ans += a[i] * diff[i];
    }
    cout << ans - total << endl;  
}
```
---

#### 3.4 lq 197716 商品库存管理 范围函数快速输入， 数字特征， partial_sum函数的花活

**问题描述**
在库存管理系统中，跟踪和调节商品库存量是关键任务之一。小蓝经营的仓库中存有多种商品，这些商品根据类别和规格被有序地分类并编号，编号范围从 \(\mathbf{1}\) 至 \(\mathbf{n}\) 。初始时，每种商品的库存量均为 \(\mathbf{0}\) 。
为了高效地监控和调整库存量，小蓝的管理团队设计了 \(\mathbf{m}\) 个操作，每个操作涉及到一个特定的商品区间，即一段连续的商品编号范围（例如区间 \(\mathbf{[L, R]}\) ）。执行这些操作时，区间内每种商品的库存量都将增加 \(\mathbf{1}\) 。然而，在某些情况下，管理团队可能会决定不执行某些操作，使得这些操作涉及的商品区间内的库存量不会发生改变，维持原有的状态。
现在，管理团队需要一个评估机制，来确定如果某个操作未被执行，那么最终会有多少种商品的库存量为 \(\mathbf{0}\) 。对此，请你为管理团队计算出，每个操作未执行时，库存量为 \(\mathbf{0}\) 的商品的种类数。

**输入格式**
第一行包含两个整数 \(\mathbf{n}\) 和 \(\mathbf{m}\) ，分别表示商品的种类数和操作的个数。
接下来的 \(\mathbf{m}\) 行，每行包含两个整数 \(\mathbf{L}\) 和 \(\mathbf{R}\) ，表示一个操作涉及的商品区间。

**输出格式**
输出共 \(\mathbf{m}\) 行，每行一个整数，第 \(\mathbf{i}\) 行的整数表示如果不执行第 \(\mathbf{i}\) 个操作，则最终库存量为 \(\mathbf{0}\) 的商品种类数。

**样例输入**
```
5 3
1 2
2 4
3 5
```
**样例输出**
```
1
0
1
```

**样例说明**
考虑不执行每个操作时，其余操作对商品库存的综合影响：
- 不执行操作 1：剩余的操作是操作 2（影响区间 \(\mathbf{[2, 4]}\)）和操作 3（影响区间 \(\mathbf{[3, 5]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[0, 1, 2, 2, 1]}\)。在这种情况下，只有编号为 \(\mathbf{1}\) 的商品的库存量为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{1}\)。
- 不执行操作 2：剩余的操作是操作 1（影响区间 \(\mathbf{[1, 2]}\)）和操作 3（影响区间 \(\mathbf{[3, 5]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[1, 1, 1, 1]}\)。在这种情况下，所有商品的库存量都不为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{0}\)。
- 不执行操作 3：剩余的操作是操作 1（影响区间 \(\mathbf{[1, 2]}\)）和操作 2（影响区间 \(\mathbf{[2, 4]}\)）。执行这两个操作后，商品库存序列变为 \(\mathbf{[1, 2, 1, 0]}\)。在这种情况下，只有编号为 \(\mathbf{5}\) 的商品的库存量为 \(\mathbf{0}\)。因此，库存量为 \(\mathbf{0}\) 的商品种类数为 \(\mathbf{1}\)。

**评测用例规模与约定**
对于 \(\mathbf{20\%}\) 的评测用例，\(\mathbf{1 \leq n, m \leq 5 \times 10^3}\)，\(\mathbf{1 \leq L \leq R \leq n}\)。
对于所有评测用例，\(\mathbf{1 \leq n, m \leq 3 \times 10^5}\)，\(\mathbf{1 \leq L \leq R \leq n}\)。

!!! : 看到 “都加一” 明显差分。 关键在于，每个不执行操作如何实现。 假设所有操作次数为 $k$ ，得到相应的差分数组后，对于第 $i$ 次操作， 在对应的区间加上 -$1$ 即可。但这样时间复杂度为 $O(n*m)$, 需优化。

!!! : 观察数字特征。 对于任意操作过的区间， 其前缀和之后的值一定是大于0的。若要不操作某个区间使得某个位置的库存变为0， 那么该位置的值在进行全部操作后必定为1。 所以只需要在目标区间统计值为 1 的个数即可。同时， 不能排除剩余区间有 0 存在的情况， 故须在进行过所有操作的数组中先统计一遍 0 的个数。 又因为若某个区间经历了操作， 其不可能为0，所以可以放心不会出现重复。

!!! : partial_sum函数的用法关注一下
``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> range (m);
    vector<long long> cnt(n + 2);
    for (auto &[f, s] : range ) {
        cin >> f >> s;
        cnt[f] ++;
        cnt[s + 1] --;
    }//范围循环快速输入
    partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    vector<int> ones(n + 2);
    int zero = 0;
    partial_sum(cnt.begin(), cnt.end() - 1, ones.begin(), [&](int prev, int cur) {
        if (cur == 0) zero ++;
        if (cur == 1) return prev + 1;
        return prev;
    });// cnt.end() - 1: 最后一个位置不需要计数。
    //这个函数用for 循环也是能写的。
    // prev cur 都是partial_sum这个函数下的一个参数位置， 分别代表前一次累加返回的值以及当前要处理的值。
    //return 的即是要存到 ones这个前缀和数组特定位置的值
    for (auto &[f, s] : range) {
        cout << ones[s] - ones[f - 1] + zero << endl;
    }
}
```

---

#### 3.5 经典题
<img src="photos\part 1 3.5 题目.png" width="100%" height="100%">

!!! : 初始想法： 先不管矩阵 0 1的分布， 暴力往上放尽可能多的邮票，然后从中抽取任意张邮票直至满足条件。 这个就有点像 3.4 只不过一次 的 不操作改成了任意次的不操作
!!! : 优化： 优化放邮票的策略。 先对原矩阵进行一次二维前缀和， 然后放邮票之前， 先判断该区间内有无 被占据的格子， 顺便差分 把可以放的格子加一， 最后再来一次前缀和统计是不是所有空格子都被占据了。
``` cpp
#include <bitsa/stdc++.h>
using namespace std;
int main() {
    int h, w;
    int grid[n][m];
    auto sum = vector (n + 2, vector(m + 2, 0));
    for (int i = 0; i <   n; i++) {
        partial_sum(grid[i].begin(), grid.end(), sum[i + 1].begin() + 1);
        for (int j = 1; j <= m; j ++) {
            sum[i + 1][j] += sum[i][j];

        }
    }
    // 注意坐标偏移
    
    auto diff = vector (n + 2, vector(m + 2, 0));
    for (int i = 0; i + h <= n; i ++) {
        for (int j = 0; j + w <= m; j ++ ) {
            int v = sum [i + h][j + w] - sum[i + h][j] - sum[i][j + w] + sum[i][j];
            if (v == 0) {
                diff [i + 1][j + 1] ++;
                diff [i + 1][j + w + 1] --;
                diff [i + h + 1][j + 1] --;
                diff [i + h + 1][j + w + 1] ++;

            }
        }
    }
    for (int i =0; i < diff.size(); i ++ ) {
        partial_sum(diff[i].begin(), diff[i].end(), diff[i].begin());
        for(int j = 0; j < diff[i].size(); j ++) { 
            if (i) diff[i][j] += diff [i - 1][j];
        }
    }//处理

    //判断是否成立
    for (int i = 0; i < n; i ++ ) {
        for (int j = 0; j < m; j ++ ) {
            if (grid[i][j] == 0 && diff[i + 1][j + 1] == 0) return false;
        }
    }
    return true;
}
```
---

#### 3.6 P4231 三步必杀 推论5 有规律的累加
**题目描述**
$N$ 个柱子排成一排，一开始每个柱子损伤度为 $0$。
接下来勇仪会进行 $M$ 次攻击，每次攻击可以用 $4$ 个参数 $l,r,s,e$ 来描述：
表示这次攻击作用范围为第 $l$ 个到第 $r$ 个之间所有的柱子(包含 $l,r$)，对第一个柱子的伤害为 $s$，对最后一个柱子的伤害为 $e$。
攻击产生的伤害值是一个等差数列。若 $l=1,r=5,s=2,e=10$，则对第 $1 \sim 5$ 个柱子分别产生 $2,4,6,8,10$ 的伤害。
鬼族们需要的是所有攻击完成之后每个柱子的损伤度。

**输入格式**
第一行 $2$ 个整数 $N,M$，用空格隔开，下同。
接下来 $M$ 行，每行4个整数 $l,r,s,e$，含义见题目描述。
数据保证对每个柱子产生的每次伤害值都是整数。

**输出格式**
由于输出数据可能过大无法全部输出，为了确保你真的能维护所有柱子的损伤度，只要输出它们的异或和与最大值即可。
（异或和就是所有数字按位异或起来的值。）
（异或运算符在 c++ 里为 `^`。）

**输入输出样例 #1**

**输入 #1**

```
5 2
1 5 2 10
2 4 1 1
```
**输出 #1**

```
3 10
```

** 输入输出样例 #2**

** 输入 #2**

```
6 2
1 5 2 10
2 4 1 1
```

**输出 #2**

```
3 10
```

**说明/提示**

**样例解释：**

样例 $1$：

第一次攻击产生的伤害：$2,4,6,8,10$。

第二次攻击产生的伤害：$0,1,1,1,0$。

所有攻击结束后每个柱子的损伤程度：$2,5,7,9,10$。

输出异或和与最大值，就是 $3,10$。

样例 $2$：

没有打到第六根柱子，答案不变

**数据范围：**

本题满分为 $100$ 分，下面是 $4$ 个子任务。(x/y)表示(得分/测试点数量)。

妖精级(18/3)：$1 \  n,m \le 1000$。这种工作即使像妖精一样玩玩闹闹也能完成吧？

河童级(10/1)：$s=e$，这可以代替我工作吗？

天狗级(20/4)：$1 \le n,m \le 10^5$。小打小闹不再可行了呢。

鬼神级(52/2)：没有特殊限制。要真正开始思考了。

以上四部分数据不相交。

对于全部的数据：$1\le n\le 10^7$，$1\le m\le 3\times 10^5$，$1\le l < r \le n$.

所有输入输出数据以及柱子受损伤程度始终在 $[0,9 \times 10^{18}]$ 范围内。

**提示：**

由于种种原因，时间限制可能会比较紧，c++ 选手请不要使用 `cin` 读入数据。

by orangebird。

!!! : 等差数列很容易联想到推论五， 至于题目中的异或和和最大值用系统库函数即可。
``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> diff(n + 3);
    while (m --) {
        int l, r, s, e;
        cin >> l >> r >> s >> e;
        int d = (e - s) / (r - l);
        diff[l] += s;
        diff[l + 1] += d - s;
        diff[r + 1] -= e + d;
        diff[r +2] += e;
    }
    partial_sum(diff.begin(), diff.end(), diff.begin());
    partial_sum(diff.begin(), diff.end(), diff.begin());

    cout << accumulate(diff.begin(), diff.end(), 0ll, [](long long prev, long long cur) {return prev ^ cur; });
    //求和函数 匿名函数
    cout << ' ' << *max_element(diff.begin(), diff.end());

}
```
---

#### 3.7 P10266 高效清理 有规律累加 三次差分 二维矩阵分对角线处理 样例题
 
**题目描述**
真寻的房间太大了，但是作为家里蹲，她又懒得打扫，于是美波里发明了一款清理炸弹给真寻使用。

真寻的房间由 $n$ 行 $m$ 列的方砖组成，第 $i$ 行第 $j$ 列的方砖上的灰尘数量为 $a_{i,j}$。

真寻将会使用 $k$ 次清理炸弹，第 $i$ 次她会在第 $x_i$ 行第 $y_i$ 列的方砖上使用能量值为 $p_i$ 的清理炸弹，这将会使 $(x_i,y_i)$ 的灰尘数量减少 ${p_i}^2$，$(x_i,y_i)$ 外围第一圈的方砖上的灰尘数量减少 $(p_i-1)^2$，外围第二圈的方砖上的灰尘数量减少 $(p_i-2)^2$ $\cdots$ 外围第 $(p_i-1)$ 圈的方砖上的灰尘数量减少 $1$。

当然，灰尘数量不能为负数，所以若某次操作前，某块方砖上的灰尘数量小于它将要减少的灰尘数量，那么它的灰尘数量将变为 $0$。

请你输出真寻使用完 $k$ 次清理炸弹后，每块方砖上的灰尘数量。

**输入格式**
第一行三个整数 $n,m,k$，分别表示方砖行数、列数及操作次数；

接下来 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示 $a_{i,j}$，描述每一块方砖上的灰尘数量；

接下来 $k$ 行，第 $i$ 行三个整数 $x_i,y_i,p_i$，描述一次操作。

**输出格式**
共 $n$ 行，每行 $m$ 个整数，第 $i$ 行第 $j$ 列的整数表示方砖 $(i,j)$ 上最终的灰尘数量。


**输入输出样例 #1**

**输入 #1**
```
4 5 2
7 5 4 6 5
2 4 7 9 5
6 4 5 3 5
1 2 3 0 7
2 4 2
3 3 2
```

**输出 #1**
```
7 5 3 5 4
2 3 5 4 4
6 3 0 1 4
1 1 2 0 7
```

**输入输出样例 #2**
**输入 #2**
```
6 7 3
6 4 7 8 4 6 1
4 5 4 6 7 5 9
1 4 3 0 7 1 3
4 6 0 7 9 0 0
1 2 3 4 4 5 8
4 7 6 8 7 4 9
5 5 3
2 3 4
3 6 2
```

**输出 #2**

```
2 0 0 0 0 5 1 
0 0 0 0 2 3 8 
0 0 0 0 1 0 1 
0 2 0 0 0 0 0 
0 1 1 0 0 0 7 
4 7 5 4 3 0 8
```

**说明/提示**

**样例** $\mathbf{1}$ **解释**

第一次操作在方砖 $(2,4)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(2,4)$ 的灰尘数量减少 $4$，$(1,3),(1,4),(1,5),(2,3),(2,5),(3,3),(3,4),(3,5)$ 的灰尘数量减少 $1$；

第二次操作在方砖 $(3,3)$ 上使用能量值为 $2$ 的“清理炸弹”，使 $(3,3)$ 的灰尘数量减少 $4$，$(2,2),(2,3),(2,4),(3,2),(3,4),(4,2),(4,3),(4,4)$ 的灰尘数量减少 $1$。

**数据范围**

对于所有数据，$1\leq n,m,p_i\leq 10^3$，$1\leq k\leq 10^6$，$0\leq a_{i,j}\leq 10^{12}$，$1\leq x_i\leq n$，$1\leq y_i\leq m$。

本题共 $11$ 个数据点，**采用捆绑测试**，子任务及数据点分配如下：

| 子任务编号 | 数据点编号 | 特殊性质 | 分值 |
| :-: | :-: | :-: | :-: |
| $0$ | $1\sim 4$ | $n,m,k\leq 300$ | $10$ |
| $1$ | $5$ | $p_i\leq 3$ | $10$ |
| $2$ | $6\sim 7$ | $k\leq 10^3$ | $20$ |
| $3$ | $8\sim 9$ | $n,m\leq 300$ | $20$ |
| $4$ | $10\sim 11$ | 无特殊限制 | $40$ |

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios :: sync_with_stdio(false);
    //解绑 scanf 缩短时间
    cin.tie(0);

    const int N = 3000 + 10;
    int offset = 1000 +5;

    int n, m, k;
    cin >> n >> m >> k;

    auto origin = vector(n, vector<long long> (m));
    for (auto & row : origin) {
        for (auto & x : row) cin >> x;
    }//输入   

    //对角线分割
    auto diag = vector(N, vector<long long> (N));
    auto back_diag = vector(N, vector<long long> (N));

    while (k --) {
        int x, y, p;
        cin >> x >> y >>p;
        x += offset;
        y += offset;

        diag[x+1][y+1] -= 2;
        diag[x+2][y+2] -= 2;
        diag[x-p+1][y-p+1] += 1;
        diag[x-p+2][y-p+2] += 1;
        diag[x+p+1][y+p+1] += 1;
        diag[x+p+2] [y+p+2]+= 1;

        back_diag[x+1][y] += 2;
        back_diag[x+2][y - 1] += 2;
        back_diag[x+1+p][y-p] -= 1;
        back_diag[x+2+p][y-p-1] -= 1;
        back_diag[x+1-p][y+p] -= 1;
        back_diag[x+2-p][y+p-1] -= 1;
        // 0 0 0 0 0 0 0 0 0 
        // 0 1 1 1 1 1 1 1 0
        // 0 1 4 4 4 4 4 1 0
        // 0 1 4 9 9 9 4 1 0
        // 0 1 4 9 16 9 4 1 0 **y
        // 0 1 4 9 9 9 4 1 0
        // 0 1 4 4 4 4 4 1 0
        // 0 1 1 1 1 1 1 1 0
        // 0 0 0 0 0 0 0 0 0
        //         *x
        // 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0
        // 0 0 3 0 0 0 0 0 0
        // 0 0 0 5 0 0 0 0 0
        // 0 0 0 0 7 0 0 0 0 **y
        // 0 0 0 0 0 7 0 0 0
        // 0 0 0 0 0 0 5 0 0
        // 0 0 0 0 0 0 0 3 0
        // 0 0 0 0 0 0 0 0 1
        //         *x
        // 0 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0 0
        // 0 0 2 0 0 0 0 0 0 0
        // 0 0 0 2 0 0 0 0 0 0
        // 0 0 0 0 2 0 0 0 0 0**y
        // 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 -2 0 0 0
        // 0 0 0 0 0 0 0 -2 0 0
        // 0 0 0 0 0 0 0 0 -2 0
        // 0 0 0 0 0 0 0 0 0 -1
        //         *x
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 1 0 0 0 0 0 0 0 0 0
        // 0 0 1 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0**y
        // 0 0 0 0 0 -2 0 0 0 0 0
        // 0 0 0 0 0 0 -2 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 0 0
        // 0 0 0 0 0 0 0 0 0 1 0
        // 0 0 0 0 0 0 0 0 0 0 1
        //         *x
    }

    //两个差分函数 特例化
    auto diag_sum = [&](auto &diag) {
        for (int i = 1; i < diag.size(); i ++) {
            for (int j = 1; j < diag.size(); j ++) {
                diag[i][j] += diag[i - 1][j - 1];
            }
        }
    };

    auto back_diag_sum = [&](auto &diback_diagag) {
        for (int i = 1; i < back_diag.size(); i ++) {
            for (int j = back_diag.size() - 1; j > 0; j --) {
                back_diag[i][j] += back_diag[i - 1][j + 1];
            }
        }
    };

    //平方数列 两次调用
    diag_sum(diag);
    diag_sum(diag);
    back_diag_sum(back_diag);
    back_diag_sum(back_diag);

    auto total = vector(N, vector(N, 0ll));
    for (int i = 0; i < N; i ++) {
        for (int j = 0; j < N; j ++) {
            total[i][j] = diag[i][j] + back_diag[i][j];
        }
    }

    for (int i = 0; i < N; i ++) {
        partial_sum(total[i].begin(),total[i].end(), total[i].begin());
        for (int j = 0; j < N; j ++) {
            total[i][j] = total[i - 1][j];
        }
    }

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            origin[i][j] -= total[i + 1 + offset][j + 1 + offset];
            if (origin[i][j] < 0) origin[i][j] = 0;
            cout << origin[i][j] << ' ';
        }
        cout << endl;
    }
}
```

#### 3.8 P4552 [Poetize6] IncDec Sequence 经典题 推论六

**题目描述**

给定一个长度为 $n$ 的数列 ${a_1,a_2,\cdots,a_n}$，每次可以选择一个区间$[l,r]$，使这个区间内的数都加 $1$ 或者都减 $1$。 
  
请问至少需要多少次操作才能使数列中的所有数都一样，并求出在保证最少次数的前提下，最终得到的数列有多少种。

**输入格式**

第一行一个正整数 $n$   
接下来 $n$ 行,每行一个整数,第 $i+1 $行的整数表示 $a_i$。

**输出格式**

第一行输出最少操作次数   
第二行输出最终能得到多少种结果

**输入输出样例 #1**

**输入 #1**

```
4
1
1
2
2
```

**输出 #1**

```
1
2
```

**说明/提示**

对于 $100\%$ 的数据，$n\le 100000, 0 \le a_i \le 2^{31}$。

!!! : 第一版： 前半部分是对的， 第二部分错误

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int k;
    cin >> k;
    vector <int> maze;
    for (int i = 0; i < k; i ++) {
        long long a;
        cin >> a;
        maze.push_back(a);
    }

    auto max_val = *max_element(maze.begin() + 1, maze.end());
    auto min_val = *min_element(maze.begin() + 1, maze.end());


    adjacent_difference(maze.begin(), maze.end(), maze.begin());

    long long pos = 0, neg = 0;

    for (int i = 1; i < k; i ++) {
        if (maze[i] > 0) pos += maze[i];
        else neg  += - maze[i];
    }


    long long op = max(pos, neg);
    long long posible =  (min_val + op) - (max_val - op) + 1;

    cout << op << endl;
    cout << posible << endl;
}
```

!!! :第二部分实际上要处理的应该是差分数组除去第一位， 正数之和减去负数之和的绝对值再加 1， 原理见下, 所有的差分数组通过加减都能化为以下的形式“1”。

``` cpp
[1, 1, 2, 2]
[x, 0, 1, 0, x]
[1,   -1]
      [1    -1]

```
!!! : AC版

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int k;
    cin >> k;
    vector <int> maze;
    // for (int i = 0; i < k; i ++) {
    //     long long a;
    //     cin >> a;
    //     maze.push_back(a);
    // }
    for (auto & x : maze) cin >> x;

    adjacent_difference(maze.begin(), maze.end(), maze.begin());

    long long pos = 0, neg = 0;

    for (auto & x : maze) {
        if (x > 0) pos += x;
        else neg  += - x;
    }

    long long posible =  abs(pos + neg) + 1;

    cout << max(pos, neg) << endl;
    cout << posible << endl;
}
```
---

#### 3.9 P6070 『MdOI R1』Decrease 推论 6 二维化

**题目描述**

给定一个 $n \times n$ 的矩阵，你可以进行若干次操作。

每次操作，你可以将一个 $k \times k$ 的 **连续** 子矩阵里的所有数全都加上 $1$ 或者全都减去 $1$。

初始时，矩阵中有 $m$ 个位置上的数不为 $0$，其它位置上的数均为 $0$。

请你求出至少需要多少次操作，可以将矩形中所有数都变为 $0$。

**输入格式**

第一行三个整数 $n,m,k$，分别表示矩阵大小，非 $0$ 格数和每次修改的连续子矩阵大小。

接下来 $m$ 行，每行三个整数 $x,y,z$，表示初始时矩阵的第 $x$ 行第 $y$ 列上的数为 $z$。

**输出格式**

一行一个整数，表示最少操作次数。

特别地，如果无法使矩阵中所有数都变为 $0$，输出 `-1`。

**输入输出样例 1**

**输入 1**

```
4 14 3
1 1 1
1 2 1
1 3 1
2 1 1
2 2 3
2 3 3
2 4 2
3 1 1
3 2 3
3 3 3
3 4 2
4 2 2
4 3 2
4 4 2
```

**输出 1**

```
3
```

**输入输出样例 2**

**输入 2**

```
3 1 2
1 1 1
```

**输出 2**

```
-1
```

**输入输出样例 3**

**输入 3**

```
4 5 1
1 1 5
2 2 -3
2 3 -4
3 3 1
4 4 2
```
**输出 3**

```
15
```

**说明/提示**

【样例 1 解释】:  

给出的矩阵为：  

```plain
1 1 1 0
1 3 3 2
1 3 3 2
0 2 2 2
```

具体步骤：  

先将以第一行第一列为左上角的连续子矩阵执行 **减 1 操作** 一次；

再将以第二行第二列为左上角的连续子矩阵执行 **减 1 操作** 两次。

总共三次。

```plain
1 1 1 0  0 0 0 0  0 0 0 0  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
1 3 3 2  0 2 2 2  0 1 1 1  0 0 0 0
0 2 2 2  0 2 2 2  0 1 1 1  0 0 0 0
```

【样例 2 解释】：  

给出的矩阵为：  

```plain
1 0 0
0 0 0
0 0 0
```

只通过 $2\times 2$ 的连续子矩阵操作不可能使得所有格子上的数都变为 $0$。

【数据范围】   

**本题采用捆绑测试。**

| 子任务编号 |    $n\leq$     | $k\leq$ | 分值 |
| :--------: | :------------: | :-----: | :--: |
|     1      |     $10^3$     |   $1$   |  11  |
|     2      |      $20$      |  $20$   |  14  |
|     3      |     $100$      |  $100$  |  17  |
|     4      |     $10^3$     | $10^3$  |  34  |
|     5      | $5\times 10^3$ | $10^3$  |  24  |

对于所有数据，$1\leq n\leq 5\times 10^3$，$1\leq m\leq \min(n^2,5\times 10^5)$，$1\leq k\leq \min(n,10^3)$，$1\leq x,y\leq n$，每对 $(x,y)$ 至多出现一次，$1 \le |z| \leq 10^9$。

数据保证如果有解，答案不超过 $2^{63}-1$。

---

【提示】

本题读入量较大，建议使用较快的读入方式。

!!! : 第一版AC :思路比较复杂。先用一个符合条件的数组画图检验， 发现逆推的话符合条件的矩阵应该是用大小为 k 的矩阵一个个累加起来的。 而矩阵的累加刚好在差分数组里有性质。 因此只需要遍历整个差分数组（画图注意边界）， 发现有不等于 0 的位置就把其在差分数组中的相应的 四个格点 变为 0 (这里不能直接变为0， 要自增或者自减， 因为下一步的判断会用到每个位置的数值)， 同时把数值记录下来，最后再遍历一次数组， 如果是符合要求的数组的话最后用一定是全为0的， 判断即可。

下为 样例1的差分数组
``` plain
0 0 0 0 0 0
0 1 0 0 -1 0
0 0 2 0 0 -2
0 0 0 0 0 0
0 -1 0 0 1 0
0 0 -2 0 0 2
```

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, t;
    cin >> n >> m >> t;
    auto maze = vector(n + 2, vector<long long> (n + 2, 0));
    auto ans = vector(n + 2, vector<long long> (n + 2, 0));
    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        maze[x ][y] += z;
    }
    
    for (int i = 1; i <= n + 1; i ++) {
        for (int k = 1; k <= n + 1 ; k ++) {
            ans[i][k] += maze[i][k] + maze[i - 1][k - 1] - maze[i - 1][k] - maze[i][k - 1];
        }
    }

    // for (int i = 0; i <= n + 1; i ++) {
    //     for (int k = 0; k <= n + 1; k ++) {
    //         cout << ans[i][k] << ' ';
            
    //     }
    //     cout << endl;
    // }

    long long total = 0;
    for (int i = 0; i <= n + 1 - t; i ++) {
        for (int k = 0; k <= n + 1 -t ; k ++) {
            if (ans[i][k] != 0) {
                total += abs(ans[i][k]);
                
                ans[i][k + t] += ans[i][k];
                ans[i + t][k] += ans[i][k];
                ans[i + t][k + t] -= ans[i][k];
                ans[i][k] -= ans[i][k];
            }
            
        }
    }

    for (int i = 0; i <= n + 1; i ++) {
        for (int k = 0; k <= n + 1 ; k ++) {
            if (ans[i][k] != 0) {
                cout << -1 << endl;
                return 0;
            }
            
        }
    }
    cout << total << endl;
    return 0;
}

```

!!! : 老师的思路：简单点~ 注意逆序差分

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    auto maze = vector(n + 1, vector<long long> (n + 1, 0));

    while (m--) {
        int x, y, z;
        cin >> x >> y >> z;
        maze[x - 1][y - 1] += z;
    }
    
    for (int i = n; i >= 0; i --) {
        for (int k = n; k >= 0 ; k --) {
            if  (i) maze[i][j] -= maze[i - 1][j];
        }
    }
    adjacent_difference(maze[i].begin(), maze[i].end(), maze[i].begin());

    long long total = 0;

    for (int i = 0; i < n; i ++) {
        for (int k = 0; k < n; k ++) {
            if (ans[i][k]) {
                if(i + k > n || j + k > n) {
                    cout << - 1 << endl;
                    return 0;
                }
                
                total += abs(ans[i][k]);
                
                ans[i][k + t] += ans[i][k];
                ans[i + t][k] += ans[i][k];
                ans[i + t][k + t] -= ans[i][k];
                ans[i][k] -= ans[i][k];
            }
            
        }
    }

    cout << total << endl;
    return 0;
}

```
---


#### 3.10  P7404 [JOI 2021 Final] 有趣的家庭菜园 4 / Growing Vegetables is Fun 4

**题目描述**
给定一个长为 $ N $的序列$ A_i $，你可以进行若干次操作：
- 选定一个区间$ [L,R] $，让这个区间里的数加$1$。
设经过这若干次操作后的序列为$ B_i $，那么你需要让$ B_i $满足下面这个要求：
- 存在一个整数$ k\in[1,N] $，满足对于子序列 $A_1= \{ B_1,B_2, \cdots,B_k \} $ 为严格递增序列，对于子序列 $ A_2 =\{ B_k,B_{k+1},\cdots,B_N\}$ 为严格递减序列。

你想知道最少需要多少次操作才能满足上面这个要求。

**输入格式**
第一行一个整数 $ N $ 代表序列长度。
第二行 $ N $ 个整数 $ A_i $ 代表序列。

**输出格式**
一行一个整数代表最小操作次数。
**输入输出样例1**
**输入1**
```
5
3 2 2 3 1
```
**输出1**
```
3
```
**输入输出样例2**
**输入2**
```
5
9 7 5 3 1
```
**输出2**
```
0
```
**输入输出样例3**
**输入3**
```
2
2021 2021
```
**输出3**
```
1
```
**输入输出样例4**
**输入4**
```
8
12 2 34 85 4 91 29 85
```
**输出4**
```
93
```
**说明/提示**
**样例1解释**
- 对$[2,5]$进行操作，序列变为 $\{3,3,3,4,2\}$ 。
- 对$[2,3]$进行操作，序列变为 $\{3,4,4,4,2\}$ 。
- 对$[3,3]$进行操作，序列变为 $\{3,4,5,4,2\}$ 。
**样例2解释**
序列已经满足要求，不需要操作。
**样例3解释**
对区间$[1,1]$或$[2,2]$进行操作都可。
**数据规模与约定**
**本题采用捆绑测试。**
- Subtask1（40pts）：$ N \le 2000 $。
- Subtask2（60pts）：无特殊限制。
对于 $ 100 \% $ 的数据，$ 1 \le N \le 2 \times 10^5 $，$ 1 \le A_i \le 10^9$。

!!! :  min(max([1 - k] neg , [k - n - 1]pos))
```
8
12 2 34 85 4 91 29 85 0
12 -10 32 51 -81 87 -62 56
x 12 -10 32 51 -81 87 -62 56 x
共 11 + 82 = 93次 
```

``` cpp

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto & x: a) cin >> x;
    vector <long long > diff (n + 2);
    adjacent_difference (a.begin(), a.end(), diff.begin() + 1);
    vector <long long> leftsum (n + 2), rightsum (n + 2);

    partial_sum(diff.begin(), diff.end(), leftsum.begin(), [](long long prev, long long cur) {
        if (cur > 0) return prev;
        return prev + (1 - cur);
    });
    //后缀和 .rbegin()
    partial_sum(diff.rbegin(), diff.rend(), rightsum.rbegin(), [](long long prev, long long cur) {
        if (cur < 0) return prev;
        return prev + (1 + cur);
    });

    long long ans = LLONG_MAX;
    for (int i = 1; i <= n; i ++) {
        ans = min (ans, max(leftsum[i], rightsum[i + 1]));
    }
    cout << ans << endl;

}
```
---
---


### 四、 单调性枚举
#### Lead In
给定一个长度为10万的非负整数数组和一个目标值 target
求一段最小区间 使得区间内数字之和大于 target
1、 枚举左右端点 计算区间内的和 复杂度：$O(n^3)$
2、 用前缀和代替区间和的计算 复杂度： $O(n^2)$
有没有什么办法让 复杂度 降为 $O(n)$ 呢、

画图可知：

<img src = 'photos\part 1 单调性枚举 1.png' width = 30% height = 30%>
<img src = 'photos\part 1 单调性枚举 2.png' width = 30% height = 30%>

绿色区域左侧是无论如何不符合要求的 右侧是一定符合要求的
<mark>并且 对于所有的绿色区域 恒有 $r_i \leqslant r_{i + 1}$</mark>

``` cpp
vector<int> rightIndex(n);
for (int l = 0; l < n; l ++) {
    int r = l == 0 ? 0 : rightIndex[l- 1];
    for (; r< n; r ++){
        if (getSum(l, r) >= target){
            ans = min(ans, r - l + 1)
            break;
        }
    }
    rightIndex[l]= r;
}
```
复杂度为 $O(n)$ 注意复杂与于程序嵌套层数没有直接关系

**公式化定义**
<img src = 'photos\part 1 单调性枚举 3.png' width = 60% height = 60%>

<img src = 'photos\part 1 单调性枚举 4.png' width = 60% height = 60%>

**单调性证明**
<img src = 'photos\part 1 单调性枚举 5.png' width = 60% height = 60%>

``` cpp
int sum = 0;
for (int l = 0, r = 0; l < n;) {
    if (r < n && sum < target) {
        sum += arr[r++];
    } else {
        if (sum >= target) {
            ans = min (ans, r - l);
        }
        sum -= arr[l ++];
    } 
}
```
**四步关键**
1. 判断是否满足条件
2. r后移
3. l后移
4. 找到满足条件的关键词如何更新答案
   
**模板函数**

``` cpp 
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
    else update(l, r - 1); //右指针越界了也找不到匹配的区间，那自然就是剩下的所有区间了。
    remove(l ++, r);
    }
}
//本函数在跳出while后， [l, r - 1] 才是符合条件的最小区间（因为while内r已自增）[l, r - 2]就是不符合条件的最大区间， 所以update的是[l, r - 2]。

int main() {
    int start, end;
    int sum;//匹配条件
    increaseEnumerate ( start, end,
        [&](int l, int r) { // match

        },
        [&](int l, int r) { // insert

        },
        [&](int l, int r) { // remove 

        },
        [&](int l, int r) { // update

        });
}
```

样例：
<img src = 'photos\part 1 单调性枚举 6.png' width = 100% height = 100%>

<img src = 'photos\part 1 单调性枚举 7.png' width = 100% height = 100%>

**有单调递增枚举 也会有单调递减枚举**
<img src = 'photos\part 1 单调性枚举 8.png' width = 100% height = 100%>

**单调性剪枝**
<mark>题面和上题相同 但是二者在判断策略上很不一样哦</mark>
<img src = 'photos\part 1 单调性枚举 9.png' width = 100% height = 100%>

**总结**
1. 单调递增枚举 ： 二元组满足条件的最小值， 单调递增
2. 四类求值 ： 最小满足， 最大不满足， 满足/不满足的方案数量
3. 公式化：关键值 条件 维护（移动） 更新
4. 单调递减枚举 ： 二元组满足条件的最小值， 单调递减
5. 单调性剪枝 ： 左边或者下面比现在的情况更差， 不用枚举（把二维矩阵的图画出来模拟一下即可）

***

#### 4.1 lq179 日志统计
**题目描述**
小明维护着一个程序员论坛。现在他收集了一份“点赞”日志，日志共有 N 行。其中每一行的格式是 $\mathtt{ts\ id}$ 表示在 $\mathtt{ts}$ 时刻编号 $\mathtt{id}$ 的帖子收到一个“赞”。

现在小明想统计有哪些帖子曾经是“热帖”。如果一个帖子曾在任意一个长度为 D 的时间段内收到不少于$ K$ 个赞，小明就认为该帖子曾是“热帖”。

具体而言，如果存在某个时刻 T 满足该帖在 $[T,T+D)$ 这段时间内（注意是左闭右开区间）收到不少于 $K$ 个赞，该帖就曾是“热帖”。  

给定日志，请你帮助小明统计出所有曾是“热帖”的帖子编号。

**输入描述**
输入格式：

第一行包含三个整数 $N,D,K$。

以下 N 行每行一条日志，包含两个整数 $\mathtt{ts}$ 和 $\mathtt{id}$。  

其中 $1\le K\le N\le 10^5，0\le \mathtt{ts}\le 10^5，0\le \mathtt{id}\le 10^5$。

**输出描述**

按从小到大的顺序输出热帖 $\mathtt{id}$。每个 $\mathtt{id}$ 一行。

**输入输出样例** 
输入  
```
7 10 2
0 1
0 10
10 10
10 1
9 1
100 3
100 3
```  
输出  
```
1
3
```

!!! : 初见， 第二部分确定是否满足条件的很好判断。但第一部分数据处理不是很会，目前的想法是把每一组转换成一组键值对，然后排序，按每种情况进行独立判断。

!!! : 老师思路 : 更有滑动窗口的感觉，同时运用stl，代码很简洁。

不用模板
``` cpp
#include <bits/stdc++.h>
using namespace std;

// 条件 t[r] - t[l] >= d
// 不符合条件的区间， 是否有 >= k

int main() {
    int n, d, k;
    cin >> n >> d >>k;
    auto logs = vector<pair<int, int>>(n);
    for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
    sort(logs.begin(), logs.end());

    // for (int i = 0; i < n; i++) {
    //     cout << logs[i].first << ' ' << logs[i].second << endl;
    // }

    vector<int> cnt (100001);
    set<int> ans;
    for (int l = 0, r = 0; r < n; ) {
        while (r < n && logs[r].first - logs[l].first < d) {
            int id = logs[r++].second;
            cnt[id] ++;
            if (cnt[id] == k) ans.insert(id);
        }
        cnt[logs[l++].second]--;
    }
    for (auto x: ans) cout << x << endl;
}
```

使用模板
``` cpp
#include <bits/stdc++.h>
using namespace std;

// 条件 t[r] - t[l] >= d
// 不符合条件的区间， 是否有 >= k

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
    int n, d, k;
    cin >> n >> d >>k;
    auto logs = vector<pair<int, int>>(n);
    for(auto & [t, id]:logs) cin >> t >> id; //二元组输入处理
    sort(logs.begin(), logs.end());

    // for (int i = 0; i < n; i++) {
    //     cout << logs[i].first << ' ' << logs[i].second << endl;
    // }
    vector<int> cnt (100001);
    set<int> ans;
    increaseEnumerate (0, n - 1,
        [&](int l, int r) { //match
            return logs[r].first - logs[r].first >= d;
        },
        [&](int l, int r) { //insert
            cnt[logs[r].second] ++;
        },
        [&](int l, int r) { //remove
            cnt[logs[l].second] --;
        },
        [&](int l, int r) { //update
            if (cnt[logs[l].second] >= k)  ans.insert(logs[l].second);
        });
    
    for (auto x: ans) cout << x << endl;
}
```

---

#### 4.2 lq2109 统计子矩阵
**问题描述**
给定一个 $N \times M$ 的矩阵 $A$，请你统计有多少个子矩阵（最小 $1 \times 1$，最大 $N \times M$）满足子矩阵中所有数的和不超过给定的整数 $K$？

**输入格式**
第一行包含三个整数 $N,M,K$。
之后 $N$ 行，每行包含 $M$ 个整数，代表矩阵 $A$。

**输出格式**
一个整数代表答案。

**样例输入**
```cpp
3 4 10
1 2 3 4
5 6 7 8
9 10 11 12
```
**样例输出**
```
19
```

**评测用例规模与约定**
对于 $30\%$ 的数据，满足$ N, M \le 20$。
对于 $70\%$ 的数据，满足 $N, M \le 100$。
对于 $100\% $的数据，满足$1 \le N, M \le 500,\quad 0 \le A{i,j} \le 1000,\quad 1 \le K \le 250\,000\,000$.

!!! : 初见：<img src = 'photos\lq 2109 1.png' width = 50% height = 50%> 遍历策略如是说。

!!! : 单调性枚举仅在一维成立， 二维损失单调性。故本题需要先将二维转成一维。先枚举 [x1, x2] 再枚举每一列的和 $O(n^2) $[y1, y2] [l, r] <= k $O(n)$。

!!! : 500 的数据量 == $O(n^3)$

``` cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, k;
    cin >> n >> m >> k;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }
    
    long long ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> sum(m);
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int y =0; y < m; y ++) sum[y] += maze[x2][y];

            int total = 0;
            for (int l = 0, r = 0; l < m; ) {
                while (r < m && total <= k) {
                    total += sum[r ++];
                }
                if (total > k) {
                    //[l, r - 2] 
                    ans += r - 2 - l + 1;
                } else {
                    //[l, r - 1]
                    ans += r - 1 - l + 1;
                }
                total -= sum[l ++];
            }
        }
    }
    cout << ans << endl;
}
```
模板
``` cpp
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
    int n, m, k;
    cin >> n >> m >> k;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }
    
    long long ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> sum(m);
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int y =0; y < m; y ++) sum[y] += maze[x2][y];

            int total = 0;

            increaseEnumerate (0, m - 1,
            [&](int l, int r) {
                return total > k;
            },
            [&](int l, int r) {
                total += sum[r];
            },
            [&](int l, int r) {
                total -= sum[l];
            },
            [&](int l, int r) {
                ans += r - l + 1;
            });
        }
    }
    cout << ans << endl;
}
```
---

#### 4.3 lq 2174 最大子矩阵
**问题描述**

小明有一个大小为 \(N \times M\) 的矩阵，可以理解为一个 \(N\) 行 \(M\) 列的二维数组。

我们定义一个矩阵 \(m\) 的稳定度 \(f(m)\) 为：
\[
f(m) = \text{max}(m) - \text{min}(m)
\]
其中 \(\text{max}(m)\) 表示矩阵 \(m\) 中的最大值，\(\text{min}(m)\) 表示矩阵 \(m\) 中的最小值。

现在小明希望从这个矩阵中找到一个稳定度不大于 \(limit\) 的子矩阵，同时他还希望这个子矩阵的面积越大越好（面积可以理解为矩阵中元素个数）。

子矩阵定义如下：从原矩阵中选择一组连续的行和一组连续的列，这些行列交点上的元素组成的矩阵即为一个子矩阵。

**输入格式**

第一行输入两个整数 \(N\)、\(M\)，表示矩阵的大小。

接下来 \(N\) 行，每行输入 \(M\) 个整数，表示这个矩阵。

最后一行输入一个整数 \(limit\)，表示限制。

**输出格式**

输出一个整数，表示小明选择的子矩阵的最大面积。

**样例输入**
``` cpp
3 4
2 0 7 9
0 6 9 7
8 4 6 4
8
```

**样例输出**
``` cpp
6
```

!!! : 遍历策略同上题， 更新条件改为 [l, r] > limit 。 寻找不满足条件的最大值， 用到 insert erase maximum minimum 数据结构用到一个multiset。

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n ,m ,limit;
    cin >> n >> m;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }

    cin >> limit;
    int ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> mmin(m, INT_MAX);
        vector<int> mmax(m, INT_MIN);
        // insert [x1, x2] max, min
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int i = 0; i < m; i++) {
                mmin[i] = min(mmin[i], maze[x2][i]);
                mmax[i] = max(mmax[i], maze[x2][i]);
            }
            multiset<int> s;
            for (int l = 0, r = 0; l < m; ) {
                while (r < m && (s.empty() || *s.rbegin() - *s.begin() <= limit)) {
                    s.insert(mmin[r]);
                    s.insert(mmax[r++]);
                }

                if (!(s.empty() || *s.rbegin() - *s.begin() <= limit)) {
                    ans = max(ans, (x2 - x1 + 1) * (r - l - 1));
                } else {
                    ans = max(ans, (x2 - x1 + 1) * (r - l));
                }
                s.erase(s.find(mmin[l]));
                s.erase(s.find(mmax[l++]));
            }
        }
    }
    cout << ans << endl;
}
```
模板
``` cpp
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
    int n ,m ,limit;
    cin >> n >> m;
    auto maze = vector(n, vector<int>(m));
    for (auto &row : maze) {
        for (auto &x : row) cin >> x;
    }

    cin >> limit;
    int ans = 0;
    for (int x1 = 0; x1 < n; x1 ++) {
        vector<int> mmin(m, INT_MAX);
        vector<int> mmax(m, INT_MIN);
        // insert [x1, x2] max, min
        for (int x2 = x1; x2 < n; x2 ++) {
            for (int i = 0; i < m; i++) {
                mmin[i] = min(mmin[i], maze[x2][i]);
                mmax[i] = max(mmax[i], maze[x2][i]);
            }
            multiset<int> s;
            increaseEnumerate (0, m - 1,
            [&](int l, int r) {
                return !s.empty() && *s.rbegin() - *s.begin() > limit;
            },
            [&](int l, int r) {
                s.insert(mmin[r]);
                s.insert(mmax[r]);
            },
            [&](int l, int r) {
                s.erase(s.find(mmin[l]));
                s.erase(s.find(mmin[l]));
            },
            [&](int l, int r) {
                ans = max(ans, (x2 - x1 + 1) * (r - l + 1));
            });
        }
    }
    cout << ans << endl;
}
```

---


#### 4.4 P10444 极差

**题目描述**

对于一个序列 $c$ ，定义 $c$ 的极差为 $c$ 中最大值与最小值之差。现在给定一个长度为 $n$ 的序列 $a$，问是否能将其分成至少两个长度大于 $1$ 的子序列，使得每个子序列的极差都相等（注意，所有元素都必须分配且每个元素仅能分配到一个子序列中）。

**输入格式**
**本题包含多组数据**。
第一行两个整数 $T,id$，表示数据组数和子任务编号。
对于每组数据，
第一行一个正整数 $n$，表示数组长度。
第二行 $n$ 个整数表示序列 $a$。

**输出格式**

对于每组数据，输出一行一个字符串 `Yes` 或 `No`。

**输入输出样例 1**
输入 1

```
2 1
6
1 1 4 5 1 4
7
1 9 1 9 8 1 0
```

输出 1

```
No
Yes
```

**说明/提示**

 样例 $\small\text{1}$ 解释

样例符合子任务 1 的约束，$id=1$。


询问一：

可以证明，没有任何方案满足条件。

询问二：

合法分配的一种子序列集合如下：
- $\{1,9\}$。
- $\{1,9\}$。
- $\{8,1,0\}$。

答案不唯一。

**数据规模与约定**

**本题采用捆绑测试**。
- Subtask 1（20 points）：$4\le \sum n\le 20,a_i\ge 0$。
- Subtask 2（20 points）：$4\le \sum n\le 100,a_i\ge 0$。
- Subtask 3（20 points）：$4\le \sum n\le 10^3,a_i\ge 0$。
- Subtask 4（10 points）：$a$ 数组中元素相等。
- Subtask 5（30 points）：无特殊限制。

对于 $100\%$ 的数据，$4\le \sum n\le 10^6,0\le |a_i|\le 10^9,1\le T\le 300$。

!!! : 本题说实话更多像是数字特征的找寻 刻意陷在单调递减就有点…… 可能我没悟透？
!!! : 首先观察题意可以很容易体会到本题需要的将数字划分为两个序列（一开始卡在多个序列也成立但不知能不能变为两个序列，下见证明）。经过挣扎后发现若能划为多个序列，则一定可以划为两个序列。那么此时，要找到的则是是否有两个数 l, r， 满足 $l - a_1 =  a_n - r$， 即 $l + r = a_1 + a_n$，同时要满足剩下的数都可以塞在这两个区间内（这个可以靠排序解决）。

>证明：
假设有一给定序列 $a$, 排序后为 $a_1, a_2, a_3, ..., a_n$， 若该序列内存在多段极差相等的子序列， 则最后一定会有 $a_{x_1} - a_1 = a_n - a_{x_n}$ ($x_{x_n}$ 代表第n段子序列的段首或段尾) 即所有的数都能放进这两个区间内而不越界。

``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
// 1 1 4 5 1 4
// 1 1 1 4 4 5
// [1 max] [min 5]
// max - 1 = 5 - min
// max + min = 5 + 1
// a + b = target
    int T, id;
    cin >> T >> id;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        sort(a.begin(), a.end());


        int target = a[0] + a[n - 1];
        cout << [&](){
            for (int l = 1, r = n - 2; l < r;) {
                if (a[l] + a[r] > target) {
                    r--;
                } else if (a[l] + a[r] < target) {
                    l++;
                } else {
                    return "Yes";
                }
            }
            return "No";
        }() << endl;
    }
}

```
---

#### 4.5 lq2209 近似gcd 

**问题描述**

小蓝有一个长度为 \(n\) 的数组 \(A = (a_1, a_2, \cdots, a_n)\)，数组的子数组被定义为从原数组中选出连续的一个或多个元素组成的数组。数组的最大公约数指的是数组中所有元素的最大公约数。如果最多更改数组中的一个元素之后，数组的最大公约数为 \(g\)，那么称 \(g\) 为这个数组的近似GCD。一个数组的近似GCD可能有多种取值。

具体的，判断 \(g\) 是否为一个子数组的近似GCD如下：

1. 如果这个子数组的最大公约数就是 \(g\)，那么说明 \(g\) 是其近似GCD。
2. 在修改这个子数组中的一个元素之后（可以改成想要的任何值），子数组的最大公约数为 \(g\)，那么说明 \(g\) 是这个子数组的近似GCD。

小蓝想知道，数组 \(A\) 有多少个长度大于等于 2 的子数组满足近似 GCD 的值为 \(g\)。

**输入格式**

输入的第一行包含两个整数 \(n, g\)，用一个空格分隔，分别表示数组 \(A\) 的长度和 \(g\) 的值。

第二行包含 \(n\) 个整数 \(a_1, a_2, \cdots, a_n\)，相邻两个整数之间用一个空格分隔。

**输出格式**

输出一行包含一个整数表示数组 \(A\) 有多少个长度大于等于 2 的子数组的近似 GCD 的值为 \(g\)。

**样例输入**
```
5 3
1 3 6 4 10
```
**样例输出**
```
5
```

!!! : 分析可得， 在在某个窗口[l, r]内有两个不满足的值的话（最小的），那么[l. r - 1] 一定满足， 余下的内部的子数组也满足， 问题就变成了统计有几个 “2”的问题。

**初版 没过 怀疑是r越界的问题**
一拖四， 滑动窗口末尾的判定问题， 左端点的移动的高效的问题。
还是要把问题尽可能简化成一个条件和一个单向的数组
``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n , g ;
    cin >> n >> g;
    auto line = vector<int>(n);
    for (auto &x : line) cin >> x;
    
    long long ans = 0;

    if (g != 1) {
        for (int i = 0 ; i < n; i ++) line[i] = line[i] % g;

        int current = 0;
        for (int l = 0, r = 0; r < n; ) {
            if (!line[r] ) {
                ++ r;
            } else if (line[r] && !current) {
                current ++;
                r++;
            } else if (line[r] && current) {
                ans += r - l - 1;
                ++ l;
                r = l;
                current = 0;
            }
            
        }
    }

    if (g == 1) ans = n * (n - 1) / 2;
    
    cout << ans << endl;
}
```

**ac版 注意 l < n 改成 r < n 过不了 窗口边界越界的问题**
``` cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n , g ;
    cin >> n >> g;
    auto line = vector<int>(n);
    for (auto &x : line) cin >> x;
    
    long long ans = 0;

    for (int i = 0 ; i < n; i ++) {
            line[i] = line[i] % g;
            if (line[i] != 0) line[i] = 1;
    }
        
    int current = 0;
    for (int l = 0, r = 0; l < n; ) {
        while(r < n && current < 2) {
            current += line[r++];
        }
        
        if (current >= 2) {
            ans += (r - 2) - (l + 1) + 1;
        } else {
            ans += (r - 1) - (l + 1) + 1;
        }

        current -= line[l++];
    }
        

    cout << ans << endl;
}
```

---

#### 4.6 lq2109 青蛙过河
**问题描述**

小青蛙住在一条河边，它想到河对岸的学校去学习。小青蛙打算经过河里的石头跳到对岸。

河里的石头排成了一条直线，小青蛙每次跳跃必须落在一块石头或者岸上。不过，每块石头有一个高度，每次小青蛙从一块石头起跳，这块石头的高度就会下降 \(1\)，当石头的高度下降到 \(0\) 时小青蛙不能再跳到这块石头上（某次跳跃后使石头高度下降到 \(0\) 是允许的）。

小青蛙一共需要去学校上 \(x\) 课，所以它需要往返 \(2x\) 次。当小青蛙具有一个跳跃能力 \(y\) 时，它能跳不超过 \(y\) 的距离。

请问小青蛙的跳跃能力至少是多少才能用这些石头上完 \(x\) 次课。

**输入格式**

输入的第一行包含两个整数 \(n, x\)，分别表示河的宽度和小青蛙需要去学校的天数。请注意 \(2x\) 是实际过河的次数。

第二行包含 \(n - 1\) 个非负整数 \(H_1, H_2, \cdots, H{n-1}\)，其中 \(H_i > 0\) 表示在河中与小青蛙的家相距 \(i\) 的地方有一块高度为 \(H_i\) 的石头，\(H_i = 0\) 表示这个位置没有石头。

**输出格式**

输出一行，包含一个整数，表示小青蛙需要的最低跳跃能力。

**样例输入**
```
5 1
1 0 1 0
```

**样例输出**
```
4
```


**样例说明**

由于只有两块高度为 1 的石头，所以往返只能各用一块。第 1 块石头和对岸的距离为 4，如果小青蛙的跳跃能力为 3 则无法满足要求。所以小青蛙最少需要 4 的跳跃能力。

**评测用例规模与约定**

对于 30\% 的评测用例, \(n \leq 100\);

对于 60\% 的评测用例, \(n \leq 1000\);

对于所有评测用例, \(1 \leq n \leq 10^5, 1 \leq x \leq 10^9, 1 \leq H_i \leq 10^4\)。

!!! : 初见：首先来回跳可以简化为2x只从一边往另一边跳。 忽略那些高度大于2x的点（即视其为与岸等价的点， 再统计两个可以视作为与岸等价的点之间的的总高度值与2x的大小的关系。若大于等于那么这个区间中所有点到左右两侧的最大值就是这个区间内需要的跳跃能力的最小值。（很复杂 而且估计是错的）

!!! : 老师： 从起点开始模拟思考。假设跳跃能力为y， 那么若要让所有青蛙都跳出第一步 [0, y] 之间的区间和必须>= 2x， 如此类推，[1, y + 1]... 反过来，就是要找相连的[l, r] 区间和内大于等于2x的区间 长度即为要更新的值。（tips：每只青蛙在区间内只能选一个点跳，即跳出一步）

``` cpp
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

int main () {
    int n, x;
    cin >> n >> x;
    n--;
    vector<int> arr(n);
    for (auto & x : arr) cin >> x;

    x <<= 1;
    int sum = 0; 
    int ans = 0;

    increaseEnumerate (0, n - 1,
        [&](int l, int r) { //match
            return sum >= x;
        },
        [&](int l, int r) { //insert
            sum += arr[r];
        },
        [&](int l, int r) { //remove
            sum -= arr[l];
        },
        [&](int l, int r) { //update
            ans = max(ans, r - l + 1);
        });

    cout << ans + 1 << endl;
}
```

---

#### 4.7 至少有K个重复字符的最长字串

**问题描述**
现有一个字符串 s 和一个整数 k， 请找出 s 中的最长字串， 要求该子串中每一个字符出现次数都不少于 k， 返回这一字串的长度。

若不存在，则直接返回0。

**示例 1:**

```
输入: s = aaabb, k = 3  


输出: 3

解释: 最长子串为 aaa，其中 'a' 重复了 3 次。
```
**示例 2:**
```
输入: s = ababbc, k = 2

输出: 5

解释: 最长子串为 ababb，其中 'a' 重复了 2 次，'b' 重复了 3 次。
```
**提示:**

- \(1 \leqslant \text{s.length} \leqslant 10^4\)
- \(s\) 仅由小写英文字母组成
- \(1 \leqslant k \leqslant 10^5\)

!!! : 首先题目条件不符合单调性的前提（可增加一个已知序列中不存在的字母）
!!! : 若是给定不同字母的总数 则可以规避这个问题（循环26次真的没问题吗）
!!! : 维护两个值， 一个记录字母种类 一个记录字母重复次数满足条件的个数

``` cpp

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int k;
    cin >> k;

    int ans = 0;
    for (int x = 1; x <= 26; x ++) {
        int cnt[128] = {};
        int typecnt = 0;
        int matchcnt = 0;
        for (int l = 0, r = 0; l < s.size();) {
            while (r < s.size() && typecnt <= x) {
                char c = s[r++];
                if (cnt[c] == 0) typecnt ++;
                cnt[c]++;
                if (cnt[c] == k) matchcnt ++;
            }
            //[l, r - 1] 最大匹配情况
            if (matchcnt == x) {
                if (typecnt > x) {
                    //[l, r - 1] 满足
                    //[l, r - 2] 不满足
                    ans = max(ans, r - 2 -l + 1);
                } else {
                    ans = max(ans, r - 1 - l + 1);
                }
            }
            char c = s[l ++];
            if (cnt[c]-- == k ) matchcnt--;
            if (cnt[c] == 0) typecnt --;
        }
    }
    cout << ans << endl;
}
```
模板
```cpp
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
    string s;
    cin >> s;
    int k;
    cin >> k;

    int ans = 0;
    for (int x = 1; x <= 26; x ++) {
        int cnt[128] = {};
        int typecnt = 0;
        int matchcnt = 0;
    increaseEnumerate (0, s.size() - 1,
        [&](int l, int r) { //match
            return typecnt > x;
        },
        [&](int l, int r) { //insert
            char c = s[r];
            if (cnt[c]++ == 0) typecnt++;
            if (cnt[c] == k) matchcnt++;
        },
        [&](int l, int r) { //remove
            char c = s[l];
            if (cnt[c]-- == k) matchcnt--;
            if (cnt[c] == 0) typecnt--;
        },
        [&](int l, int r) { //update
            if (matchcnt == x) {
                ans = max(ans, r - l + 1);
            }
        });
    }
    cout << ans << endl;
}
```

#### 4.8 盛最多水的容器
**问题描述**

给定一个长度为 \(n\) 的整数数组 \(\text{height}\)。有 \(n\) 条垂线，第 \(i\) 条线的两个端点是 \((i, 0)\) 和 \((i, \text{height}[i])\)。

找出其中的两条线，使得它们与 \(x\) 轴共同构成的容器可以容纳最多的水。

返回容器可以储存的最大水量。

说明：你不能倾斜容器。

**示例1**
<img src = 'photos\part 1 4.8.png' width = 60% height = 60%>

输入: [1,8,6,2,5,4,8,3,7]
输出: 49
解释: 图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。

**示例 2:**

输入: height = [1,1]
输出: 1

!!! : 要计算装的水， 其实就是找到一个让 min(h[l], h[r]) * dis(l, r) 最大的区间。若采用传统的l， r同起点开始遍历， 那么dis部分是单调的， 但是乘上前面的部分就不单调了。
!!! : 要找到单调的， 实际上就是找到什么高度在什么情况下和长度的增减性是一样的。并利用单调性排除掉不合理的情况。假设有一区间[l, r] h[l] < h[r]。那么，r左移的话，整体取值是单调减的（这与题目要求最大值相悖），所以这种情况可以都排除掉。即只能是l右移才有更新答案的可能性。 至于说l左移和r右移，要从中间开始遍历，比较反直觉，可能也可以？ 至于说大于的情况，反过来便是。
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector <int> height (n);
    for (auto &x : height) cin >> x;

   int ans = 0;
    for (int l = 0, r = height.size() - 1; l < r;) {
        ans = max(ans, min(height[l], height[r]) * (r - l));
        if (height[l] < height[r]) l++;
        else r--;
    }
    cout << ans << endl;
}
```

---

#### 4.9 P10710 School Photo
**题目描述**

Zane 是 NOI 学校的校长。NOI 学校有 $n$ 个班，每个班有 $s$ 名同学。第 $i$ 个班中的第 $j$ 名同学的身高是 $a_{i,j}$。

现在 Zane 想从每个班上选出一名同学拍照，使得这 $n$ 名同学中最高的同学和最低的同学的身高差最小。

请你输出这个最小值。

**输入格式**

第一行，两个整数 $n,s$；

接下来 $n$ 行，每行 $s$ 个整数，表示 $a$。

**输出格式**

一行一个整数表示答案。

输入输出样例 1
输入 1

```
2 3
2 1 8
5 4 7
```

输出 1

```
1
```

输入输出样例 2

输入 2

```
3 3
3 1 4
2 7 18
9 8 10
```
输出 2

```
4
```

说明/提示

【样例 2 解释】

选择 $a_{1,3},a_{2,2},a_{3,2}$，答案为 $8-4=4$。

** **

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$11$|$n=2$|
|$2$|$22$|$n,s\le100$|
|$3$|$9$|$n,s\le250$|
|$4$|$33$|$n,s\le500$|
|$5$|$25$|无|

对于 $100\%$ 的数据，$1\le n,s \le 1000,1\le a_{i,j} \le 10^9$。

!!! : 初见， 每一行单独排序，然后逐一枚举
!!! : 换个角度想，不考虑班级，只考虑高度，就是在给定的身高中选两个最接近的。但是要满足选出n个人的条件，所以还要维护一个变量来存放当前序列中不同班级的数量。遍历方式见下

eg
```
3 3
3 1 4
2 7 18
9 8 10
```
||1|2|3|4|5|6|7|8|9|
|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
|height|1|2|3|4|7|8|9|10|18|
|class|1|2|1|1|2|3|3|3|2|

```cpp
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
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> arr;
    arr.reserve(n * m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int h;
            cin >> h;
            arr.push_back({h, i});
        }
    }

    sort(arr.begin(), arr.end());

    vector<int> cnt(n);
    int classCnt = 0;
    int ans = INT_MAX;

    increaseEnumerate(0, n * m - 1,
        [&](int l, int r) {
            return classCnt == n;
        },
        [&](int l, int r) {
            if (cnt[arr[r++].second]++ == 0) classCnt++;
        },
        [&](int l, int r) {
            if (--cnt[arr[l++].second] == 0) classCnt--;
        },
        [&](int l, int r) {
            // [l, r+1]
            if (r + 1 == n * m) return;
            ans = min(ans, arr[r + 1].first - arr[l].first);
        });
    cout << ans << endl;
}
```

---

#### 4.10 P8708 [蓝桥杯 2020 省 A1] 整数小拼接

**题目描述**

给定一个长度为 $n$ 的数组 $A_1,A_2,\cdots,A_n$。你可以从中选出两个数 $A_i$ 和 $A_j$($i\neq j$)，然后将 $A_i$ 和 $A_j$ 一前一后拼成一个新的整数。例如 `12` 和 `345` 可以拼成 `12345` 或 `34512`。注意交换 $A_i$ 和 $A_j$ 的顺序总是被视为 $2$ 种拼法，即便是 $A_i=A_j$ 时。

请你计算有多少种拼法满足拼出的整数小于等于 $K$。

**输入格式**

第一行包含 $2$ 个整数 $n$ 和 $K$。

第二行包含 $n$ 个整数 $A_1,A_2,\cdots,A_n$。

**输出格式**

一个整数代表答案。

输入输出样例 1
输入 1

```
4 33
1 2 3 4
```

输出 1

```
8
```

**说明/提示
**
对于 $30\%$ 的评测用例 $1\le n\le1000$，$1\le k\le10^8$，$1\le A_i\le10^4$。

对于所有评测用例，$1\le n\le10^5$，$1\le k\le10^{10}$，$1\le A_i\le10^9$。

!!! : 显而易见，题目本身没啥好说的，两个数拼接起来的时候，字符串开销比较大，所以单开一个数组用来计算进位

``` cpp

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    sort(a.begin(), a.end());
    // 12 & 345 >> 12 * 1000 + 345 
    //拼接后前一个数要偏移的大小
    vector<long long> exp(n, 1);
    for (int i = 0; i < a.size(); i++) {
        for (int x = a[i]; x; x /= 10, exp[i] *= 10);
    }

    long long ans = 0;
    for (int l = 0, r = n - 1; r >= 0 && l < n;) {
        if (a[l] * exp[r] + a[r] <= k) {
            ans += r - l;
            l++;
        } else {
            r--;
        }
    }

}
```
---

#### 4.11 P8472 [Aya Round 1 G] 咕噜论坛（post） link to 4.2 二维矩阵下的枚举方式


**题目描述**

「咕噜论坛」的一篇帖子下，有若干个不同的人对其进行了回复，这些评论形成了一个 $n\times m$ 的矩阵。

论坛管理员 prAB 发现这些评论者的名字颜色只有灰名、紫名和棕名三种，他决定「动用神权」来增加这些评论的整齐度。但是论坛站长超氧化铯（CsO2）可能会因为他「滥用神权」导致论坛「臭名昭著」而踢掉他的管理身份。所以 prAB **最多**只能动用 $k$ 次神权。已知他的神权有两种：

- 「暴政警告」：送一个灰名进陶片使他变成棕名。
- 「放人一马」：将一个棕名解封使他变成灰名。

由于「咕噜论坛」的管理员是至高无上的，对于评论中的紫名他无能为力。

prAB 认为在这些评论者的名字颜色中，最大的颜色相同的子矩阵的大小能代表这篇帖子评论的整齐度。所以他想知道，他动用完神权后评论的整齐度的最大值。

**输入格式**

- 第一行输入三个整数 $n,m,k$。
- 接下来 $n$ 行，每行输入一个长度为 $m$ 的字符串，代表评论矩阵中每个人名字的颜色。其中 `B` 代表棕名，`G` 代表灰名，`P` 代表紫名。

**输出格式**

- 第一行输出一个整数，表示整齐度的最大值。
- 下面 $n$ 行，每行输出一个长度为 $m$ 的字符串，格式同「输入格式」。代表修改完后每个人名字的颜色。如有多种方案输出则任意一种即可。

 输入输出样例 1

 输入 1

```
3 4 2
BBGB
GBBB
PGPP
```

 输出 1

```
8
BBBB
BBBB
PGPP
```

**说明/提示**

**数据范围及约定**

对于 $100\%$ 的数据，$1 \le n,m\le 500$，$0 \le k \le nm$。字符矩阵中只会出现大写字母 `B`、`G` 和 `P`。

!!! : 易得P是没有讨论的必要的，所以分成两种情况， B，G来进行讨论。 将不需要修改的位置设成0， 要的位置设成1， 实际上就是要求最大的一个子矩阵，包含尽可能少的修改次数。P只需要修改为k+1（必越界）不参与讨论即可。
!!! : 详见4.2

``` cpp
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
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> maze(n);
    for (auto &row : maze) cin >> row;
    int ans = 0;
    tuple<char, int, int, int, int> res;

    auto func = [&](int B, int G, int P) {
        vector<int> v(128);
        v['B'] = B;
        v['G'] = G;
        v['P'] = P;

        for (int x1 = 0; x1 < n; x1++) {
            vector<int> sum(m);
            for (int x2 = x1; x2 < n; x2++) {
                for (int i = 0; i < m; i++) {
                    sum[i] += v[maze[x2][i]];
                }
           

            int total = 0;
            increaseEnumerate(0, m - 1,
                [&](int l, int r) {
                    return total > k;
                },
                [&](int l, int r) {
                    total += sum[r];
                },
                [&](int l, int r) {
                    total -= sum[l];
                },
                [&](int l, int r) {
                    int temp = (x2 - x1 + 1) * (r - l + 1);
                    if (temp > ans) {
                        ans = temp;
                        char c = 'p';
                        if (B == 0) c = 'B';
                        else if (B == 1) c = 'G';
                        res = {c, x1, x2, l, r};
                    }
                });
            } 
        }
    };

    func(0, 1, k + 1);
    func(1, 0, k + 1);
    func(k + 1, k + 1, 0);

    auto [c, x1, x2, y1, y2] = res;
    for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
            maze[x][y] = c;
        }
    }

    cout << ans << endl;
    for (auto row : maze) cout << row << endl;

}
```

#### 4.12 接雨水
<img src="photos\枚举 2.4.png" width="100%" height="100%">

!!! : 和前缀和做法一样，对于每个点还是需要知道左右的最高高度。
```cpp
int trap(vector<int>& h) {
    int ans = 0;
    int n = h.size();
    for (int l = 1, r = n - 2, leftMax = h[0], rightMax = h[n - 1]; l <= r;) {
        leftMax = max(leftMax, h[l]);
        rightMax = max(rightMax, h[r]);
        if (leftMax < rightMax) ans += (leftMax - h[l++]);
        else ans += (rightMax - h[r--]);
    }
    return ans;
}

```

---

#### 4.13 P11243 繁花

**题目背景**

我已经知道，在设置好循环播放时就已经知道，我是在麻痹自己，在逃避问题。

我承认如此，可捞起那些沉于水底的细节时，却一瞬间突然和所有所有真实的心跳共鸣。

那时总想的太少，现在常想得太多，不知所措似荒塘里的绿藻蔓延着。

然而这世间情感太多，小 R 也只能体会更开心和更难过。

**题目描述**

小 R 想对上面的问题进行探究，她想先做一些统计，于是她抽象了这个问题。

小 R 有 $n$ 个未知量 $a_1\dots a_n$，对每个 $1 \leq i < n$，她都比较了 $a_i$ 和 $a_{i+1}$ 并写下了一个字符 $c_i \in \{\texttt <, \texttt >, \texttt =\}$，表示两个未知量之间的比较结果。具体地：

- 若 $c_i = \texttt >$，则 $a_i > a_{i+1}$；
- 若 $c_i = \texttt <$，则 $a_i < a_{i+1}$；
- 否则（$c_i = \texttt =$），表示 $a_i = a_{i+1}$。

小 R 称 $\bm{a_i}$ **比** $\bm{a_j}$ **更开心**，当且仅当对任何 **满足上述 $\bm{n - 1}$ 条约束的** $[a_1, \dots, a_n] \in \mathbb R^n$，都有 $a_i < a_j$。请你帮她数出 $1 \leq i, j \leq n$ 且 $a_i$ 比 $a_j$ 更开心的整数数对 $(i, j)$ 个数。

因为要循环播放，所以有多组数据。

**输入格式**

**本题有多组数据。**

第一行，一个整数 $T$，表示数据组数。对于每组数据：

- 第一行一个整数 $n$。
- 接下来一行，一个长度为 $n - 1$ 的字符串 $c_1c_2\dots c_{n-1}$。

 输出格式

对于每组数据，输出仅一行一个整数，表示符合条件的整数数对个数。

 输入输出样例 1

 输入 1

```
5
5
<<<<
7
<=><=<
9
=<<><==<
11
>=<<=>>>=>
13
=><<=<=>=><>
```

 输出 1

```
10
9
13
29
25
```

**说明/提示**

**样例解释**

- 对于第一组数据，$a_i$ 比 $a_j$ 开心当且仅当 $1 \leq i < j \leq n$，故共有 $\frac{5\times 4}{2} = 10$ 对合法的 $(i, j)$。
- 对于第二组数据，合法的 $(i, j)$ 分别为：$(1, 2), (1, 3), (4, 2), (4, 3), (4, 5), (4, 6), (4, 7), (5, 7), (6, 7)$，共 $9$ 对。
- 对于其他几组数据，聪明的读者可以自行验证。

**数据规模与约定**

**本题采用捆绑测试和子任务依赖。**

- Subtask 0（0 pts）：样例。
- Subtask 1（10 pts）：$n \leq 8$，$T \leq 8$。
- Subtask 2（20 pts）：$n \leq 5000$，$T \leq 8$。依赖于子任务 $0, 1$。
- Subtask 3（20 pts）：$c_i \neq \texttt =$。
- Subtask 4（50 pts）：无特殊限制。依赖于子任务 $0 \sim 3$。

对于所有数据，保证 $2 \leq n \leq 2\times 10^5$，$1 \leq T \leq 10^4$，$c_i \in \{\texttt <, \texttt >, \texttt =\}$，$\sum n \leq 5\times 10^5$。


!!! : 本题在符号的处理上和先前的咕噜论坛很像，写好一个统一的函数，用数值来进行区分
!!! : 本题可以很容易发现单调性是围绕着大于号和小于号进行的。至于等于号则是重点要特判的地方。相比于一开始模拟倍数的想法，设满足单调增的序列数量为a， 满足单调减的区间数量为b， 中间有等号（即无论大于号还是小于号都跳出条件）的序列数量为c， a + b - 2 * c 即为答案（如何推?）

```cpp
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
```

#### 4.14 First One
**题目描述**

soda 有一个整数数组 \( a_1, a_2, \ldots, a_n \)。令 \( S(i, j) \) 为 \( a_i, a{i+1}, \ldots, a_j \) 的和。现在 soda 想知道下面的值：

$\sum_{i=1}^{n} \sum_{j=i}^{n} \left( \lfloor \log_2 S(i, j) \rfloor + 1 \right) \times (i + j)$
注意：在这个问题中，你可以认为 \( \log_2 0 \) 为 0。

**输入**

有多个测试用例。输入的第一行包含一个整数 \( T \)，表示测试用例的数量。对于每个测试用例：

- 第一行包含一个整数 \( n \) \( (1 \leq n \leq 10^5) \)，表示数组中的整数数量。
- 第二行包含 \( n \) 个整数 \( a_1, a_2, \ldots, a_n \) \( (0 \leq a_i \leq 10^5) \)。

**输出**

对于每个测试用例，输出该值。

**示例输入**

```
1
2
1 1
```

**示例输出**

```
12
```

!!! : 对 S(i, j) 求 log 又取整数， 实际上会压缩数据的范围 (2, 4, 8, 16, 32 .....) 且越往后，间隔越大。 条件就是判断有无超出这些个点即可。

!!! : 朴素来说，我们希望的是让 (i + j) 乘上的始终是同一个数字，这样我们就可以直接用等差数列的公式求出来每个区段的答案。 同时， 又要对log有一定的数字敏感度， 知道其会压缩整个区间。

!!! : 两层循环， 实际上这是一个二维平面上的枚举， 想成一维上的滑动窗口你就会浪费一个小时 😦 所以说应该按照如下方式去枚举

!!! : md 数组里全是正数， 枚举过一次就好了 草

``` cpp
for i in [1, n]
    for k in [L, R]
    ( i * (R - L + 1) + (L + R) * (R - L + 1) / 2) * lg 
```
公式记得自己推哦

