#include "Bid.h"
#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include "Factory.h"
#include <limits>

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
    std::cout << "Dear " << username_ << ", your bid was successful! The product has been added to your purchases." << std::endl;
}

void Seller::history() {
    std::vector<std::string> temp = Driver::getInstance()->getSellerHistory();
    for (const auto &t : temp){
        std::cout << t << std::endl;
    }
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
        std::cout << "5.) Place product for sale" << std::endl;
        std::cout << "6.) Seller's History" << std::endl;
        std::cout << "7.) Exit" << std::endl;

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
                break;
            case 6:
                history();
                break;
            case 7:
                exit = true;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
        Manager::getInstance()->matchBids(Driver::getInstance()->getBids(), Driver::getInstance()->getProducts(), this);
        
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
// Curently not fully working because of no sell history
void Seller::bidHistory() {
    std::cout << "Your products.\n";
    std::vector<Product*> products = Driver::getInstance()->getProducts();
    int productCount = 1;
    bool exit = false;
    int input;

    while (exit == false) {
        std::cout << "Select product to view the bid history of.\n";

        for (const auto &p : products) {
            if (p->getUsername() == this->username_ && this->checkPassword(p->getPassword())) {
                std::cout << productCount << ".) " << *p << std::endl;
                productCount++;
            }
        }

        std::cin >> input;

        if (input > 0 && input <= productCount) {
            int check_count = 1;
            for (const auto &p : products) {
                if (p->getUsername() == this->username_ && this->checkPassword(p->getPassword())) {
                    if (check_count == productCount) {
                        std::cout << "Work in progress, sell history unavailable for products atm\n";
                        exit = true;
                    }
                    else {
                        check_count++;
                    }
                }
            }
            std::cout << "Critical error in bidHistory()\n";
        }
        else {
            std::cout << "Please enter a valid input\n";
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
    std::cout << "Dear " << username_ << ", your bid was successful! The product has been added to your purchases." << std::endl;
}

void Buyer::history() {
    std::vector<std::string> temp = Driver::getInstance()->getBuyerHistory();
    for (const auto &t : temp){
        std::cout << t << std::endl;
    }
}

void Buyer::dashboard() {
    bool exit = false;
    int input;


    do {
        std::cout << *this << std::endl;
        std::cout << "1.) Check Account Balance" << std::endl;
        std::cout << "2.) Update User Information" << std::endl;
        std::cout << "3.) View Bought Items" << std::endl;
        std::cout << "4.) View Products for Sale" << std::endl;
        std::cout << "5.) Place a bid" << std::endl;
        std::cout << "6.) View bids" << std::endl;
        std::cout << "7.) History" << std::endl;
        std::cout << "8.) Exit" << std::endl;
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
                listBoughtItems();
                break;
            case 4:
                listProductsForSale();
                break;
            case 5:
                placeBidforProduct();
                break;
            case 6:
                viewBids();
                break;
            case 7:
                history();
                break;
            case 8:
                exit = true;
                break;
            default:
                std::cout << "Invalid option" << std::endl;
        }
        Manager::getInstance()->matchBids(Driver::getInstance()->getBids(), Driver::getInstance()->getProducts(), this);



    } while (!exit);




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

void Buyer::listBoughtItems() {
    for (auto &b : boughtProducts){
        std::cout << b->getClassName() << " for " << b->getProductPrice() << std::endl;
    }
}

void Buyer::placeBidforProduct() {
    bool exit = false;
    PRODUCT_TYPE product_type;
    double bid_price;
    int input;

    do {
        std::cout << "Place bid for a product."  << std::endl;
        std::cout << "Item to place on bid: " << std::endl;
        std::cout << "1.) Phone " << std::endl;
        std::cout << "2.) Audiobook " << std::endl;
        std::cin >> input;
    

        switch (input) {
            case 1:
                product_type = PRODUCT_TYPE::ELECTRONICS_PHONE;
                exit = true;
                break;
            case 2:
                product_type = PRODUCT_TYPE::MEDIA_AUDIOBOOK;
                exit = true;
                break;
            default:
                std::cout << "Invalid Option" << std::endl;
        }
    } while(!exit);



    do {
        std::cout << "Bid Price: " << std::endl;
        if (std::cin >> bid_price && bid_price > 0) exit = true;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } while(!exit);

    Driver::getInstance()->addBid(username_, password_, product_type, bid_price);
}

void Buyer::viewBids() {
    std::vector<Bid*> bids = Driver::getInstance()->getBids();
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "CURRENT BIDS: " << std::endl;
    for (const auto &b : bids) {
        if (b->getUsername() == this->username_ && this->checkPassword(b->getPassword())) {
            std::cout << *b << std::endl;
        }
    }
    std::cout << "--------------------------------------" << std::endl;
}