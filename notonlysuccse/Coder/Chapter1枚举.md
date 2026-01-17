[TOC]

# <center> 一、枚举算法
***
## 1.1 lq19709 匿名函数&判断奇偶
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

## 1.2 lq3491 匿名函数&幸运数
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

## 1.3 lq1443 运用vector建立类似字典的效果
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


## 1.4 lq1065 标准化输入&枚举判断
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

## 1.5 lq19732 反弹问题 按时间枚举
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

## 1.6 lq3495 闰年判断 注意有坑
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

## 1.7 lq3492 子串匹配枚举 有函数可以用
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

## 1.8 lq19730 大模拟 向下取整
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

## 1.9 P1179
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

## 1.10 P1149 火柴棒 粗略判断上界
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
