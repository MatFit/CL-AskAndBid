#include "Manager.h"
#include "Driver.h"
#include "Users.h"
#include <iostream>
#include <algorithm>


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

/**
void Manager::resolveBids(std::vector<Bid*> bids, std::vector<Product*>& productForSale, std::vector<Product*>& sold) {
    // sort bids based on the highest bid
    std::sort(bids.begin(), bids.end());

    // iterate through each product in the products for sale
    for (auto& product : productForSale) {
        double highestBidPrice = 0;
        Bid* highestBid = nullptr;

        // find the highest bid for this product
        for (auto& bid : bids) {
            if (bid->getProductType() == product->getProductType()) {
                if (bid->getBidPrice() > highestBidPrice) {
                    highestBidPrice = bid->getBidPrice();
                    highestBid = bid;
                }
            }
        }

        // if the highest bid exists move the product to sold
        if (highestBid != nullptr) {
            sold.push_back(product);

            productForSale.erase(std::remove(productForSale.begin(), productForSale.end(), product), productForSale.end());
        }
    }
}
*/