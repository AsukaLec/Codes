// #include <iostream>
// #include <string>
// using namespace std;
// int main(){
//     string a="100";
//     string b="1000";
//     a -=b;
//     cout<<b;
// }
#include <iostream>
#include <string>

int main() {
    // 初始化字符串
    std::string str = "Hello";

    // 增加字符串
    std::string addStr = " World";
    str += addStr; // 使用+=运算符
    std::cout << "After adding: " << str << std::endl; // 输出: Hello World

    // 删除字符串
    str.erase(5, 6); // 删除从位置5开始的6个字符
    std::cout << "After deleting: " << str << std::endl; // 输出: Hello

    return 0;
}