#include <iostream>
#include <fstream>
using namespace std;
int main(){
    ifstream inputFile("poly.in");
    ofstream outputFile("poly.out");
    int a[100];
    int b[100];
    char d;
    int t = 0;
    int g=0;
    for (int i = 0; i < 100; i++) {

        inputFile >> a[i];
        d = inputFile.get();
        if (d == 10) {
             t = i + 1; break;
        }
    }
    int arr1[t];
    for(int i=0;i<t;i++){
        arr1[i]=a[i];
    }

    for (int i = 0; i < 100; i++) {

        inputFile >> b[i];
        d = inputFile.get();
        if (d == 10) {
             g = i + 1; break;
        }
    }
    int arr2[g];
    for(int i=0;i<g;i++){
        arr2[i]=b[i];
    }
    

    // int t=10;
    // int g=6;
    // int arr1[t]={54,8,2,6,7,3,25,1,78,0};
    // int arr2[g]={43,7,4,2,8,1};

    int q=arr1[1];
    int p=arr2[1];
    int w;
    w=(q>p)?2*q:2*p;

    int arr3[w+2];
    for(int i=1;i<w+2;i+=2){
        arr3[i]=(w+1-i)/2;
        arr3[i-1]=0;
    }
    
    
        for(int k=1;k<w+2;k+=2){
            for(int i=1;i<t;i+=2){
                if(arr1[i]==arr3[k]){
                    arr3[k-1]+=arr1[i-1];
                }
            }
        
        }

    

    for(int k=1;k<w+2;k+=2){
        for(int i=1;i<g;i+=2){
            if(arr2[i]==arr3[k]){
                arr3[k-1]+=arr2[i-1];
            }
        }
        
    }
    
    for(int i=0;i<w+2;i+=2){
        if(arr3[i]!=0){
            
            outputFile<<arr3[i]<<" "<<arr3[i+1]<<" ";
        }
        
    }
    

    inputFile.close();
    outputFile.close();
}