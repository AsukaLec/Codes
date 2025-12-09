//本题因为结果的位数可能到1000位，故需要使用高精度加法进行计算。
//同时本题要注意多测（卡了两个钟）。

# include <bits/stdc++.h>
using namespace std;
int a[1020]={0}, b[1020]={0}, ans[1020]={0};

void add(int *a, int *b, int *ans){
        for(int i = 0;i < 1020;i++){
			ans[i] += a[i] + b[i];

		}
        for(int i = 0; i<1020; i++){
            if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
			}
        }

        for(int i = 0; i<1020; i++){
            a[i] = b[i];
            b[i] = ans[i];
            ans[i] = 0;
        }
}

int main(){
    int n;
    
    while(cin>>n){
        n-=1;
        a[0] = 1;
        b[0] = 1;
        while(n--){
            add(a, b, ans);
        }
        int w=1019; //output
        while(a[w]==0){
            w-=1;
        }
        if(w>=0){
            for(int i=w;i>=0;i--){
                cout<<a[i];
            }
        cout<<endl;
            }
        else{
            cout<<0<<endl;
        }
        for(int i = 0; i<1020;i++){
            a[i]=0;
            b[i]=0;
            ans[i]=0;
        }
        a[0] = 1;    
        b[0] = 1;
    }
    
}