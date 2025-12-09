#include <iostream>
#include <cstring>
using namespace std;
class COM{
    char *pname;
    char *punit;
    char *pnum;
    char box[6];
public:
    COM();
    COM(char *name,char *unit,char *num,char *b);
    COM(const COM &p);
   //     
COM& operator=(const COM &p);
//
   //重载赋值运算符函数
    ~COM();
    void print();
    void setname(char *name);
    void setuint(char *unit);
    void setnum(char *num);
    void setbox(char *b);
    char *getname();
    char *getuint();
    char *getnum();
    char *getbox();
};
//
COM::COM() 
{
    pname = new char[1];
    punit = new char[1];
    pnum = new char[1];   
    memset(box, 0, sizeof(box));
}
 

COM::COM(char *name, char *unit, char *num, char *b) 
{
    pname = new char[strlen(name) + 1];
    strcpy(pname, name);
    punit = new char[strlen(unit) + 1];
    strcpy(punit, unit);
    pnum = new char[strlen(num) + 1];
    strcpy(pnum, num);
    strncpy(box, b, sizeof(box) + 1);
    box[sizeof(box) + 1] = '\0'; 
}
 

COM::COM(const COM &p)
 {
    pname = new char[strlen(p.pname) + 1];
    strcpy(pname, p.pname);
    punit = new char[strlen(p.punit) + 1];
    strcpy(punit, p.punit);
    pnum = new char[strlen(p.pnum) + 1];
    strcpy(pnum, p.pnum);
    strncpy(box, p.box, sizeof(box) + 1);
    box[sizeof(box) + 1] = '\0';  
}
 

COM& COM::operator=(const COM &p) 
{
    if (this == &p) return *this;  
    delete[] pname;
    delete[] punit;
    delete[] pnum;
 
    pname = new char[strlen(p.pname) + 1];
    strcpy(pname, p.pname);
    punit = new char[strlen(p.punit) + 1];
    strcpy(punit, p.punit);
    pnum = new char[strlen(p.pnum) + 1];
    strcpy(pnum, p.pnum);
    strncpy(box, p.box, sizeof(box) + 1);
    box[sizeof(box) + 1] = '\0';  
 
    return *this;
}
 

COM::~COM()
 {
    delete[] pname;
    delete[] punit;
    delete[] pnum;
}
 

void COM::print() 
{
    cout << pname << endl;
    cout << punit << endl;
    cout << pnum << endl;
    cout << box << endl;
}
 

void COM::setname(char *name) 
{
    delete[] pname;
    pname = new char[strlen(name) + 1];
    strcpy(pname, name);
}
 
void COM::setuint(char *unit) 
{
    delete[] punit;
    punit = new char[strlen(unit) + 1];
    strcpy(punit, unit);
}
 
void COM::setnum(char *num) 
{
    delete[] pnum;
    pnum = new char[strlen(num) + 1];
    strcpy(pnum, num);
}
 
void COM::setbox(char *b) 
{
    strncpy(box, b, sizeof(box) + 1);
    box[sizeof(box) + 1] = '\0';  
}
 

char *COM::getname() 
{
    return pname;
}
 
char *COM::getuint() 
{
    return punit;
}
 
char *COM::getnum() 
{
    return pnum;
}
 
char *COM::getbox() 
{
    return box;
}
 

//
int main()
{
    
    COM c1("wangdahai","江大","88664455","212013"),
        c2("张三","江科技大","88771111","212034"),c3(c1),c4;
    c3.setname("李四");
    c4.setname("王五");
    c4.setuint("科大");
    c4.setnum("22334455");
    c4.setbox("212067");
    c1.print();
    c2.print();
    c3.print();
    c4.print();
        c4=c1;
    c4.print();
}