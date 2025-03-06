#include "Driver.h"
#include "BidManager.h"
#include "Users.h"

User::~User() {} // Undefined referance to v-table







// SELLER METHODS
void Seller::updateAccountInformation() {
    std::cout << "Updating seller account information.\n";
}

void Seller::history() {
    std::cout << "Displaying seller history.\n";
}

void Seller::dashboard() {
    std::cout << "Showing seller dashboard.\n";
}

void Seller::postProduct() {
    std::cout << "Posting product for sale.\n";
}

void Seller::openBid() {
    std::cout << "Opening bid for a product.\n";
}

void Seller::closeBid() {
    std::cout << "Closing bid for a product.\n";
}


// BUYER METHOD
void Buyer::updateAccountInformation() {
    std::cout << "Updating seller account information.\n";
}

void Buyer::history() {
    std::cout << "Displaying seller history.\n";
}

void Buyer::dashboard() {
    std::cout << "Showing seller dashboard.\n";
}

void Buyer::findProductsForSale() {
    std::cout << "Finding products for sale.\n";
}

void Buyer::placeBid() {
    std::cout << "Place bid for a product.\n";
}