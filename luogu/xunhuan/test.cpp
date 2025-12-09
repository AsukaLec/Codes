#include <iostream>
#include <string>
using namespace std;
int main(){
    string m;
    m="0";
    char arr[]="fuckyou world";
    int n=13;
    for(int i=0;i<n;i++){
        m+=arr[i];
    }
    cout<<m;

}