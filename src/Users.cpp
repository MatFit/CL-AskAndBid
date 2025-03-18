#include "Bid.h"
#include "Driver.h"
#include "Manager.h"
#include "Users.h"

User::~User() {} // Undefined referance to v-table


void User::updateAccountInformation() {
    std::string input = "";

    // Some user input if 1 -> ask for new address -> call set address
    // Some user input if 2 -> ask for new phone number -> call set phone number
    while (input != "3") {

        std::cout << "Select Info to change.\n";
        std::cout << "1) Address.\n";
        std::cout << "2) Phone Number.\n";
        std::cout << "3) Exit.\n";

        std::cin >> input;

        if (input == "1") {
            std::cout << "Please enter the new address.\n";
            std::cin >> input;
            address_ = input;
        }
        else if (input == "2") {
            std::cout << "Please enter the new phone number.\n";
            std::cin >> input;
            phone_no_ = input; // maybe sanatize this input latter
        }
        else {
            std::cout << "Please enter a valid input.\n";
        }
    }

    return;

}




// SELLER METHODS
void Seller::notify() {
    std::cout << "Notifying seller.\n";
}

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
void Buyer::notify() {
    std::cout << "Notifying buyer.\n";
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

void Buyer::placeBidforProduct() {
    std::cout << "Place bid for a product.\n";
}
