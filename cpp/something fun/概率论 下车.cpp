#include <iostream>
#include <random>
#include <bits/stdc++.h>
using namespace std;
int choice (){
    random_device rd;
    mt19937 gen(rd());
    bernoulli_distribution dis(0.1); 
    int random_number = dis(gen);
    return random_number;
}

int main() {
    int totaltimes = 20;
    while (totaltimes --){

    
    int times = 20;
    double sum = 0.0;

    while(times--){
        int total = 20;
        int pos = 10;
        int judge = 0;
        int stop = 0;

        while(pos>1){
            int now = total;

            for (int i = 0; i<now; i++){
                int current = choice();
                if(current == 1){
                    judge = 1;
                    total -= 1;
                }
            }
            
            if(judge == 1) stop +=1;

            pos -= 1;
            judge = 0;
        }

        if(total != 0) stop += 1;

        sum += stop;
    }

    cout<< sum/20<< endl;
    
    }

    return 0;
}




// #include <iostream>
// #include <vector>
// #include <cstdlib>
// #include <ctime>

// using namespace std;

// int simulateStops() {
//     const int numPassengers = 20;
//     const int numStations = 10;
//     vector<bool> passengers(numPassengers, true); // 每位旅客是否下车
//     int stops = 0;

//     for (int station = 0; station < numStations; ++station) {
//         bool someoneGotOff = false;
//         for (int i = 0; i < numPassengers; ++i) {
//             if (passengers[i] && (rand() % 10) < 1) { // 每个旅客有1/10的概率下车
//                 passengers[i] = false;
//                 someoneGotOff = true;
//             }
//         }
//         if (someoneGotOff) {
//             stops++;
//         }
//     }
//     return stops;
// }

// int main() {
//     const int numSimulations = 100000; // 模拟次数
//     int totalStops = 0;

//     // 初始化随机数种子
//     srand(static_cast<unsigned int>(time(0)));

//     // 进行多次模拟
//     for (int i = 0; i < numSimulations; ++i) {
//         totalStops += simulateStops();
//     }

//     // 计算期望值
//     double expectedStops = static_cast<double>(totalStops) / numSimulations;

//     cout << "The expected number of stops after " << numSimulations << " simulations is: " << expectedStops << endl;

//     return 0;
// }