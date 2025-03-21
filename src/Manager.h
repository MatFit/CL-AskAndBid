#ifndef MANAGER_H
#define MANAGER_H
#include <vector>
#include <string>
#include "Bid.h"
#include "Product.h"

enum ACCOUNT_TYPE { BUYER, SELLER };

class Manager {
    public:
        static Manager* getInstance() {
            if (!instance) instance = new Manager();
            return instance;
        }
        
        void matchBids(std::vector<Bid*>& bids, std::vector<Product*>& productsForSale);
        void notifyUser(std::string username, std::string password, ACCOUNT_TYPE account_type);
        // void resolveBids(std::vector<Bid*> bids, std::vector<Product*>& productForSale);
    private:
        static Manager* instance;
        Manager();
};

#endif  // MANAGER_H
