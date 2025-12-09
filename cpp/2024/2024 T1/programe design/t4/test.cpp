#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
using namespace std;

int sum(int &x){
    int n=0;
    while(x/10!=0){
        x=x/10;
        n=n+1;
    }
    char str[n];

}

int main (){
    
}




int sum_of_digits(int num) {
    string str = to_string(num);
    int sum = 0;

    for (char digit : str) {
        sum += digit - '0';
    }

    return sum;
}

int sum_of_digits_string(int num) {
    string str = to_string(num);
    int sum = accumulate(str.begin(), str.end(), 0,
        [](int total, char digit) -> int {
            return total + (digit - '0');
        });
    return sum;
}

int main() {
    int num = 12345;
    std::cout << "The sum of digits of " << num << " is " << sum_of_digits_string(num) << std::endl;
    return 0;
}
