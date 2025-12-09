#include <iostream>
using namespace std;

class base{
public:
       base(){cout<<"base!"<<endl;}
       ~base(){ cout<<"~base!"<<endl;}
};
class derived: public base{
public:
       derived(){cout<<"derived!"<<endl;}
       ~derived(){ cout<<"~derived!"<<endl;}
};
int main()
{
       derived x;
       return 1;
}