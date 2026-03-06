#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <algorithm>

void greedy_algorithm(
    const std::vector<int>& UAH, 
    const std::vector<int>& COIN, 
    int grivnas, 
    int coins,
    std::map<int, int, std::greater<int>>& UAH_register, 
    std::map<int, int, std::greater<int>>& COIN_register
) {
    for (int bill : UAH) {
        int count = 0; 
        while (grivnas >= bill && UAH_register[bill] > 0) {
            grivnas -= bill;
            UAH_register[bill]--;
            count++; 
        }
        if (count > 0) {
            std::cout << bill << " UAH --> " << count << std::endl;
        }
    }
    for (int cent : COIN) {  
        int count = 0;             
        while (coins >= cent && COIN_register[cent] > 0) {          
            coins -= cent;
            COIN_register[cent]--;
            count++;                
        }
        if (count > 0){
            std::cout << cent << " COIN --> " << count << std::endl;
        }
    }
    if (grivnas > 0 || coins > 0) {
        std::cout << "EMPTYYYY" << std::endl;
    }
}

void refill(std::vector<int>& UAH, std::vector<int>& COIN, std::map<int, int, std::greater<int>>& UAH_reg, std::map<int, int, std::greater<int>>& COIN_reg) {
    int type, nominal, count;
    std::cout << "1 - UAH, 2 - COIN: ";
    std::cin >> type;
    std::cout << "nominal: ";
    std::cin >> nominal;
    std::cout << "count: ";
    std::cin >> count;

    if (type == 1) {
        if (UAH_reg[nominal] == 0) {
            UAH.push_back(nominal);
            std::sort(UAH.begin(), UAH.end(), std::greater<int>());
        }
        UAH_reg[nominal] += count;
    }
    else {
        if (COIN_reg[nominal] == 0) {
            COIN.push_back(nominal);
            std::sort(COIN.begin(), COIN.end(), std::greater<int>());
        }
        COIN_reg[nominal] += count;
        
    }
}

int main() {
    std::vector<int> UAH = {20, 10, 5, 2, 1};
    std::vector<int> COIN = {50, 25, 10, 5, 1};
    
    std::map<int, int, std::greater<int>> UAH_register{
        {20,5},
        {10,3},
        {5,0},
        {2,2},
        {1,7},
    };
    std::map<int, int, std::greater<int>> COIN_register{
        {50,5},
        {25,3},
        {10,4},
        {5,2},
        {1,7},
    };

    int mode;
    while (true) {
        std::cout << "\n1 - GET REST\n2 - REFILL\n0 - EXIT\n-> ";
        std::cin >> mode;

        if (mode == 0) {
            break;
            
        }

        if (mode == 1) {
            double rest;
            std::cout << "enter rest -> ";
            std::cin >> rest; 

            int totalCents = static_cast<int>(std::round(rest * 100));
            int grivnas = totalCents / 100;
            int coins = totalCents % 100;

            
            greedy_algorithm(UAH, COIN, grivnas, coins, UAH_register, COIN_register);

        } 
        else if (mode == 2) {
            refill(UAH, COIN, UAH_register, COIN_register);
        }
    }
    
    return 0;
}
