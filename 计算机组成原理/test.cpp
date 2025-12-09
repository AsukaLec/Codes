#include <iostream>
using namespace std;

int main () {
    short si = -32768;
    cout  << si << endl;
    unsigned short usi  = si;
    cout << usi << endl;
    int i = si;
    cout << i << endl;
    unsigned ui = si;
    cout << ui << endl;
    return 0; 
}