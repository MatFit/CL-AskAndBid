#include "Driver.h"
#include "BidManager.h"
#include "Users.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

Driver* Driver::instance = nullptr;
BidManager* Driver::bidManager = nullptr; 


Driver::Driver() {
    bidManager = BidManager::getInstance();
}

void Driver::Run() {
    storeFront();
    loadAccounts();
}



void Driver::loadAccounts() {
    std::ifstream buyer_data("data/buyer_data.csv");
    if (!buyer_data.is_open()) {
        std::cout << "Error opening buyer file" << std::endl;
        return;
    }

    std::string line;
    std::string line2;
    std::getline(buyer_data, line); // Skip first line with columns

    while (std::getline(buyer_data, line)) {
        std::istringstream ss(line);
        
        while (std::getline(ss, line2, ',')) {
            std::cout << line2 << std::endl;
            std::cout << "asdasd" << std::endl;
        }
    }
}


void Driver::storeFront() {
    std::string line;
    std::ifstream store_front;
    store_front.open("arts/storefront.txt");

    if (store_front.is_open()) {
        while (std::getline(store_front, line)) {
            std::cout << line << std::endl;
        }
        store_front.close();
    }
    else{
        std::cout << "asdasJHUIAYGSKDBJ" << std::endl;
    }
}
