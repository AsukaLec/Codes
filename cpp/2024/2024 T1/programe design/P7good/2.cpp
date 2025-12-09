#include <iostream>
using namespace std;
class Shape
{
public:
    virtual double area() = 0;
};

/*在这里写代码，包括Circle、Rectangle和Triangle类继承Shape*/
class Circle :public Shape
{   public:
        Circle(double k){r=k;}
            double area() override {
                return 3.14159 * r * r; 
            }

    private:
        double r;
};

class Rectangle :public Shape
{   public:
        Rectangle(double k,double t){m=k;n=t;}
            double area() override {
                return m*n; 
            }

    private:
        double m,n;
};

class Triangle :public Shape
{   public:
        Triangle(double k,double t){m=k;n=t;}
            double area() override {
                return m*n/2; 
            }

    private:
        double m,n;
};

void printArea(Shape& s)
{
    cout << s.area() << endl;
}

int main() {
    Circle circle(12.6); 
    cout << "area of circle =";
    printArea(circle);
    
    Rectangle rectangle(4.5, 8.4); 
    cout << "area of rectangle ="; 
    printArea(rectangle); 
    
    Triangle triangle(4.5, 8.4);
    cout << "area of triangle ="; 
    printArea(triangle);
    
    return  0;
}