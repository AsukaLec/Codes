// #include <iostream>

// // 交换两个字符的函数
// void swap(char &a, char &b) {
//     char temp = a;
//     a = b;
//     b = temp;
// }

// // 递归函数来生成全排列
// void permute(char *a, int start, int end) {
//     if (start == end) {
//         // 打印当前排列
//         for (int i = 0; i <= end; i++) {
//             std::cout << a[i]<<" ";
//         }
//         std::cout << std::endl;
//     } else {
//         for (int i = start; i <= end; i++) {
//             // 固定当前位置的数字
//             swap(a[start], a[i]);
//             // 递归生成剩余数字的排列
//             permute(a, start + 1, end);
//             // 回溯，撤销上一步操作
//             swap(a[start], a[i]);
//         }
//     }
// }

// int main() {
//     int N;

//     std::cin >> N;

//     // 创建一个字符数组来存储数字
//     char a[N + 1];

//     // 初始化字符数组
//     for (int i = 1; i <= N; i++) {
//         a[i] = '0' + i; // 将数字转换为字符
//     }
//     a[0] = '\0'; // 字符串结束符

//     // 生成并打印全排列
    
//     permute(a, 1, N);

//     return 0;
// }

#include <iostream>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void permute(int arr[], int start, int end) {
    if (start == end) {
        printArray(arr, end + 1);
    } else {
        for (int i = start; i <= end; i++) {
            swap(&arr[start], &arr[i]);
            permute(arr, start + 1, end);
            swap(&arr[start], &arr[i]); // backtrack
        }
    }
}

int main() {
    int N;

    std::cin >> N;



    int *arr = new int[N];
    for (int i = 0; i < N; i++) {
        arr[i] = i + 1;
    }

    permute(arr, 0, N - 1);
    delete[] arr;
    return 0;
}
