// #include <iostream>
// #include <cstring>
// #include <stdio.h>
// #define endl '\n'
// int a[105], b[105], ans[205];
// int main(){
// //	9999
// //	*
// //	9999
// //  10
	
//     	freopen("plus.in", "r", stdin);
//     	freopen("plus.out", "w", stdout);
//     fclose(stdin);
// 	fclose(stdout);
    
//     std::string x, y;
// 	char opt;
// 	std::cin >> x >> opt >> y;
// 	int xlen = x.size(), ylen = y.size();
// 	x = " " + x;
// 	y = " " + y;
// 	int ap = xlen, bp = ylen;
// 	for(int i = xlen;i >= 1;i--)a[i] = x[i] - '0';
// 	for(int i = ylen;i >= 1;i--)b[i] = y[i] - '0';
// 	if(opt == '+'){
// 		for(int i = 1;i <= std::max(xlen, ylen);i++)
// 			ans[i] = a[i] + b[i];
// 		int p = std::max(xlen, ylen);
// 		for(int i = 1;i <= p;i++){
// 			ans[i + 1] += ans[i] / 10;
// 			ans[i] %= 10;
// 		}
// 		while(ans[p] > 10){
// 			ans[p + 1] += ans[p] / 10;
// 			ans[p] %= 10;
// 			p++;
// 		}
// 		for(int i = p;i >= 1;i--)std::cout << ans[i];
// 		std::cout << endl;
// 	}else{
// 		//123456789 * 0
// 		for(int i = 1;i <= ap;i++)
// 			for(int j = 1;j <= bp;j++)
// 				ans[i + j - 1] = a[i] * b[j];
// 		int p = ap + bp - 1;
// 		for(int i = 1;i <= p;i++){
// 			ans[i + 1] += ans[i] / 10;
// 			ans[i] %= 10;
// 		}
// 		while(ans[p] > 10){
// 			ans[p + 1] += ans[p] / 10;
// 			ans[p] %= 10;
// 			p++;
// 		}
// 		while(!ans[p])p--;
// 		if(p <= 0)std::cout << 0;
// 		for(int i = p;i >= 1;i--)std::cout << ans[i];
// 		std::cout << endl;
// 	}
// 	return 0;
// }


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(){
	int a[105], b[105], ans[205];
	ifstream input("plus.in");
	ofstream output("plus.out");

	for(int i=0;i<205;i++){
		ans[i]=0;
	}

	string x;
	string y;
	char opt;
	input >> x >> opt >> y;

	int xlen = x.size(), ylen = y.size();

	for(int i = 0;i < xlen ;i++) a[i] = x[xlen-i-1] - '0';
	for(int i = 0;i < ylen ;i++) b[i] = y[ylen-i-1] - '0';

	int p = min(xlen, ylen);
	int q = max(xlen, ylen);

	if(opt == '+'){
		for(int i = 0;i < p;i++){
			ans[i] += a[i] + b[i];
			if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
			}
		}
			
		if(q==xlen){
			for(int i = p;i < q;i++){
				ans[i]+=a[i];
				if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
				}
			}
		}
		else{
			for(int i = p;i < q;i++){
				ans[i]+=b[i];
				if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
				}
			}
		}
	 	
		int w=204;
		while(ans[w]==0){
			w-=1;
		}
		
			if(w>=0){
				for(int i=w;i>=0;i--){
					output<<ans[i];
			}
			output << endl;
			}
			else{
				output<<0<<endl;
			}
	}
	
	
	else{
		if(q==xlen){
			for(int i=0;i<p;i++){
				for(int k=0;k<q;k++){
					ans[i+k] += a[k]*b[i];
				}
			}

			for(int i=0;i<160;i++){
				if(ans[i]>9){
					string m= to_string(ans[i]);
					int mlen=m.size();
					
					ans[i]=m[mlen-1]-'0';

					for(int k=i+1;k<mlen+i;k++){
						ans[k] += m[mlen-1-(k-i)]-'0';
					}
				}
			}
			int w=204;
			while(ans[w]==0){
				w-=1;
			}
		
			if(w>=0){
				for(int i=w;i>=0;i--){
					output<<ans[i];
			}
			output << endl;
			}
			else{
				output<<0<<endl;
			}
		}

		else{
			for(int i=0;i<p;i++){
				for(int k=0;k<q;k++){
					ans[i+k] += b[k]*a[i];
				}
			}

			for(int i=0;i<160;i++){
				if(ans[i]>9){
					string m= to_string(ans[i]);
					int mlen=m.size();
					
					ans[i]=m[mlen-1]-'0';

					for(int k=i+1;k<mlen+i;k++){
						ans[k] += m[mlen-1-(k-i)]-'0';
					}
				}
			}
			int w=204;
			while(ans[w]==0){
				w-=1;
			}
			
			if(w>=0){
				for(int i=w;i>=0;i--){
					output<<ans[i];
			}
			output << endl;
			}
			else{
				output<<0<<endl;
			}

		}


	}

	input.close();
	output.close();
}