#include <iostream>
#include <string>
#include <iostream>
#include <bitset>

// std::string to_binary(unsigned int n) {
//     if (n == 0) return "0";
//     std::string result;
//     while (n > 0) {
//         result = (n % 2 ? "1" : "0") + result;
//         n /= 2;
//     }
//     return result;
// }

int main() {
    // int num = 42;
    // std::cout << to_binary(num) << std::endl;  // 输出：101010    
    while(true){
        int num1 = 42;
        std::cin >> num1 ;
        std::bitset<8> binary(num1);  // 8 位二进制
        std::cout << binary << std::endl;  // 输出：00101010
    }

}
