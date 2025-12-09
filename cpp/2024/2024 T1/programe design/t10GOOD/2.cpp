#include <iostream>
using namespace std;
int main(){
    int arr[19][19];
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            cin>>arr[m][n];
        }
    }//初始化棋盘
    
    int t=0;
    int g=0;
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==1){
                if((arr[m][n+1]==1)&&(arr[m][n+2]==1)&&(arr[m][n+3]==1)&&((arr[m][n-1]==0)||(arr[m][n+4]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
        }
    }//白子行判断
    
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==1){
                if((arr[m+1][n]==1)&&(arr[m+2][n]==1)&&(arr[m+3][n]==1)&&((arr[m-1][n]==0)||(arr[m+4][n]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
        }
    }//白子列判断
    
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==1){
                if((arr[m+1][n+1]==1)&&(arr[m+2][n+2]==1)&&(arr[m+3][n+3]==1)&&((arr[m-1][n-1]==0)||(arr[m+4][n+4]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==1){
                if((arr[m+1][n-1]==1)&&(arr[m+2][n-2]==1)&&(arr[m+3][n-3]==1)&&((arr[m-1][n+1]==0)||(arr[m+4][n-4]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==1){
                if((arr[m-1][n+1]==1)&&(arr[m-2][n+2]==1)&&(arr[m-3][n+3]==1)&&((arr[m+1][n-1]==0)||(arr[m-4][n+4]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==1){
                if((arr[m-1][n-1]==1)&&(arr[m-2][n-2]==1)&&(arr[m-3][n-3]==1)&&((arr[m+1][n+1]==0)||(arr[m-4][n-4]==0))){
                    cout<<1<<":"<<m+1<<","<<n+1<<endl;
                    t+=1;
                    goto flag;
                }
            }
        }
    }//白子斜判断

//白子貌似是先手，故先判断白子，而后黑子

    
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==2){
                if((arr[m][n+1]==2)&&(arr[m][n+2]==2)&&(arr[m][n+3]==2)&&((arr[m][n-1]==0)||(arr[m][n+4]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
        }
    }//行判断
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==2){
                if((arr[m+1][n]==2)&&(arr[m+2][n]==2)&&(arr[m+3][n]==2)&&((arr[m-1][n]==0)||(arr[m+4][n]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
        }
    }//列判断
    for(int m=0;m<19;m++){
        for(int n=0;n<19;n++){
            if(arr[m][n]==2){
                if((arr[m+1][n+1]==2)&&(arr[m+2][n+2]==2)&&(arr[m+3][n+3]==2)&&((arr[m-1][n-1]==0)||(arr[m+4][n+4]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==2){
                if((arr[m+1][n-1]==2)&&(arr[m+2][n-2]==2)&&(arr[m+3][n-3]==2)&&((arr[m-1][n+1]==0)||(arr[m+4][n-4]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==2){
                if((arr[m-1][n+1]==2)&&(arr[m-2][n+2]==2)&&(arr[m-3][n+3]==2)&&((arr[m+1][n-1]==0)||(arr[m-4][n+4]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
            if(arr[m][n]==2){
                if((arr[m-1][n-1]==2)&&(arr[m-2][n-2]==2)&&(arr[m-3][n-3]==2)&&((arr[m+1][n+1]==0)||(arr[m-4][n-4]==0))){
                    cout<<2<<":"<<m+1<<","<<n+1<<endl;
                    g+=1;
                    goto flag;
                }
            }
        }
    }//斜判断


    if((t==0)&&(g==0)){
        cout<<"No"<<endl;
    }
    flag :return 0;//没有，输出No
}