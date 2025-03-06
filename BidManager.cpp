#include "Driver.h"
#include "BidManager.h"
#include "Users.h"
#include <iostream>

BidManager* BidManager::instance = nullptr;

BidManager::BidManager() {
    std::cout << "bidding big" << std::endl;
}
