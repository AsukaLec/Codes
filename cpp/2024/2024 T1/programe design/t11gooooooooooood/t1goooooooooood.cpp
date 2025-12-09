# include <iostream>
using namespace std;

class vehicle
{
       int wheels;
       float weight;
public:
       virtual void message()//virtual or not !!!
       {cout<<"vehicle message\n";}
};


class car:public vehicle
{
       int passengers;
public:
       void message(){
       cout<<"car message\n";}
};

class truck:public vehicle
{
       int goods;
public:
        void message(){
       cout<<"truck message\n";}
};

class god:public truck
{
       int man;
public:
        void message(){
       cout<<"god message\n";}
};


int main()
{
       vehicle obj,*ptr;
       car obj1;
       truck obj2;
       god obj3;
       ptr=&obj;
       ptr->message();
       ptr=&obj1;
       ptr->message();
       ptr=&obj2;
       ptr->message();
       ptr=&obj3;
       ptr->message();
}