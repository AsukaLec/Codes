#include<iostream>
#include<string>
using namespace std;
int judge(const std::string& num1, const std::string& num2) {
    // 比较数字长度
    size_t len1 = num1.length(), len2 = num2.length();
    if (len1 != len2) {
        // 如果长度不同，较长的数字更大
        return len1 > len2 ? 1 : 0;
    }

    // 如果长度相同，逐位比较
    for (size_t i = 0; i < len1; ++i) {
        if (num1[i] != num2[i]) {
            // 如果某一位不同，则比较该位的数值
            return num1[i] > num2[i] ? 1 : 0;
        }
    }

    // 如果所有位都相同，则两个数字相等
    return 0;
}

void add(const string& x, const string& y){
    int a[55], b[55], ans[110];
    for(int i=0;i<110;i++){
		ans[i]=0;
	}
    int xlen=x.size();
    int ylen=y.size();
    for(int i=0;i<xlen;i++) a[i]=x[xlen-i-1]-'0';
    for(int i=0;i<ylen;i++) b[i]=y[ylen-i-1]-'0';
    
    if(judge(x,y)==1){
        for(int i = 0;i < ylen;i++){
			ans[i] += a[i] + b[i];
			if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
			}
		}
		for(int i = ylen;i < xlen;i++){
			ans[i]+=a[i];
			if(ans[i]>9){
			    ans[i]-=10;
			    ans[i+1]+=1;
			}
		}
	}
    else{
        for(int i = 0;i < xlen;i++){
			ans[i] += a[i] + b[i];
			if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
			}
		}
		for(int i = xlen;i < ylen;i++){
			ans[i]+=b[i];
			if(ans[i]>9){
			    ans[i]-=10;
			    ans[i+1]+=1;
			}
		}
	}
	int w=109;
	while(ans[w]==0){
		w-=1;
	}
    if(w>=0){
		for(int i=w;i>=0;i--){
			cout<<ans[i];
		}
		cout << endl;
		}
	else{
		cout<<0<<endl;
	}              
    
}

int main(){
    string a,b;
    b='1';
    cin>>a;
    add(a,b);
}