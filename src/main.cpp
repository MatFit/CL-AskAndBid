/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is a simple main that makes a driver and runs it.
*/
#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include <iostream>


int main(){
    Driver *driver = Driver::getInstance();
    driver->Run();
}
