#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <string>


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
int main() {
    double rest;
    std::cout << "enter rest -> ";
    std::cin >> rest; 
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

    int totalCents = static_cast<int>(std::round(rest * 100));
    std::cout << "========LOG=========" << std::endl;
    std::cout << "converted to hundrets -> " << totalCents << std::endl;
    
    int grivnas = totalCents / 100;
    int coins = totalCents % 100;
    
    std::cout << grivnas << std::endl;
    std::cout << coins << std::endl;
    std::cout << "====================" << std::endl;
    
    greedy_algorithm(UAH, COIN, grivnas, coins, UAH_register, COIN_register);
    
    
    return 0;
}