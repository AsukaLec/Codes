#include <iostream>
using namespace std;

int  daxiaoyue(int n){
    switch(n){
        case 1:
           return 1;
           break;
        case 3:
           return 1;
           break;
        case 5:
           return 1;
           break;
        case 7:
           return 1;
           break;
        case 8:
           return 1;
           break;
        case 10:
           return 1;
           break;
        case 12:
           return 1;
           break;
        case 4:
           return 0;
           break;
        case 6:
           return 0;
           break;
        case 9:
           return 0;
           break;
        case 11:
           return 0;
           break;
        case 2:
           return 3;
           break; 
    }
}

int runnian (int n){
     if( n%4==0&&n%100!=0){
            return 1;

        }
        if( n%100==0&&n%400==0  ){
            return 1;
        }
        else{
            return 0;
        }
}

int main(){
    int year,month;
    cin>>year>>month;
    if(year<=0||year>=10000){
        cout<<"Error!";
        goto flag;
    }
    if(month<1||month>=13){
        cout<<"Error!";
        goto flag;
    }

    if(runnian(year)==1){
        if(daxiaoyue(month)==1){
            cout<<31;
        }
        if(daxiaoyue(month)==0){
            cout<<30;
        }
        if(daxiaoyue(month)==3){
            cout<<29;
        }
    }
    if(runnian(year)==0){
        if(daxiaoyue(month)==1){
            cout<<31;
        }
        if(daxiaoyue(month)==0){
            cout<<30;
        }
        if(daxiaoyue(month)==3){
            cout<<28;
        }
    }
    flag:return 0;

}