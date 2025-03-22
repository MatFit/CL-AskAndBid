/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is the header file for manager that outlines the structer of the class
*/
#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include <string>
#include "Bid.h"
#include "Product.h"
#include "Users.h"

enum ACCOUNT_TYPE { BUYER, SELLER };

class Manager {
    public:
        static Manager* getInstance() {
            if (!instance) instance = new Manager();
            return instance;
        }
        
        void matchBids(std::vector<Bid*>& bids, std::vector<Product*>& productsForSale, User* activeUser);
        void transferFunds(Bid* bid, Product* product);
        void addProductToBuyer(std::string username, std::string password, Product* product);
    private:
        static Manager* instance;
        Manager();
};

#endif  // MANAGER_H
