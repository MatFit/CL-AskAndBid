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
        std::vector<std::string> getBuyerHistory() { return buyerHistory; }
        std::vector<std::string> getSellerHistory() { return sellerHistory; }

        void addToBuyerHistory(std::string log) { 
            buyerHistory.push_back(log);
        }
        void addToSellerHistory(std::string log) { 
            sellerHistory.push_back(log);
        }
        void addBid(std::string username, std::string password, PRODUCT_TYPE product_type, double bid_price) { 
            bids.push_back(new Bid(username, password, product_type, bid_price)); 
        }
        void addProductToSell(Product *product) {
            productsForSale.push_back(product);  
        }


        void Run();
        void Login();
        void CreateAccount();
        void Load();
        void Commit();
        

        void storeFront();

    private:
        static Driver* instance;
        User* activeUser = nullptr;

        std::vector<Seller*> sellers;
        std::vector<Buyer*> buyers;
        // Manager class will handle and notify
        std::vector<Bid*> bids;
        std::vector<Product*> productsForSale;
        std::vector<std::string> buyerHistory;
        std::vector<std::string> sellerHistory;

        Driver();
};




#endif
