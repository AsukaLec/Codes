//通过观察可以发现，本题实际上只需考虑定义的数组中每个数对于3的余数。因为项与项之间是相加的关系，那么每个数对于3的余数在数列中也满足相加关系。
//通过观察原数组可以发现，从数列的第二项开始，每隔四项就会出现一个符合题目要求的数字。

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while(cin>>n){
        if(n % 4 ==2) cout<< "yes" <<endl;
        else cout<< "no"<<endl; 
    }
}