#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<stack>
using namespace std;
stack<int>S;
char a[100005], b[100005];
char c[100005];
void dfs(int anow,int bnow,int clen) {
	//anow 原字符串已经入栈了多少位   bnow 已出栈的已经符合目标字符串多少位 clen 解决方案已存储字符数量
	if (clen == strlen(b) * 2) {
		//由于每一次调用函数均会判断是否符合，故只要c种存了len个i，即len个o，就说明当前方案符合要求
		for (int i = 0; i < clen; i++)
			cout << c[i] << " ";
		cout << endl;
	}

	//若原字符串未入栈完，则尝试入栈并调用函数
	if (anow < strlen(a)) {
		//入栈操作
		S.push(a[anow]);
		c[clen] = 'i'; 
		//尝试入栈一位
		dfs(anow + 1, bnow , clen + 1); 
		//将栈还原供后续操作
		S.pop();
	}

	//若栈顶元素与目标字符串当前位置相同，则可尝试出栈
	if (!S.empty() && S.top() == b[bnow]) {
		//出栈操作
		S.pop();
		c[clen] = 'o';
		//尝试出栈
		dfs(anow, bnow + 1, clen + 1);
		//还原
		S.push(b[bnow]);
	}
	return;
}
int main() {
	while (scanf("%s%s", a, b) != EOF) {
		cout << "[" << endl;
		dfs(0,0,0);
		cout << "]" << endl;
	}
}


