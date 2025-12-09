#include <iostream>
#include <string>
using namespace std;

int main() {
    string str1;
    string str2;
    getline(cin, str1);
    getline(cin, str2);
    int n=str1.size();
    int m=str2.size();

    char arr0[26];
    for(int i=0;i<26;i++){
        arr0[i]=i+65;
    }

    char a=0;
    int t=1;
    int k=0;
    
    for(int i=0;i<m;i++){
       
        if(t%n==0){
            a=str1[n-1];
        }
        else{
            a=str1[t%n-1];
        }
        k=int(a)-65;
        
        for(int i=0;i<26;i++){
            arr0[i]=(k+int(arr0[i])-65)%26+65;
        }

        if(str2[i]<65 ||str2[i]>90){
            cout<<str2[i];
        }
        else{
            cout<<arr0[str2[i]-65];
        }
        
        for(int i=0;i<26;i++){
        arr0[i]=i+65;
        }

        t+=1;
    }
    cout<<endl;
}