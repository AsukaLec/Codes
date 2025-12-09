#include <iostream>
#include <string>
using namespace std;

int main(){
string m;
cin>>m;
int n=m.size();
for(int i=m-1;i>=0;i--){
    cout<<m[i];
}
}