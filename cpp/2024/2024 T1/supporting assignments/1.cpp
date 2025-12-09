#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

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


int daxiaoyue(int n){
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
           return 3;
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

int main(){
    string t;
    int n;
    cin>>t>>n;
    int k = stoi(t);
    int year=k/10000;
    int month =(k-year*10000)/100;
    int day= (k-year*10000-month*100);

    
    while(n>0){
        day=day+1;
        
        n=n-1;
        
        if(month==2){
            if(runnian(year)==1){
                if(day==30){
                    day=day-29;
                    month=month+1;
                }
            }
        }//闰年2月底

        if(month==2){
            if(runnian(year)==0){
                if(day==29){
                    day=day-28;
                    month=month+1;
                }
            }
        }//平年2月底

        if(month==12&&day==32){
            year=year+1;
            month=month-11;
            day=day-31;
        }//每年最后一天
          
        if(daxiaoyue(month)==1&&day==32){
            month=month+1;
            day=day-31;
        }//大月最后一天
  
         if(daxiaoyue(month)==0&&day==31){
            month=month+1;
            day=day-30;
        }//小月最后一天

    }
    if(year<10000){
        cout<< setfill('0') << setw(4) << year <<setfill('0')<<setw(2)<<month<<setfill('0')<<setw(2)<<day;
    }
    if(year>=10000){
        cout<<"out of limitation!";
    }
}

