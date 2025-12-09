#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

// 升序排序
int compare_strings(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    return strcmp(str_a, str_b);
}

int main() {
    char ch;
    scanf("%c", &ch);

    char *strings[MAX_STRINGS];
    int count = 0;
    char input[MAX_LENGTH];

    // 读取字符串直到输入"@"
    while (scanf("%s", input) == 1 && strcmp(input, "@") != 0) {
        strings[count] = (char *)malloc((strlen(input) + 1) * sizeof(char));
        strcpy(strings[count], input);
        count++;
    }

    // 移除字符串中的字符'ch'
    for (int i = 0; i < count; i++) {
        char *str = strings[i];
        char *src = str, *dst = str;
        while (*src) {
            if (*src != ch) {
                *dst++ = *src;
            }
            src++;
        }
        *dst = '\0'; // 确保字符串以空字符结尾
    }

    // 使用qsort进行升序排序
    qsort(strings, count, sizeof(char *), compare_strings);

    // 按升序输出排序后的字符串
    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]); // 释放动态分配的内存
    }

    return 0;
}