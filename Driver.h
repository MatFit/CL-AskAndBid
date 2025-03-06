#ifndef DRIVER_H
#define DRIVER_H
#include "Users.h"
#include <iostream>


class BidManager; // Neat strat
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
    private:
        static Driver* instance;
        static BidManager* bidManager;
        User* activeUser;
        Driver();
};




#endif