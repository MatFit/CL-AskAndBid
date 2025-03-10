#ifndef DRIVER_H
#define DRIVER_H
#include "Users.h"
#include <iostream>
#include <vector>


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
        void loadAccounts();

    private:
        static Driver* instance;
        static BidManager* bidManager;
        User* activeUser;

        std::vector<Seller*> sellers;
        std::vector<Buyer*> buyers;

        Driver();
};




#endif