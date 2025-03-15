#include "headers/Driver.h"
#include "headers/Manager.h"
#include "headers/Users.h"
#include <iostream>

Manager* Manager::instance = nullptr;

Manager::Manager() {
    std::cout << "bidding big" << std::endl;
}
