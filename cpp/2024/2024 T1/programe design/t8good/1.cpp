#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;


// string formatNumber(int value) {
//     ostringstream oss;
//     oss << setw(5) << setfill(' ') << right << value;
//     return oss.str();
// }

int main() {
 int a[100];
    char d;
    int t = 0;
    for (int i = 0; i < 100; i++) {

            cin >> a[i];
           d = cin.get();


           if (d == 10) {
             t = i + 1; break;
         }
        }

//不完全等价。cin.get() 和 cin >> d; 在C++中都用于从标准输入读取数据，但它们的行为和用途有所不同：

// cin >> d;：

// 这是一个提取运算符（extraction operator），用于从输入流中读取格式化的数据。
// 它主要用于读取数据类型为int、float、double、char等基本数据类型的值。
// 当用于读取char类型时，cin >> d;会跳过任何空白字符（如空格、制表符、换行符等），直到遇到非空白字符，然后读取该字符。
// cin.get(d);：

// 这是一个成员函数，用于从输入流中读取单个字符，并将其存储在提供的变量中。
// 它可以读取任何类型的字符，包括空白字符。
// cin.get(d);会读取下一个可用的字符，无论它是空白字符还是非空白字符。
// 因此，cin.get(d); 更通用，可以读取任何类型的字符，包括那些cin >> d;会跳过的空白字符。而cin >> d;主要用于读取非空白字符，并且适用于基本数据类型的值。如果你想要读取一个字符，包括可能的空白字符，那么cin.get(d);是更合适的选择。
   
    int b[t][t];
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {

           if(i==0) b[i][j] = a[j];
           if (i != 0) cin >> b[i][j];
        }

    }
    
    char fuhao;
    cin >> fuhao;
    int e[t][t];
    for (int i = 0; i < t; i++) {
        for (int j = 0; j < t; j++) {

            cin >> e[i][j];
        }
    }


    switch (fuhao) {
    case '+':
    
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                
                cout<<setw(5)<<b[i][j] + e[i][j];
            }
            cout << endl;
            }
        
        break;
       
        

    case '-':
    
       for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                
                cout<<setw(5)<<b[i][j] - e[i][j];
            }
            cout << endl;
            }
        

        break;

    case '*':
       int ji[t][t];
        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {

                ji[i][j] = 0;

            }
        }

        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                for (int k = 0; k < t; k++) {

                    ji[j][i] += b[j][k] * e[k][i];

                }
            }
        }

        for (int i = 0; i < t; i++) {
            for (int j = 0; j < t; j++) {
                cout<<setw(5)<<ji[i][j];
            }
            cout << endl;
        }
        break;
      }

    return 0;
}

// #include <iostream>
// #include <iomanip>
// #include <sstream>
// #include <string>
// using namespace std;


// string formatNumber(int value) {
//     ostringstream oss;
//     oss << setw(5) << setfill(' ') << right << value;
//     return oss.str();
// }

// int main() {
//  int a[100];
//     char d;
//     int t = 0;
//     for (int i = 0; i < 100; i++) {

//             cin >> a[i];
//            d = cin.get();
//            if (d == 10) { t = i + 1; break; }
//         }
//     int b[t][t];
//     for (int i = 0; i < t; i++) {
//         for (int j = 0; j < t; j++) {

//            if(i==0) b[i][j] = a[j];
//            if (i != 0) cin >> b[i][j];


//         }


//     }
//     char fuhao;
//     cin >> fuhao;
//     int e[t][t];
//     for (int i = 0; i < t; i++) {
//         for (int j = 0; j < t; j++) {

//             cin >> e[i][j];
//         }
//     }


//     switch (fuhao) {
//     case '+':
//         for (int i = 0; i < t; i++) {
//             for (int j = 0; j < t; j++) {
//                 int sum = b[i][j] + e[i][j];
//                 cout << formatNumber(sum) << " ";
//             }
//             cout << endl;
//         }
//         break;

//     case '-':
//         for (int i = 0; i < t; i++) {
//             for (int j = 0; j < t; j++) {
//                 int jian = b[i][j] - e[i][j];
//                 cout << formatNumber(jian) << " ";
//             }
//             cout << endl;
//         }
//         break;

//     case '*':
//        int ji[t][t];
//         for (int i = 0; i < t; i++) {
//             for (int j = 0; j < t; j++) {

//                 ji[i][j] = 0;

//             }
//         }


//         for (int i = 0; i < t; i++) {
//             for (int j = 0; j < t; j++) {
//                 for (int k = 0; k < t; k++) {

//                     ji[j][i] += b[j][k] * e[k][i];




//                 }


//             }
//         }


//         for (int i = 0; i < t; i++) {
//             for (int j = 0; j < t; j++) {
//                 cout << formatNumber(ji[i][j]);
//             }
//             cout << endl;
//         }
//         break;
//     }

//     return 0;
// }