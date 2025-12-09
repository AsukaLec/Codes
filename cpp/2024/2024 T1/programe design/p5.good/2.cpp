// #include <iostream>
// using namespace std;


// #include <string>

// int main() {
//     string str1;
//     string str2;
//     cin>>str1>>str2;
//     int n=str1.size();
//     int m=str2.size();

//     char arr[n+m];
    

//     for (int i = 0; i < n; ++i) {
//         arr[i] = str1[i];
//     }
//     for (int i = n; i < m+n; ++i) {
//         arr[i] = str2[i-n];
//     }

//     for(int i=0; i<n+m-1; i++){
//         int min = i;
//         for(int k=i+1; k<n+m; k++){
//             if (arr[min]>arr[k]){
//                 min = k; 
//             }
//         }
//         if (min!=i){
//             swap(arr[min],arr[i]);
//         }
//     }

//     for(int i=0;i<n+m;i++){
//         cout<<arr[i];
//     }
// }


#include <iostream>
#include <cstring>
using namespace std;

string* str_bin(string* str1, string* str2)
{

 strcat(str1,str2);
 for(short i=0; i<size(str1); i++)
 for(short j=i+1, char temp=str1[i]; j<strlen(str1); j++)
if(str1[i]>str1[j])
 {
str1[i]=str1[j];
str1[j]=temp;
temp=str1[i];
}
 return str1;
}



int main()
{

string  *str1,*str2;

string  str11="abcd";
string  str22="efgt";




cout<<str_bin(str1, str2);
return 0;
}

 // for (int i = 0; i < n-1; i++) {
	// 	int min = i;
	// 	for (int j = i; j < n; j++) {
	// 		if (arr[min] > arr[j]) {
	// 			min = j;
	// 		}
	// 	}
	// 	if (min != i) {
	// 		swap(arr[i], arr[min]);
	// 	}
    // }

// std::string str = "Hello, World!";
//     char charArray[str.size() + 1]; // 创建一个足够大的char数组，包括空终止符的位置

//     // 遍历std::string对象并将每个字符复制到char数组中
//     for (size_t i = 0; i < str.size(); ++i) {
//         charArray[i] = str[i];
//     }

//     // 手动添加字符串结束符'\0'
//     charArray[str.size()] = '\0';

//     // 现在charArray包含了字符串
//     std::cout << "charArray: " << charArray << std::endl;

//     return 0;