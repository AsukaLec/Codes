#include <iostream>
#include <string>
using namespace std;
int main(){
    int arr[3][3]={
        {'zhangsan',100,100},
        {'lisi',90,90},
        {'wangwu',80,80}
    };
    for(int i=0;i<3;i++){
        for(int n=0;n<3;n++){
            cout<<arr[i][n];
        }
        cout<<endl;



    char arr[3][20]={"tome","sam","damn"};
    for(int i=0;i<3;i++){
        cout<<arr[i];
        cout<<endl;
    }
}
}