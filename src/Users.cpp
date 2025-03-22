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
                placeProductforSale();
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
// TODO : GIVE SELLERS THE FEATURE TO PLACE THEIR PRODUCTS FOR SALE
void Seller::placeProductforSale() {
    int input_product;
    int input_quality;
    double input_price;
    
    do {
        std::cout << "What Product do you want to post?" << std::endl;
        std::cout << "1.) Phone" << std::endl;
        std::cout << "2.) Audiobook" << std::endl;
        std::cout << "3.) Couch" << std::endl;
        std::cout << "4.) Action Figure" << std::endl;
        std::cout << "5.) Super Sword" << std::endl;
        std::cout << "0.) Cancel" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> input_product;
        
        if (input_product == 0) {
            return;
        }
        
        if (input_product < 1 || input_product > 5) {
            std::cout << "Invalid product choice. Please try again." << std::endl;
            continue;
        }
        
        std::cout << "What condition?" << std::endl;
        std::cout << "0.) NEW" << std::endl;
        std::cout << "1.) USED_VERY_GOOD" << std::endl;
        std::cout << "2.) USED_GOOD" << std::endl;
        std::cout << "3.) USED_OKAY" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> input_quality;
        
        if (input_quality < 0 || input_quality > 3) {
            std::cout << "Invalid quality choice. Please try again." << std::endl;
            continue;
        }
        
        std::cout << "Enter price: $";
        std::cin >> input_price;
        
        if (input_price <= 0) {
            std::cout << "Price must be greater than zero. Please try again." << std::endl;
            continue;
        }
        
        break;
        
    } while (true);
    
    PRODUCT_TYPE type;
    switch (input_product) {
        case 1: type = PRODUCT_TYPE::ELECTRONICS_PHONE; break;
        case 2: type = PRODUCT_TYPE::MEDIA_AUDIOBOOK; break;
        case 3: type = PRODUCT_TYPE::FURNITURE_COUCH; break;
        case 4: type = PRODUCT_TYPE::TOY_ACTIONFIGURE; break;
        case 5: type = PRODUCT_TYPE::WEAPON_SUPERSWORD; break;
        default:
            std::cout << "Invalid product type." << std::endl;
            return;
    }
    
    PRODUCT_QUALITY quality = static_cast<PRODUCT_QUALITY>(input_quality);
    Product* newProduct = ProductFactory::createProduct(type, input_price, quality, username_, password_, true);
    
    if (newProduct) {
        std::cout << "Product successfully placed for sale!" << std::endl;
        std::cout << *newProduct << std::endl;
        Driver::getInstance()->addProductToSell(newProduct);
    } else {
        std::cout << "Failed to create product. Please try again." << std::endl;
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
    int input_product;
    double input_price;
    
    do {
        std::cout << "What Product do you want to bid on?" << std::endl;
        std::cout << "1.) Phone" << std::endl;
        std::cout << "2.) Audiobook" << std::endl;
        std::cout << "3.) Couch" << std::endl;
        std::cout << "4.) Action Figure" << std::endl;
        std::cout << "5.) Super Sword" << std::endl;
        std::cout << "0.) Cancel" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> input_product;
        
        if (input_product == 0) {
            return;
        }
        
        if (input_product < 1 || input_product > 5) {
            std::cout << "Invalid product choice. Please try again." << std::endl;
            continue;
        }
        
        std::cout << "Enter bid price: $";
        std::cin >> input_price;
        
        if (input_price <= 0) {
            std::cout << "Bid price must be greater than zero. Please try again." << std::endl;
            continue;
        }
        
        break;
        
    } while (true);
    
    PRODUCT_TYPE type;
    switch (input_product) {
        case 1: type = PRODUCT_TYPE::ELECTRONICS_PHONE; break;
        case 2: type = PRODUCT_TYPE::MEDIA_AUDIOBOOK; break;
        case 3: type = PRODUCT_TYPE::FURNITURE_COUCH; break;
        case 4: type = PRODUCT_TYPE::TOY_ACTIONFIGURE; break;
        case 5: type = PRODUCT_TYPE::WEAPON_SUPERSWORD; break;
        default:
            std::cout << "Invalid product type." << std::endl;
            return;
    }
    
    Driver::getInstance()->addBid(username_, password_, type, input_price);
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
