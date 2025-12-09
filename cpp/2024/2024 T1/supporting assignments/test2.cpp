#include<iostream>
#include<cmath>
using namespace std;



int weishu(int a){
    int n=1;
    while(a/10!=0){
        n=n+1;
    }
    return n;
}

int main(){
    int i;
    cin>>i;
    int power=0;
    int c,d;

    power=i*i;
        c=weishu(i);
        cout<<power<<" "<<c<<endl;
        int k;
        k=power/pow(10,c);
        d=power-k*pow(10,c)
        
        cout<<d;

}
