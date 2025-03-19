#include "Manager.h"
#include "Driver.h"
#include "Users.h"
#include <iostream>

Manager* Manager::instance = nullptr;

Manager::Manager() {}

void Manager::matchBids(std::vector<Bid*>& bids, std::vector<Product*>& productsForSale) {
    int bid_size = bids.size();
    int productsForSale_size = productsForSale.size();

    for (int i = 0; i < bid_size; ++i) {
        for (int j = 0; j < productsForSale_size; ++j) {
            if (bids[i]->getBidPrice() == productsForSale[j]->getProductPrice() && productsForSale[j]->getOpenBid()) {
                notifyUser(bids[i]->getUsername(), bids[i]->getPassword(), BUYER);
                notifyUser(productsForSale[j]->getUsername(), productsForSale[j]->getPassword(), SELLER);
            }
        }
    }
}

void Manager::notifyUser(std::string username, std::string password, ACCOUNT_TYPE account_type) {
    // Handle buyer
    if (account_type == BUYER) {
        std::vector<Buyer*> temp_buyers = Driver::getInstance()->getBuyers();
        for (auto* b : temp_buyers) {
            if (b->getUsername() == username && b->checkPassword(password)) {
                // Handle buyer notification logic
            }
        }
    }

    // Handle seller
    if (account_type == SELLER) {
        std::vector<Seller*> temp_sellers = Driver::getInstance()->getSellers();
        for (auto* s : temp_sellers) {
            if (s->getUsername() == username && s->checkPassword(password)) {
                // Handle seller notification logic
            }
        }
    }
}
