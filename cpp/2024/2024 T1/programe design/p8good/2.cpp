#include <iostream> 
using namespace std;
#include<cstring>
class CStaff 
{  protected:
    int number;
    char name[10];
    int age;
   public:
    CStaff(int num, const char *na, int a) 
    {    number = num;
        age = a;
        strcpy(name, na);
    }
    void Display()
    {    cout << name << " is a Staff " << age << " yeas old"  << endl;  }
}; 

class CTeacher:public CStaff 

{
protected:
    char zch[20];     //职称
public:
    CTeacher(int num, const char *na, int a,const char *zc);
    void Display()
    {
        cout << name << " is a Teacher " << age << " yeas old, " << zch << endl;
    }
};
CTeacher::CTeacher(int num, const char *na, int a,const char *zc):CStaff( num, na, a)
{       number = num;
        age = a;
        strcpy(name, na);
        strcpy(zch, zc);
}
 

class CManagement:public CTeacher

{
protected:
    char zw[50];             //职务
public:
    CManagement(int num,const  char *na, int a,const char *z);
    void Display()
    {
        cout << name << " is a management " << age << " yeas old, " << zw << endl;
    }
};
CManagement::CManagement(int num,const  char *na, int a,const char *z):CTeacher(num, na, a,zw)
{       number = num;
        age = a;
        strcpy(name, na);
        strcpy(zw, z);
}

 
class CTeacherManagement:public CManagement

{
public:
    CTeacherManagement(int num,const char *na, int a, const char *zc,const char *z);
    void Display()
    {
        cout << name << " is a Teacher management " << age << " yeas old, " 
                       << zch << ", " << zw << endl;
    }
}; 

CTeacherManagement::CTeacherManagement(int num,const char *na, int a, const char *zc,const char *z):CManagement(num,na, a,z)
{       number = num;
        age = a;
        strcpy(name, na);
        strcpy(zw, z);
strcpy(zch, zc);
}    

int main()
{
    CStaff   s1(101,"Zhao",20);
    CTeacher t1(102,"Zhang",30,"Lecture");
    CManagement m1(103,"Wang", 50,"dean");
    CTeacherManagement tm1(104,"Li",40, "Peofessor", "department head");
    s1.Display();
    t1.Display();
    m1.Display();
    tm1.Display();
        return 0;
} 
