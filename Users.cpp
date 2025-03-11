#include "Driver.h"
#include "BidManager.h"
#include "Users.h"

User::~User() {} // Undefined referance to v-table

void User::setPhoneNumber(std::string phone_no_){
    this->phone_no_ = phone_no_;
}

void User::setAddress(std::string address_){
    this->address_ = address_;
}

void User::updateAccountInformation() {
    std::cout << "Select Info to change.\n";
    std::cout << "1) Address.\n";
    std::cout << "2) Phone Number.\n";

    // Some user input if 1 -> ask for new address -> call set address
    // Some user input if 2 -> ask for new phone number -> call set phone number

    

}






// SELLER METHODS
void Seller::history() {
    std::cout << "Displaying seller history.\n";
}

void Seller::dashboard() {
    std::cout << "Showing seller dashboard.\n";
}

void Seller::productOverview() {
    std::cout << "Posting product for sale.\n";
}

void Seller::openBidforProduct() {
    std::cout << "Opening bid for a product.\n";
}

void Seller::closeBidforProduct() {
    std::cout << "Closing bid for a product.\n";
}


// BUYER METHOD

void Buyer::history() {
    std::cout << "Displaying seller history.\n";
}

void Buyer::dashboard() {
    std::cout << "Showing seller dashboard.\n";
}

void Buyer::findProductsForSale() {
    std::cout << "Finding products for sale.\n";
}

void Buyer::placeBidforProduct() {
    std::cout << "Place bid for a product.\n";
}