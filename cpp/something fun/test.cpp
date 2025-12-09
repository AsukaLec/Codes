// #include <iostream>
// #include <algorithm> // 用于 std::abs

// // 函数声明
// int gcd(int a, int b); // 最大公约数函数
// int lcm(int a, int b); // 最小公因数函数

// int main() {
//     int num1, num2;
//     std::cout << "Enter two numbers: ";
//     std::cin >> num1 >> num2;
//     std::cout << "The LCM of " << num1 << " and " << num2 << " is " << lcm(num1, num2) << std::endl;
//     return 0;
// }

// // 最大公约数函数定义
// int gcd(int a, int b) {
//     while (b != 0) {
//         int temp = b;
//         b = a % b;
//         a = temp;
//     }
//     return a;
// }

// // 最小公因数函数定义
// int lcm(int a, int b) {
//     return std::abs(a * b) / gcd(a, b);
// }   

// #include <bits/stdc++.h>
// using namespace std;
// int main(){
//     int n;
//     cin >> n;
//     int ans[n + 1] = {0};
//     int k = n -1 ;

//     while (k --) {
//         int a,b;
//         cin >> a >> b;
//         ans[a] += 1;
//         ans[b] += 1;
//     }
//     int times = 0;
//     int head = -1, end = -1;
//     for (int i = 1; i <= n; i++){
//         if (ans[i] == 1) {
//             times += 1;
//             if (head == -1) {
//                 head = ans[i];
//                 continue;
//             }
//             if (end == -1) {
//                 end = ans[i];
//                 continue;
//             }
//         }
//     }
//     if (times == 2) cout << head << " " << end;
//     else cout << -1;
    
// }

#include<cstdio>
#include<queue>
using namespace std;
priority_queue <int,vector<int>,less<int> > p;
priority_queue <int,vector<int>,greater<int> > q;
int a[5]={10,12,14,6,8};
int main()
{
	for(int i=0;i<5;i++)
		p.push(a[i]),q.push(a[i]);
		
	printf("less<int>:");
	while(!p.empty())
		printf("%d ",p.top()),p.pop();	
		
	printf("\ngreater<int>:");
	while(!q.empty())
		printf("%d ",q.top()),q.pop();
}
