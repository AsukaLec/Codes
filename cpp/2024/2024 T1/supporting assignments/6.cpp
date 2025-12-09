
// goto goooooooooooooooooooood!!!!!!!!!!!!!!!



#include <iostream>
using namespace std;
int main(){
    int n;
    int m=0;
    
    cin>>n;

    
    cout<<"2";
    for(int i=3;i<=n;i++){
        
        for(int b=1;b<=i;b++){
           
           if(i%b==0){
            m=m+1;
            }

            if(m>2){
                goto flag;
            }
        
        }
        

        if(m==2){
             cout<<" "<<i; 
            }
       
        flag:
        m=0;
        
        
    }
    
    
    

    
}