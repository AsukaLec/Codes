#include <bits/stdc++.h>
using namespace std;
long long sum = 0;

void GetAnswer (int n, int k){
    if (k == 2) {
        sum += (n + 1)/2;
    }
    else {
        int a = 1, b = n;
        int times = 1;
        while(a<=b){
            GetAnswer(times , k-1);
            a += 1;
            b -= 1;
            times += 1;
        }
    }
}

int main(){
    int n, k;
    cin>> n >> k;
    
    GetAnswer(n + 1 -k,k);
    cout<< sum;
}