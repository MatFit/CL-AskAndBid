#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include <iostream>

Manager* Manager::instance = nullptr;

Manager::Manager() {
    std::cout << "bidding big" << std::endl;
}
