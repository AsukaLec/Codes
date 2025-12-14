// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     cin.tie(0) -> sync_with_stdio(false);
//     int ws, kk;
//     while(true) {
//         cin >> ws;
//         cout << "Hello, World!" << endl;
//         cin >> kk;
//         cout << "Goodbye, World!" << endl;
//     }
// }
//cin.tie(0) -> sync_with_stdio(false); 这是干嘛的
// 这行代码的作用是提高输入输出的效率。
// 在C++中，标准输入输出流（cin和cout）默认是与C语言的标准输入输出流（scanf和printf）同步的。
// 这种同步会导致一些性能开销，特别是在大量输入输出操作时。
// 通过调用cin.tie(0)，我们将cin与cout解绑，意味着cin不会再自动刷新cout。
// 通过调用sync_with_stdio(false)，我们禁用了C++标准库与C标准库之间的同步。
// 这样做可以显著提高输入输出的速度，尤其是在需要频繁进行输入输出操作的情况下。
// 需要注意的是，一旦禁用了同步，就不能再混合使用C和C++的输入输出函数，否则可能会导致未定义行为。
// 总的来说，这行代码主要用于优化程序的输入输出性能，适用于对效率要求较高的场景。   
// 另外，cin.tie(0) 返回的是一个指向之前绑定的ostream对象的指针，
// 这里使用了箭头操作符（->）来调用sync_with_stdio(false)方法，这是一种链式调用的写法。
// 这种写法在C++中是合法的，因为cin.tie(0)返回的指针类型允许我们直接调用其成员函数。
// 这种链式调用的写法在实际代码中并不常见，但它确实可以工作，并且在某些情况下可以使代码更简洁。
// 综上所述，这行代码的主要目的是为了提高输入输出的效率，
// 并且使用了链式调用的方式来实现这一点。


#include <bits/stdc++.h>
using namespace std;

int main() {
    double ax, ay, bx, by;
    cin >> ax >> ay >> bx >> by;
    int n = 8;
    int x[8] = {2, 2, 8, 5, 7, 6, 1, 4};
    int y[8] = {10, 5, 4, 8, 5, 4, 2, 9};

    while(n --) {
        int cx, cy;
        cx = x[ 7 - n];
        cy = y[ 7 - n];

        cout << "Point (" << cx << ", " << cy << "):\n";
        cout << "to a: "<< sqrt((cx - ax) * (cx - ax) + (cy - ay) * (cy - ay)) << '\n';
        cout << "to b: "<< sqrt((cx - bx) * (cx - bx) + (cy - by) * (cy - by)) << '\n';
        cout << "--------" << '\n' << '\n';
    }
}