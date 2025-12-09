
#include <iostream>
using namespace std;
int main()
{
    int a=-1,b=4,k;
    k=(++a<0)&&!(b--<0);
    cout<<k<<a<<b;
}