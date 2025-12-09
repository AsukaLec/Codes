#include<iostream>
#include<math.h>
using namespace std;

int main(){
    while (true) {
        double total, k1,k2;
        cin >> total >> k1;
        k2 = total - k1;
        double ans = -(k1/total * log2(k1/total) + k2/total * log2(k2/total));
        cout << ans << endl;
    }
}