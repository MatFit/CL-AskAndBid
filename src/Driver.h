#ifndef DRIVER_H
#define DRIVER_H
#include "Users.h"
#include <iostream>
#include <vector>
#include <string>


class Manager;
class Driver {
    public:
        static Driver* getInstance(){
            if (instance == nullptr) {
                instance = new Driver();
            }
            return instance;
        };


        void Run();
        void Login();
        void CreateAccount();
        

        void storeFront();
        void load();

    private:
        static Driver* instance;
        static Manager* manager;
        User* activeUser = nullptr;

        std::vector<Seller*> sellers;
        std::vector<Buyer*> buyers;

        Driver();
};




#endif