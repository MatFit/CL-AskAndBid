#include "Bid.h"
#include "Driver.h"
#include "Manager.h"
#include "Users.h"

User::~User() {} // Undefined referance to v-table


void User::updateAccountInformation() {
    int input;

    while (true) {
        std::cout << "Select Info to change.\n";
        std::cout << "1) Address\n";
        std::cout << "2) Phone Number\n";
        std::cout << "3) Exit\n";

        std::cin >> input;

        switch (input) {
            case 1:
                std::cout << "Please enter the new address: ";
                std::cin.ignore();
                std::getline(std::cin, address_);
                break;
            case 2:
                std::cout << "Please enter the new phone number: ";
                std::cin >> phone_no_;
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}




// SELLER METHODS
void Seller::notify() {
    std::cout << "Notifying seller.\n";
}

void Seller::history() {
    std::cout << "Displaying seller history.\n";
}

void Seller::dashboard() {
    bool exit = false;
    int input;

    do {
        std::cout << *this << std::endl;
        std::cout << "1.) Check Account Balance" << std::endl;
        std::cout << "2.) Update User Information" << std::endl;
        std::cout << "3.) Overview Your Products" << std::endl;
        std::cout << "4.) Adjust bids for products" << std::endl;
        std::cout << "5.) Exit" << std::endl;

        std::cin >> input;

        switch (input) {
            case 1:
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "ACCOUT BALANCE: " << getAccountBalance() << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                break;
            case 2:
                updateAccountInformation();
                break;
            case 3:
                productOverview();
                break;
            case 4:
                adjustBidsforProducts();
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
    } while (!exit);
    std::cout << "ASDAS" << std::endl;

}

void Seller::productOverview() {
    std::cout << "Posting product for sale.\n";
    std::vector<Product*> products = Driver::getInstance()->getProducts();

    for (const auto &p : products){
        if (p->getUsername() == this->username_ && this->checkPassword(p->getPassword())){
            std::cout << *p << std::endl;
        }
    }
}

void Seller::adjustBidsforProducts() {
    int input;
    std::vector<Product*> products = Driver::getInstance()->getProducts();

    for (const auto &p : products){
        if (p->getUsername() == this->username_ && this->checkPassword(p->getPassword())){
            
            while (true) {
                std::cout << *p << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "Make Biddable? " << std::endl;
                std::cout << "1.) Yes " << std::endl;
                std::cout << "2.) No " << std::endl;
                std::cin >> input;
                
                if (input == 1){
                    p->setOpenBid(true);
                    break;
                }
                else if (input == 2){
                    p->setOpenBid(false);
                    break;
                }
                else{
                    std::cout << "Invalid choice youngin" << std::endl;
                }
            }


        }
    }
}


// BUYER METHOD
void Buyer::notify() {
    std::cout << "Notifying buyer.\n";
}

void Buyer::history() {
    std::cout << "Displaying buyer history.\n";
}

void Buyer::dashboard() {
    bool exit = false;
    int input;


    do {
        std::cout << *this << std::endl;
        std::cout << "1.) Check Account Balance" << std::endl;
        std::cout << "2.) Update User Information" << std::endl;
        std::cout << "3.) View Products for Sale" << std::endl;
        std::cout << "4.) Place a bid" << std::endl;
        std::cout << "5.) Exit" << std::endl;
        std::cin >> input; 

        switch (input) { 
            case 1:
                std::cout << "--------------------------------------" << std::endl;
                std::cout << "ACCOUT BALANCE: " << getAccountBalance() << std::endl;
                std::cout << "--------------------------------------" << std::endl;
                break;
            case 2:
                updateAccountInformation();
                break;
            case 3:
                listProductsForSale();
                break;
            case 4:
                placeBidforProduct();
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
    } while (!exit);




    /*
        List out options of what they can do:
        - View Products
        - Place bid
        - Check Account balance (Tibbles)
        - Update user Info (Tibbles)
        - Get an overview of the bids they have placed
        - View the history of products they have bought

    */
}
void Buyer::listProductsForSale() {
    std::cout << "PRODUCT STORE \n" << std::endl;
    std::vector<Product*> products = Driver::getInstance()->getProducts();

    for (const auto &p : products){
        std::cout << *p << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        
    }
}

void Buyer::placeBidforProduct() {
    std::cout << "Place bid for a product.\n";
}
