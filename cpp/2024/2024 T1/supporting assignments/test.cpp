// #include <iostream>

// class Rectangle {
// public:
//     // 默认构造函数
//     Rectangle(void) : mLength(0), mWidth(0) {}

//     // 带参数的构造函数
//     Rectangle(float length, float width) : mLength(length), mWidth(width) {}

//     // 析构函数
//     ~Rectangle(void) {}

//     // 计算面积的函数
//     float getArea() {
//         return mLength * mWidth;
//     }

//     // 计算周长的函数
//     float getGirth() {
//         return 2 * (mLength + mWidth);
//     }

// private:
//     // 私有成员变量，存储长度和宽度
//     float mLength;
//     float mWidth;
// };

// int main() {
//     float m, n;
//     std::cout << "Input the Length and Width: ";
//     std::cin >> m >> n;
//     Rectangle r1(m, n);
//     std::cout << "The Area is: " << r1.getArea() << std::endl;
//     Rectangle r2(m, n);
//     std::cout << "The Perimeter: " << r2.getGirth() << std::endl;
//     return 0;
// }        






// //

// for(int i=0;i<a+b;i++){
//         minimum=arr3[i];
        
//         for(int n=i+1;n<a+b;n++){
//             if(arr3[n]<minimum){
//                 minimum=arr3[n];
//                 k=n;
//             }   
//         }
//         if(minimum<99999999){
//             cout<<minimum<<" ";
//             arr3[k]=99999999;
//         }
//     }
    


 
    
   
   #include <iostream>
using namespace std;

int main() {
double a = 1.499;
double b = 1.500;
double c = 1.48;
double d = 1.5;
double n_a = -1.499;
double n_b = -1.500;

printf("%.2f\n", a); // 1.50
printf("%.2f\n", b); // 1.50
printf("%.2f\n", c); // 1.48
printf("%.2f\n", d); // 1.50
printf("%.2f\n", n_a); // -1.50
printf("%.2f\n", n_b); // -1.50

return 0;
}