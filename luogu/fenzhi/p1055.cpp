#include<iostream>
#include<string>
using namespace std;
int main(){
    int sum=0;
    string m;
    getline(cin,m);
    m.erase(1,1);
    m.erase(4,1);
    m.erase(9,1);
    for(int i=0;i<9;i++){
        sum+=(m[i]-'0')*(i+1);
    }
    sum=sum%11;
    if(sum==10){
        if(m[9]=='X') cout<<"Right";
        else cout<<m[0]-'0'<<'-'<<m[1]-'0'<<m[2]-'0'<<m[3]-'0'<<'-'<<m[4]-'0'<<m[5]-'0'<<m[6]-'0'<<m[7]-'0'<<m[8]-'0'<<"-X";
    }
    else{
        if(sum==(m[9]-'0')) cout<<"Right";
        else cout<<m[0]-'0'<<'-'<<m[1]-'0'<<m[2]-'0'<<m[3]-'0'<<'-'<<m[4]-'0'<<m[5]-'0'<<m[6]-'0'<<m[7]-'0'<<m[8]-'0'<<'-'<<sum;
    }
}