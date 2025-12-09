#include <iostream>
using namespace std;
int main(){
    int i;//i for the number of the students
    cin>>i;

    int score[i+1][3];
    char name[i+1][10];//place for storage

    for(int n=0;n<i;n++){
    cin>>name[n]>>score[n][0]>>score[n][1]>>score[n][2];
    }
    
    int total[i];
    for(int n=0;n<i;n++){
    total[n]=score[n][0]+score[n][1]+score[n][2];
    }// the sum

    
    

        
    
}