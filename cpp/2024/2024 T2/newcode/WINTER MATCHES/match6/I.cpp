#include <bits/stdc++.h>
using namespace std;



int main (){
    int times;
    cin>>times;
    while(times--){
        
        int length,k;
        scanf("%d", &length);
        scanf("%d", &k);
        
        int arr0[length];

        for(int i=0;i<length;i++){
            scanf("%d", &arr0[i]);
        }

        while(k--){                                                                     
            int arr[length];

            memcpy(arr, arr0, sizeof(arr));
            
            int l,r,c;
            scanf("%d", &l);
            scanf("%d", &r);
            scanf("%d", &c);

            int original = arr[c - 1];
            l-=1;
            int count = l;
            for (int i = l; i < r; ++i) {
                if (arr[i] < original) {
                    count++;
                }
            }
            count += 1  ;



            printf("%d\n", count);
        }
    }
}