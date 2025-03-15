#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include <iostream>


int main(){
    Driver *driver = Driver::getInstance();
    driver->Run();
}
