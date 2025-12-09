#include<iostream>
using namespace std;
void PrintN(int N){
    if (N>0){
        PrintN(N-1);
        cout<<N<<endl;
    }
}
int main(){
    int N=10;
    PrintN(N);
    return 0;
}





