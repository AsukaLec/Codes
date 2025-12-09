#include <iostream>
#include <string>
using namespace std;
int main(){
    string str;
    char ch;
    cin>>str>>ch;
    int n=str.size();
    int t=0;
    for(int i=0;i<n;i++){
        if(str[i]==ch){
            cout<<i<<" ";
            t+=1;
        }
    }

    if(t==0){
        cout<<"NULL";

    }

    
    
}