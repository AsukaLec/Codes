#include <bits/stdc++.h>
using namespace std;
int a[5005] = {0};

int main(){
    int limit;
    int total;
    cin>> limit >> total;
    for (int i = 0; i < total; i++){
        int target;
        cin>> target;
        a[target] = 1;
    }
    if (total == 0) cout<< 0 << " " << 0;
    else{
        if (limit % 2 == 1){
            int middle , far;
            int mid = limit / 2 + 1;
            int index1 = mid, index2 = mid;
            while(a[index1] == 0 && a[index2] == 0){
                index1 -= 1;
                index2 += 1;
            } 
            if(index1 != 0) middle = index1;
            else middle = limit + 1 - index2;
            //
            index1 = 1, index2 = limit;
            while(a[index1] == 0 && a[index2] == 0){
                index1 += 1;
                index2 -= 1;
            }
            if(index1 != 0) far = limit + 1 - index1;
            else far = index2;
            //
            cout<< middle << " " << far;
        }
        else{
            int middle , far;
            int mid = limit / 2 ;
            int index1 = mid, index2 = mid + 1;
            while(a[index1] == 0 && a[index2] == 0){
                index1 -= 1;
                index2 += 1;
            } 
            if(index1 != 0) middle = index1;
            else middle = limit + 1 - index2;
            //
            index1 = 1, index2 = limit;
            while(a[index1] == 0 && a[index2] == 0){
                index1 += 1;
                index2 -= 1;
            }
            if(index1 != 0) far = limit + 1 - index1;
            else far = index2;
            //
            cout<< middle << " " << far;
        }
    }
    

}