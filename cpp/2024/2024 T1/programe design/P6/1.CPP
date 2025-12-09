#include <iostream>
using namespace std;

void move(char src, char dest){
    cout<<src<<"-->"<<dest<<endl;
}//输出每一步移动的结果

void hanio(int n,char src, char medium, char dest){//当前要解决的汉诺塔问题的盘子总数以及起始针，中间针及目标针
    if(n==1)
       move(src,dest);//如果最后只有一个盘子，可以直接移动到目标针的顶部
    else{
        hanio(n-1,src,dest,medium);//将n-1个盘子看为一个整体，并将其转换为2个盘子的问题                                                           
        move(src,dest);
        hanio(n-1,medium,src,dest);
    }
}

int main(){
    int m;
    cout<<"Enter the number of disks:";
    cin>>m;
    cout<<"the step to move "<<m<<"disks:"<<endl;
    hanio(m,'A','B','C');
    return 0;
}