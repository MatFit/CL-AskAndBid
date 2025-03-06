#include "Driver.h"
#include "BidManager.h"
#include "Users.h"
#include <iostream>
#include <fstream>

Driver* Driver::instance = nullptr;
BidManager* Driver::bidManager = nullptr; 


Driver::Driver() {
    bidManager = BidManager::getInstance();

}

void Driver::Run() {
    storeFront();
    
    Seller *seller = new Seller(1,"2","2",3);
    std::cout << *seller << std::endl;

    seller->dashboard();

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
