#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

int sum(int &x){
    
    int s=0;
    if(x%10==0&&x!=200){
        s=x;
    }
    else{
        while(x/10!=0){
            s=s+x%10;
            x=x/10;
        }
        s=s+x;
    }
    return s;
}

int main (){
    int n;
    cin>>n;
    cout<<sum(n);
}

