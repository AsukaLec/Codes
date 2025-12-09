#include <iostream>
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
    int y1,y2,m1,m2,d1,d2;
    cin>>y1>>m1>>d1>>y2>>m2>>d2;
    int t=0;
    while(!((y1==y2)&&(m1==m2)&&(d1==d2))){
        t+=1;
        d1+=1;
        if(m1==2){
            if(runnian(y1)==1){
                if(d1==30){
                    d1=d1-29;
                    m1=m1+1;
                }
            }
        }//闰年2月底

        if(m1==2){
            if(runnian(y1)==0){
                if(d1==29){
                    d1=d1-28;
                    m1=m1+1;
                }
            }
        }//平年2月底

        if(m1==12&&d1==32){
            y1=y1+1;
            m1=m1-11;
            d1=d1-31;
        }//每年最后一天
          
        if(daxiaoyue(m1)==1&&d1==32){
            m1=m1+1;
            d1=d1-31;
        }//大月最后一天
  
         if(daxiaoyue(m1)==0&&d1==31){
            m1=m1+1;
            d1=d1-30;
        }//小月最后一天
    }
    cout<<t;
}