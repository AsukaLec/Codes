#include <iostream>
using namespace std;

template<class T>
class Tadd                              
{                                     
    T x,y;                                   
public:
    Tadd(T a,T b):x(a),y(b){ }          
    int add() { return x+y;}                
};

int main(){
    Tadd<float>K('3','4');
    cout<<K.add();
}