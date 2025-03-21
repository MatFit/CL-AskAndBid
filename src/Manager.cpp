#include "Manager.h"
#include "Driver.h"
#include "Users.h"
#include <iostream>
#include <algorithm>


Manager* Manager::instance = nullptr;

Manager::Manager() {}

void Manager::matchBids(std::vector<Bid*>& bids, std::vector<Product*>& productsForSale, User* activeUser) {
    // We love auto
    for (auto bid : bids) {
        for (auto product : productsForSale) {
            if (bid->getBidPrice() == product->getProductPrice() && product->getOpenBid()) {
                product->setOpenBid(false);

                // Transfer money
                transferFunds(bid, product);
                
                // Add product to buyer's purchased items
                addProductToBuyer(bid->getUsername(), bid->getPassword(), product);
                
                // Notify
                activeUser->notify();

                std::string buyerLog = "Buyer " + activeUser->getUsername() + " purchased " + Utils::productToString(product->getProductType());
                std::string sellerLog = "Seller " + activeUser->getUsername() + " purchased " + Utils::productToString(product->getProductType());

                Driver::getInstance()->addToBuyerHistory(buyerLog);
                Driver::getInstance()->addToSellerHistory(sellerLog);

            }
        }
    }
}


void Manager::transferFunds(Bid* bid, Product* product) {
    for (auto buyer : Driver::getInstance()->getBuyers()) {
        if (buyer->getUsername() == bid->getUsername() && buyer->checkPassword(bid->getPassword())) {
            for (auto seller : Driver::getInstance()->getSellers()) {
                if (seller->getUsername() == product->getUsername() && 
                    seller->checkPassword(product->getPassword())) {
                    
                    double buyerBalance = buyer->getAccountBalance();
                    double sellerBalance = seller->getAccountBalance();
                    
                    // Update balances
                    buyer->setAccountBalance(buyerBalance - bid->getBidPrice());
                    seller->setAccountBalance(sellerBalance + bid->getBidPrice());
                    
                    
                    return;
                }
            }
        }
    }
}

void Manager::addProductToBuyer(std::string username, std::string password, Product* product) {
    for (auto buyer : Driver::getInstance()->getBuyers()) {
        if (buyer->getUsername() == username && buyer->checkPassword(password)) {
            // Append to Buyers purchased shiz
            buyer->addPurchasedProduct(product);
            return;
        }
    }
}

