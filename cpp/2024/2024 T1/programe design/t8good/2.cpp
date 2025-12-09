// #include <iostream>
// #include <iomanip>
// using namespace std;

// // void swap0(int a,int b){
    
// // }//swap




// int main(){
//     int n;
//     cin>>n;
//     if(n<1||n>9){
//         cout<<"Please input 1-9.";
//     }

//     int arr1[n][5];
//     char arr2[n+1][10];
//     for(int i=0;i<n;i++){
//         cin>>arr1[i][0];
//         cin>>arr2[i];
//         cin>>arr1[i][1];
//         cin>>arr1[i][2];
//         cin>>arr1[i][3];
//         arr1[i][4]=arr1[i][1]+arr1[i][2]+arr1[i][3];
//     }//input
    
//     int arr3[n];
//     for(int i=0;i<n;i++){
//         arr3[i]=arr1[i][4];
//     }

//     for (int i = 0; i < n-1; i++) {
// 		int min = i;
// 		for (int j = i; j < n; j++) {
// 			if (arr3[min] > arr3[j]) {
// 				min = j;
// 			}
// 		}
// 		if (min != i) {
// 			for(int k=0;k<5;k++){
//                 int t=arr1[min][k];
//                 arr1[min][k]=arr1[i][k];
//                 arr1[i][k]=t;
//                 }
            
            
//             for (int j = 0; j < 10; ++j) {
//                 int temp[10]; // 假设每行的最大元素数为100
//                 temp[j] = arr1[min][j];
//                 arr1[min][j] = arr2[i][j];
//                 arr2[i][j] = temp[j];
//                 }
//             // arr2[n]=arr2[min];
//             // arr2[min]=arr2[i];
//             // arr2[i]=arr2[n];
		
//         }
//     }
    
    
//     int w=1;
//     int arr4[n];
//     for(int i=n-1;i>=0;i--){
//         if(i==n-1){
//             arr4[i]=w;
//             w+=1;
//         }
//         else{
//             if(arr3[i]==arr3[i+1]){
//                 arr4[i]=arr4[i+1];
//                 w+=1;
//             }
//             else{
//                 arr4[i]=w;
//             }
//         }
//     }    
    
//     for(int i=0;i<n;i++){
//         cout<<setw(4)<<arr4[i]<<setw(10)<<arr1[i][0]<<setw(10)<<arr2[i]<<setw(5)<<arr1[i][1]<<setw(5)<<arr1[i][2]<<setw(5)<<arr1[i][3];
//         cout<<endl;


//     }
// }



#include <iostream>
#include <iomanip> 
#include <string>  
using namespace std;

struct Student {
    int rank;
    int  id;         
    std::string name;    
    int math;            
    int english;         
    int chinese;         
    int totalScore;      
};

int main() {
    int n;
    std::cin >> n; 

    if (n < 1 || n >= 10) {
        std::cout << "Please input 1-9." << std::endl;
        return 0;
    }

    Student students[n]; 
    
    for (int i = 0; i < n; ++i) {
        students[i].rank=0;
        cin >> students[i].id >> students[i].name >> students[i].math >> students[i].english >> students[i].chinese;
        
        students[i].totalScore = students[i].math + students[i].english + students[i].chinese;
    }
    
    for(int i=0; i<n;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(students[min].totalScore>students[j].totalScore){
                min=j;
            }
        }
        if(min!=i){
            int t1=students[min].chinese;
            int t2=students[min].english;
            int t3=students[min].math;
            int t4=students[min].id;
            int t5=students[min].totalScore;
            string t=students[min].name;

            students[min].chinese=students[i].chinese;
            students[min].english=students[i].english;
            students[min].math=students[i].math;
            students[min].id=students[i].id;
            students[min].name=students[i].name;
            students[min].totalScore=students[i].totalScore;

            students[i].chinese=t1;
            students[i].english=t2;
            students[i].math=t3;
            students[i].id=t4;
            students[i].totalScore=t5;
            students[i].name=t;
            }
        
    }

    int w=1;
    for(int i = n-1; i >=0; i--){
        if(i==n-1){
            students[i].rank=w;
            w+=1;
        }
        else{
            if(students[i].totalScore==students[i+1].totalScore){
                students[i].rank=students[i+1].rank;
                w+=1;               
            }
            else{
                students[i].rank=w;
                w+=1;
            }
        }
    }
    

     for(int i=0; i<n;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if((students[min].id>students[j].id)&&(students[min].rank==students[j].rank)){
                min=j;
            }
        }
        if(min!=i){
            int t1=students[min].chinese;
            int t2=students[min].english;
            int t3=students[min].math;
            int t4=students[min].id;
            int t5=students[min].totalScore;
            string t=students[min].name;

            students[min].chinese=students[i].chinese;
            students[min].english=students[i].english;
            students[min].math=students[i].math;
            students[min].id=students[i].id;
            students[min].name=students[i].name;
            students[min].totalScore=students[i].totalScore;

            students[i].chinese=t1;
            students[i].english=t2;
            students[i].math=t3;
            students[i].id=t4;
            students[i].totalScore=t5;
            students[i].name=t;
            }
        
    }
    
    for (int i=0;i<n;i++) {
        
             cout << std::setw(4) << students[i].rank ;
             cout<< std::setw(10) << students[i].id ;
             cout<< std::setw(10) << students[i].name ;
             cout<< std::setw(5) << students[i].math ;
             cout<< std::setw(5) << students[i].english ;
             cout<< std::setw(5) << students[i].chinese << std::endl;
    }

    return 0;
}


