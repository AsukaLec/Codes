#include<iostream>
using namespace std;

    void PrintN (int N){
    int i ;
    for (i =1; i<N ; i++){
        cout<<i;
    }
}

int main(){
    int N = 10;
    PrintN(N);
    return 0;
}