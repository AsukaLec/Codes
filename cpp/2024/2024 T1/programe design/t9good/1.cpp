#include <iostream>
#include <string>
using namespace std;
int main(){
    string str;
    cin>>str;
    int n=str.size();
    char arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = str[i];
    }
    cout<<arr;
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

    // for(int i=1;i<n;i++){
    //     if(arr[i]==arr[i-1]){
    //         arr[i-1]='0';
    //     }
    // }
    // for(int i=0;i<n;i++){
    //     if(arr[i]>96){
    //         cout<<arr[i];
    //     }
    // }

}