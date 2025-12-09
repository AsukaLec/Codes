#include <iostream>
#include <string>
using namespace std;

int main() {
    string str1;
    string str2;
    getline(cin, str1); // 使用getline读取带空格的字符串
    getline(cin, str2); 
    int n=((str1.size())-1)/2;
    int m=((str2.size())-1)/2;
    int arr1[n];
    for(int i=0;i<n;i++){
        arr1[i]=str1[2*i]-'0';
    }
    int arr2[m];
    for(int i=0;i<m;i++){
        arr2[i]=str2[2*i]-'0';
    }

    for(int i=0;i<n;i++){
        int t=0;
        for(int k=0;k<m;k++){
            if(arr1[i]==arr2[k]){
                t+=1;
            }
        }

        if(t==0){
            cout<<arr1[i]<<" ";
        }
    }
}




// 在C++中，如果你有一个字符串，其内容全部由数字组成，并且你想要将这些数字存储到一个整型数组中，你可以使用以下几种方法：

// ### 方法1：使用`std::stoi`函数

// `std::stoi`函数可以将字符串转换为`int`类型。你可以遍历字符串，逐个字符转换，然后存储到数组中。

// ```cpp
// #include <iostream>
// #include <string>
// #include <vector>

// int main() {
//     std::string str = "123456789"; // 假设这是你的字符串
//     std::vector<int> arr; // 使用vector动态数组，因为不知道字符串长度

//     for (char c : str) {
//         arr.push_back(c - '0'); // 将字符转换为对应的数字
//     }

//     // 打印数组内容
//     for (int num : arr) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
// ```

// ### 方法2：使用`std::stringstream`

// `std::stringstream`可以用来从字符串中提取数字。

// ```cpp
// #include <iostream>
// #include <sstream>
// #include <vector>

// int main() {
//     std::string str = "123456789";
//     std::vector<int> arr;
//     std::stringstream ss(str);

//     int num;
//     while (ss >> num) {
//         arr.push_back(num);
//     }

//     // 打印数组内容
//     for (int num : arr) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
// ```

// ### 方法3：使用`std::stoi`和循环

// 如果你想要将字符串中的每个字符都转换为数字，并且存储到数组中，可以使用`std::stoi`。

// ```cpp
// #include <iostream>
// #include <string>
// #include <vector>

// int main() {
//     std::string str = "123456789";
//     std::vector<int> arr;

//     for (size_t i = 0; i < str.length(); i += 1) {
//         arr.push_back(str[i] - '0'); // 将字符转换为对应的数字
//     }

//     // 打印数组内容
//     for (int num : arr) {
//         std::cout << num << " ";
//     }
//     std::cout << std::endl;

//     return 0;
// }
// ```

// 以上方法都可以将字符串中的数字字符转换为整数，并存储到数组中。你可以根据实际情况选择最适合你需求的方法。