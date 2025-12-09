# include <bits/stdc++.h>
using namespace std;
int a[10]={0}, b[10]={0}, ans[10]={0};


void add(int *a, int *b, int *ans){
        for(int i = 0;i < 10;i++){
			ans[i] += a[i] + b[i];

		}
        for(int i = 0; i<10; i++){
            if(ans[i]>9){
				ans[i]-=10;
				ans[i+1]+=1;
			}
        }

        for(int i = 0; i<10; i++){
            a[i] = b[i];
            b[i] = ans[i];
            ans[i] = 0;
        }

        
}


int main(){
   
    int n = 
    a[0] = 1;
    b[0] = 1;
    n-=1;
    while(n--){
        add(a, b, ans);
    }
    
    int w=999; //output
	while(a[w]==0){
		w-=1;
	}
    if(w>=0){
		for(int i=w;i>=0;i--){
			cout<<a[i];
		}
		cout << endl;
		}
	else{
		cout<<0<<endl;
	}              
    
    
}