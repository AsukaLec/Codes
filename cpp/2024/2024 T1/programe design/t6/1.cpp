#include <iostream>
#include <iomanip>

using namespace std;

class Time {
   int hour,minute,second;


public:
   Time(int a,int b, int c):hour(a),minute(b),second(c){}
   
   int m_hour=hour;
   int m_minute=minute;
   int m_second=second;  
};

void add(int a,int b,int c,int d,int e,int f){
    int hour=0,minu=0,sec=0;
    if(c+f<60){
        sec=c+f;
    }
    else{
        minu=1;
        sec=c+f-60;
    }

    if(b+e+minu<60){
        minu=b+e+minu;
    }
    else{
        minu=b+e+minu-60;
        hour=1;
    }
    if(a+d+hour<24){
        hour=a+d+hour;
    }
    else{
        hour=a+d+hour-24;
    }

    cout<<setfill('0')<<setw(2)<<hour<<":"<<setfill('0')<<setw(2)<<minu<<":"<<setfill('0')<<setw(2)<<sec<<endl;
}


void sub(int a,int b,int c,int d,int e,int f){
    int hour=0,minu=0,sec=0;
    if(c-f>=0){
        sec=c-f;
    }
    else{
        minu=-1;
        sec=c-f+60;
    }

    if(b-e+minu>=0){
        minu=b-e+minu;
    }
    else{
        minu=b-e+minu+60;
        hour=-1;
    }
    if(a-d+hour>=0){
        hour=a-d+hour;
    }
    else{
        hour=a-d+hour+24;
    }

    cout<<setfill('0')<<setw(2)<<hour<<":"<<setfill('0')<<setw(2)<<minu<<":"<<setfill('0')<<setw(2)<<sec<<endl;
}

int main (){
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    Time A(a,b,c),B(d,e,f);
    
    add(A.m_hour,A.m_minute,A.m_second,B.m_hour,B.m_minute,B.m_second);
    sub(A.m_hour,A.m_minute,A.m_second,B.m_hour,B.m_minute,B.m_second);
}