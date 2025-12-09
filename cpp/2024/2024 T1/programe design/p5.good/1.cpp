#include <iostream>
#include <fstream>
using namespace std;
int main(){
ifstream inputFile("dlist.in");
ofstream outputFile("dlist.out");

    int n;
    inputFile>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        inputFile>>arr[i];
    }
    int k;
    inputFile>>k;

    for(int i=n-1;i>-1;i--){
        if(arr[i]!=k){
            outputFile<<arr[i]<<" ";

        }
        else{
            n-=1;

        }
    }
    if(n==0){
        outputFile<<-1;
    }
    inputFile.close();
    outputFile.close();
    
    return 0;
    
}

// #include <iostream>
// #include <fstream>
// #include <vector>
// using namespace std;

// int main() {
//     // 打开输入文件
//     ifstream inputFile("dlist.in");
//     // 打开输出文件


//     // 检查文件是否成功打开
//     if (!inputFile.is_open() || !outputFile.is_open()) {
//         cerr << "Error opening file!" << endl;
//         return 1;
//     }

//     int n;
//     inputFile >> n;
//     vector<int> arr(n);
//     for (int i = 0; i < n; i++) {
//         inputFile >> arr[i];
//     }
//     int k;
//     inputFile >> k;

//     // 使用迭代器来移除等于k的元素
//     vector<int>::iterator it = arr.begin();
//     while (it != arr.end()) {
//         if (*it == k) {
//             it = arr.erase(it); // erase返回下一个元素的迭代器
//         } else {
//             ++it;
//         }
//     }

//     // 打印结果到输出文件
//     bool found = false;
//     for (int num : arr) {
//         outputFile << num << " ";
//         found = true;
//     }
//     if (!found) {
//         outputFile << -1;
//     }

//     // 关闭文件


//     return 0;
// }