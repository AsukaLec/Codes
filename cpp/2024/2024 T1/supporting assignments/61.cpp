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
    int year,month0,day0;
    cin>>year>>month0>>day0;

    int day=1,month=1;
    int t=1;
    
    while(month!=month0){
        t+=1;
        day+=1;
    
    if(runnian(year)==1){
        if(month==2){
            if(day==30){
                day=day-29;
                month=month+1;
            }
        }//闰年2月底
        
        if(daxiaoyue(month)==1&&day==32){
            month=month+1;
            day=day-31;
        }//大月最后一天
  
         if(daxiaoyue(month)==0&&day==31){
            month=month+1;
            day=day-30;
        }//小月最后一天
        

    }

    if(runnian(year)==0){
        

        if(month==2){
            
            if(day==29){
                day=day-28;
                month=month+1;
            }
            
        }//平年2月底
        if(daxiaoyue(month)==1&&day==32){
            month=month+1;
            day=day-31;
        }//大月最后一天
  
         if(daxiaoyue(month)==0&&day==31){
            month=month+1;
            day=day-30;
        }//小月最后一天
        
    }
        

    }

    while(month0==month){
        if(day0!=day){
            t+=1;
            day+=1;
            
            if(runnian(year)==1){
        if(month==2){
            if(day==30){
                day=day-29;
                month=month+1;
            }
        }//闰年2月底
        
        if(daxiaoyue(month)==1&&day==32){
            month=month+1;
            day=day-31;
        }//大月最后一天
  
         if(daxiaoyue(month)==0&&day==31){
            month=month+1;
            day=day-30;
        }//小月最后一天
        

    }

    if(runnian(year)==0){
        

        if(month==2){
            
            if(day==29){
                day=day-28;
                month=month+1;
            }
            
        }//平年2月底
        if(daxiaoyue(month)==1&&day==32){
            month=month+1;
            day=day-31;
        }//大月最后一天
  
         if(daxiaoyue(month)==0&&day==31){
            month=month+1;
            day=day-30;
        }//小月最后一天
        
    }
    
    
        }

        if(day==day0){
            goto flag;
        }
    }
    
    flag:cout<<t;



}


        
        