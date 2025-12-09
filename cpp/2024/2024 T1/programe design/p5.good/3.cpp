#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    
    // int arr[n]={0,1,2,3,9,56,87,88,89,90,99,3520,3521};

    
    
    for (int i = 0; i < n-1; i++) {
		int min = i;
		for (int j = i; j < n; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		if (min != i) {
			swap(arr[i], arr[min]);
		}
    
    }
    
    int arr2[n];
    for(int i=0;i<n;i++){
       arr2[i]=0;
    }
    
    int maxi=0;
    for(int i=0;i<n-1;i++){
        int t=0;
        int k=i;
        while(arr[k]==arr[k+1]-1){
            
            k+=1;
            t+=1;
        }
        if(t>=maxi){
            maxi=t;
            
            arr2[k]=1;
        
        }

        
    }
    
    if(maxi==0){
        cout<<0;
    }
    if(maxi!=0){
        cout<<maxi+1<<endl;
       
        for(int i=0;i<n;i++){
            
            if(arr2[i]==1){
                
                for(int k=i-maxi;k<=i;k++){
                    cout<<arr[k]<<" ";
                }

                cout<<endl;
            }

        }
    }




    // for (int i = 0; i < n; i++)
	// {
	// 	cout << arr[i] << ",";
	// }
	// cout << endl;
	

}