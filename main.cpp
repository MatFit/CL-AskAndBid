#include "headers/Driver.h"
#include "headers/Manager.h"
#include "headers/Users.h"
#include <iostream>


int main(){
    Driver *driver = Driver::getInstance();
    driver->Run();
}
