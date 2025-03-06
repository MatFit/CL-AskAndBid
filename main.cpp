#include "Driver.h"
#include "BidManager.h"
#include "Users.h"
#include <iostream>


int main(){
    Driver *driver = Driver::getInstance();
    driver->Run();
}
