#include <stdio.h>
#include <iostream>
#include <cstring>
#define endl '\n'
int ans[105], p = 1, n, x, a[105];
int main(){

	std::cin >> x >> n;
	p = n;
	for(int i = 1;i <= n;i++)ans[i] = x;
	n--;
//	12345
//	54321
	while(n){
		memset(a, 0, sizeof a);
		for(int i = 1;i <= n;i++)a[i] = x;
		for(int i = p - 1;i >= 1;i--){
			ans[i + 1]--;
			ans[i] += 10;
			ans[i] -= a[i];
		}
		for(int i = 1;i <= p;i++){
			ans[i + 1] += ans[i] / 10;
			ans[i] %= 10;
		}
		while(!ans[p])p--;
		n--;
	}
	for(int i = p;i >= 1;i--)std::cout << ans[i];
	std::cout << endl;
	
	return 0;
}