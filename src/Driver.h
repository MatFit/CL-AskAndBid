#ifndef DRIVER_H
#define DRIVER_H
#include "Users.h"
#include "Factory.h"
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
        std::vector<Seller*>& getSellers() { return sellers; }
        std::vector<Buyer*>& getBuyers() { return buyers; }
        std::vector<Bid*>& getBids() { return bids; }
        std::vector<Product*>& getProducts() { return productsForSale; }


        void addBid(std::string username, std::string password, PRODUCT_TYPE product_type, double bid_price) { 
            bids.push_back(new Bid(username, password, product_type, bid_price)); 
        }
        // void addProduct(Product* product) { productsForSale.push_back(product); }


        void Run();
        void Login();
        void CreateAccount();
        void Load();
        void Commit();
        

        void storeFront();

    private:
        static Driver* instance;
        static Manager* manager;
        User* activeUser = nullptr;

        std::vector<Seller*> sellers;
        std::vector<Buyer*> buyers;
        // Manager class will handle and notify
        std::vector<Bid*> bids;
        std::vector<Product*> productsForSale;

        Driver();
};




#endif