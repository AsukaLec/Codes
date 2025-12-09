#include <iostream>
using namespace std;
class Clock    //时钟类声明
{
public:    //外部接口
    Clock(int NewH=0, int NewM=0, int NewS=0);
    void ShowTime();
     Clock operator ++();        //前置单目运算符重载
 //后置单目运算符重载
     Clock operator ++(int);
   
 //+运算符重载
     Clock operator +(const Clock &c1);
         
  
private:    //私有数据成员
    int Hour, Minute, Second;
};
//
Clock::Clock(int NewH, int NewM, int NewS):Hour(NewH),Minute(NewM),Second(NewS){}

Clock Clock::operator ++(){
    Second++;
    if(Second>=60){
        Second-=60;
        Minute+=1;
        if(Minute>=60){
            Minute-=60;
            Hour=(Hour+1)%24;
        }
    }
    return *this;
}

Clock Clock::operator ++(int){
    Clock old=*this;
    ++(*this);
    return old;
}

Clock Clock:: operator +(const Clock &c1){
    Second+=c1.Second;
    Minute+=c1.Minute;
    Hour+=c1.Hour;
    if(Second>=60){
        Second-=60;
        Minute+=1;
        if(Minute>=60){
            Minute-=60;
            Hour=(Hour+1)%24;
        }
    }
    return *this;
}

//

void Clock::ShowTime()
{  
   cout<<Hour<<":"<<Minute<<":"<<Second<<endl;
}

int main()
{
    Clock c1(23,59,59),c2(5,12,10),c3;
    c1.ShowTime();
    c1++;
    c1.ShowTime();
    c3=++c2;
    c3.ShowTime();
    c3=c2+c1;
    c3.ShowTime();
    return 0;
}


#include <iostream>
using namespace std;

class Clock { // 时钟类声明
public: // 外部接口
    Clock(int NewH = 0, int NewM = 0, int NewS = 0);
    void ShowTime();
    Clock operator ++(); // 前置单目运算符重载
    Clock operator ++(int); // 后置单目运算符重载
    Clock operator +(const Clock& c1); // +运算符重载

private: // 私有数据成员
    int Hour, Minute, Second;
};

// 构造函数
Clock::Clock(int NewH, int NewM, int NewS) : Hour(NewH), Minute(NewM), Second(NewS) {}

// 前置单目运算符重载
Clock Clock::operator ++() {
    Second++;
    if (Second >= 60) {
        Second = 0;
        Minute++;
        if (Minute >= 60) {
            Minute = 0;
            Hour = (Hour + 1) % 24;
        }
    }
    return *this;
}

// 后置单目运算符重载
Clock Clock::operator ++(int) {
    Clock old = *this;
    ++(*this);
    return old;
}

// +运算符重载
Clock Clock::operator +(const Clock& c1) {
    Clock temp = *this;
    temp.Second += c1.Second;
    temp.Increment();
    temp.Minute += c1.Minute;
    temp.Increment();
    temp.Hour += c1.Hour;
    temp.Increment();
    return temp;
}

// 辅助函数，用于处理秒和分钟的进位
void Clock::Increment() {
    if (Second >= 60) {
        Second -= 60;
        Minute++;
        if (Minute >= 60) {
            Minute = 0;
            Hour = (Hour + 1) % 24;
        }
    }
}

// 显示时间
void Clock::ShowTime() {
    cout << Hour << ":" << Minute << ":" << Second << endl;
}

int main() {
    Clock c1(23, 59, 59), c2(5, 12, 10), c3;
    c1.ShowTime();
    c1++;
    c1.ShowTime();
    c3 = ++c2;
    c3.ShowTime();
    c3 = c2 + c1;
    c3.ShowTime();
    return 0;
}