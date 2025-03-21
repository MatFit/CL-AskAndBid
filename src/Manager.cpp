#include "Manager.h"
#include "Driver.h"
#include "Users.h"
#include <iostream>
#include <algorithm>


Manager* Manager::instance = nullptr;

Manager::Manager() {}


// TODO : REMOVE BOTH BID AND PRODUCT AFTER SUCCESSFULL TRANSACTION, MAKE SURE VECTORS IN DRIVER CLASS ARE CHANGED
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
                
                // Notify active buyer user
                activeUser->notify();
                
                // Append history logs 
                std::string buyerLog = "Buyer " + bid->getUsername() + " bought " + Utils::productToString(product->getProductType()) + " from " + product->getUsername();
                std::string sellerLog = "Seller " + product->getUsername() + " sold " + Utils::productToString(product->getProductType()) + " to " + bid->getUsername();

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

