#include <iostream>
using namespace std;
int main(){
    int a,b,c;
    cin>>a>>b>>c;

    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }

    if(b < c){
        int temp = b;
        b = c;
        c = temp;
    }

    if(a < b){
        int temp = a;
        a = b;
        b = temp;
    }
    
    if((b+c>a)&&(a-b<c)){
        if(a*a==b*b+c*c) cout<<"Right triangle"<<endl;
        
        if(b*b+c*c-a*a>0) cout<<"Acute triangle"<<endl;
        if(b*b+c*c-a*a<0) cout<<"Obtuse triangle"<<endl;
        
        if(b==c||a==b) cout<<"Isosceles triangle"<<endl;
        
        if((a==b)&&(b==c)) cout<<"Equilateral triangle"<<endl;
    }
    else cout<<"Not triangle";
}

// 如果是直角三角形，输出Right triangle；
// 如果是锐角三角形，输出Acute triangle；
// 如果是钝角三角形，输出Obtuse triangle；
// 如果是等腰三角形，输出Isosceles triangle；
// 如果是等边三角形，输出Equilateral triangle。