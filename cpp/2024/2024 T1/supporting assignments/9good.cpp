#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

// 函数用于删除字符串中的特定字符
string removeChar(const string& str, char ch) {
    string result;
    for (char c : str) {
        if (c != ch) {
            result += c;
        }
    }
    return result;
}

int add(int bb,int cc){
    cout<<"   ";
}


int main() {
    const int MAX_STRINGS = 30;
    const int MAX_LENGTH = 31; // 包括空字符'\0'
    char ch;
    string strings[MAX_STRINGS];
    string input;

    // 读取需要删除的字符
    cin >> ch;

    int count = 0;
    while (getline(cin, input) && input != "@") {
        // if (count < MAX_STRINGS) {
        //     strings[count++] = removeChar(input, ch);
        // } else {
        //     // 如果超过字符串数量限制，输出错误信息并退出
        //     cerr << "Error: Exceeded maximum number of strings." << endl;
        //     return 1;
        // }
        strings[count++] = removeChar(input, ch);
    }

    // 逆序排序字符串数组
    sort(strings, strings + count, greater<string>());

    // 输出排序后的字符串   
    for (int i = 0; i < count; ++i) {
        if(strings[i][0]!='@'){
            cout << strings[i] << endl;
        }
        
    }

    return 0;
}