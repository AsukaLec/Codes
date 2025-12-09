#include<iostream>
using namespace std;

const float PI = 3.14; 
class Circle{
    public:
   
   Circle():r1(0){}
   Circle(int r):r1(r){}
   float getArea(){
    return PI*r1*r1;
   }
   float getGirth(){
    return 2*PI*r1;
   }
    private:
       int r1;      
        
};


int main()
{
    float r;
    cout << "请输入圆的半径：";
    cin >> r;                                     //浠庨敭鐩樻帴鍙楀崐寰勭殑鍊?
    Circle c1(r);                            //灏嗗�艰祴鍊肩粰鍗婂緞骞惰皟鐢ㄥ畾涔夊ソ鐨勫嚱鏁?
    cout<<"圆的面积为："<<c1.getArea()<<endl;
    Circle c2(r);
    cout<<"圆的周长为："<<c2.getGirth()<<endl;
}


