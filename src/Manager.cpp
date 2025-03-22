/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is our manager class that handels money and bids
*/
#include "Manager.h"
#include "Driver.h"
#include "Users.h"
#include <iostream>
#include <algorithm>


Manager* Manager::instance = nullptr;

Manager::Manager() {}


/**
    Matches bids to products based on bid and product price.

    @param bids A vector of Bid pointers representing the current bids.
    @param productsForSale A vector of Product pointers representing the available products for sale.
    @param activeUser The currently logged-in user who will be notified after a successful match.
    @return Void. The function modifies the state of the product and bid lists, transfers funds, 
            adds purchase history, and updates the open bid status.
*/
void Manager::matchBids(std::vector<Bid*>& bids, std::vector<Product*>& productsForSale, User* activeUser) {
    auto bid_it = Driver::getInstance()->getBids().begin();
    
    while (bid_it != Driver::getInstance()->getBids().end()) {
        auto product_it = Driver::getInstance()->getProducts().begin();
        bool matchFound = false;
        
        while (product_it != Driver::getInstance()->getProducts().end() && !matchFound) {
            Bid* bid = *bid_it;
            Product* product = *product_it;
            
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
                
                // Remove matched bid and product from Driver's vectors by address
                bid_it = Driver::getInstance()->getBids().erase(bid_it);
                product_it = Driver::getInstance()->getProducts().erase(product_it);
                matchFound = true;
            } else {
                ++product_it;
            }
        }
        
        if (!matchFound) {
            ++bid_it; // Only increment if no match was found
        }
    }
}

/**
    Transfers funds from the buyer to the seller based on the matched bid and product.

    @param bid The Bid object representing the buyer's bid on the product.
    @param product The Product object representing the product being bought.
    @return Void. The function updates the account balances of the buyer and seller accordingly.
*/
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

/**
    Adds a purchased product to the specified buyer's list of purchased products.

    @param username The username of the buyer making the purchase.
    @param password The password of the buyer for authentication.
    @param product The Product object representing the product being purchased.
    @return Void. The function updates the buyer's purchase history by adding the product to their list of purchased products.
*/
void Manager::addProductToBuyer(std::string username, std::string password, Product* product) {
    for (auto buyer : Driver::getInstance()->getBuyers()) {
        if (buyer->getUsername() == username && buyer->checkPassword(password)) {
            // Append to Buyers purchased shiz
            buyer->addPurchasedProduct(product);
            return;
        }
    }
}

