//根据点的定义，写出线段和三角形的定义，并通过主程序进行验证
//mypoint.h
class MyPoint
{
public:
    MyPoint();
    MyPoint(double x, double y);
    double getX();
    double getY();
private:
    double mX,mY;
};
//
#include<iostream>
#include<cmath>
using namespace std;

MyPoint::MyPoint(){}
MyPoint::MyPoint(double x,double y):mX(x),mY(y){}
double MyPoint::getX(){return mX;}
double MyPoint::getY(){return mY;}

class Line:public MyPoint
{
public:
    Line(){}
    Line(MyPoint &p1,MyPoint &p2):mp1(p1),mp2(p2){}   //最好是 const Mypoint &p1 
    double GetDistance(){
        double a=mp1.getX()-mp2.getX();
        a*=a;
        double b=mp1.getY()-mp2.getY();
        b*=b;
        double n= sqrt(a+b);
        return n;
    }
private:
    MyPoint mp1,mp2;
};

class Triangle:public Line
{
public:
    Triangle(){}
    Triangle(MyPoint &p1,MyPoint &p2,MyPoint &p3):l1(p1,p2),l2(p1,p3),l3(p2,p3){}
    double  getGirth(){
        return l1.GetDistance()+l2.GetDistance()+l3.GetDistance();
    }
private:
    Line l1,l2,l3;
};



//


int main()
{
    double x1, x2, x3, y1, y2, y3;
    cout << "请输入点1的x的值：";
    cin >> x1;
    cout << "请输入点1的y的值：";
    cin >> y1;
    cout << "请输入点2的x的值：";
    cin >> x2;
    cout << "请输入点2的y的值：";
    cin >> y2;
    cout << "请输入点3的x的值：";
    cin >> x3;
    cout << "请输入点3的y的值：";
    cin >> y3;
    cout << "点1的坐标为：(" << x1 << "," << y1 << ")" << endl;
    cout << "点2的坐标为：(" << x2 << "," << y2 << ")" << endl;
    cout << "点3的坐标为：(" << x3 << "," << y3 << ")" << endl;
    MyPoint p1(x1, y1), p2(x2, y2), p3(x3, y3);
    Line  line1(p1,p2);
    cout<<"线长度:"<<line1.GetDistance()<<endl;
    Triangle t(p1, p2, p3);
    cout << "该三角形的周长为：" << t.getGirth() << endl;
    return 0;
}