// #include<iostream>
// #include<string>
// #include<iomanip>
// #include<algorithm>
// using namespace std;
// struct students{
// 	int No;string number;string name;int Chinese;int Maths;int English;int total;
// };
// bool compared(const students&a,const students&b){
// 	if(a.total!=b.total){
// 		return a.total<b.total;
// 	}
// 	else{
// 		return a.number<b.number;
// 	}
// }
// int main(){
// 	int n,m=1;
// 	cin>>n;
// 	if(n>=10||n<1){
// 		cout<<"Please input 1-9."<<endl;
// 		return 0;
// 	}
// 	students stu[n];
// 	for(int i=0;i<n;i++){
// 		cin>>stu[i].number>>stu[i].name>>stu[i].Chinese>>stu[i].Maths>>stu[i].English;
// 		stu[i].total=stu[i].Chinese+stu[i].Maths+stu[i].English;
// 	}
// 	sort(stu,stu+n,compared);
// 	stu[n-1].No=1;
// 	for(int j=n-2;j>=0;j--){
// 		m++;
// 		if(stu[j].total!=stu[j+1].total){
// 			stu[j].No=m;
// 		}
// 		else{
// 			stu[j].No=stu[j+1].No;
// 		}
// 	}
// 	for(int i=0;i<n;i++){
// 		cout<<setw(4)<<setfill(' ')<<stu[i].No;
// 		cout<<setw(10)<<setfill(' ')<<stu[i].number;
// 		cout<<setw(10)<<setfill(' ')<<stu[i].name;
// 		cout<<setw(5)<<setfill(' ')<<stu[i].Chinese;
// 		cout<<setw(5)<<setfill(' ')<<stu[i].Maths;
// 		cout<<setw(5)<<setfill(' ')<<stu[i].English<<endl;
// 	}
// 	return 0;
// }


// #include <iostream>
// #include <iomanip> // 用于格式化输出
// #include <string>  // 用于处理字符串

// const int MAX_STUDENTS = 9; // 最大学生数

// // 定义学生结构体
// struct Student {
//     long long id;         // 学号
//     std::string name;    // 姓名
//     int math;            // 数学成绩
//     int english;         // 英语成绩
//     int chinese;         // 语文成绩
//     int totalScore;      // 总成绩
// };

// // 比较函数，用于排序
// bool compare(const Student &a, const Student &b) {
//     if (a.totalScore != b.totalScore) {
//         return a.totalScore < b.totalScore;
//     } else {
//         return a.id < b.id;
//     }
// }

// int main() {
//     int n;
//     std::cin >> n; // 读取学生人数

//     // 检查学生人数是否符合要求
//     if (n < 1 || n >= 10) {
//         std::cout << "Please input 1-9." << std::endl;
//         return 0;
//     }

//     Student students[MAX_STUDENTS]; // 学生数组

//     // 读取学生信息
//     for (int i = 0; i < n; ++i) {
//         std::cin >> students[i].id >> students[i].name >> students[i].math >> students[i].english >> students[i].chinese;
//         students[i].totalScore = students[i].math + students[i].english + students[i].chinese;
//     }

//     // 对学生信息进行排序
//     for (int i = 0; i < n - 1; ++i) {
//         for (int j = 0; j < n - i - 1; ++j) {
//             if (compare(students[j], students[j + 1])) {
//                 std::swap(students[j], students[j + 1]);
//             }
//         }
//     }

//     // 输出排序后的学生信息
//     int rank = 1;
//     int lastScore = -1;
//     for (int i = 0; i < n; ++i) {
//         if (lastScore != students[i].totalScore) {
//             lastScore = students[i].totalScore;
//             rank = i + 1;
//         }
//         std::cout << std::setw(4) << rank << " "
//                   << std::setw(10) << students[i].id << " "
//                   << std::setw(10) << students[i].name << " "
//                   << std::setw(5) << students[i].math << " "
//                   << std::setw(5) << students[i].english << " "
//                   << std::setw(5) << students[i].chinese << std::endl;
//     }

//     return 0;
// }