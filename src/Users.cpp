/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is implementation for users that handels all seller and buyer specfic functionalites aswell as there front end implementations.
*/
#include "Bid.h"
#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include "Factory.h"
#include <limits>

User::~User() {} // Undefined referance to v-table

/**
    Allows the user to update their account information such as address and phone number.

    This function provides a menu with options to update the user's address, phone number, or exit the update process.

    @return Void. The function updates the user's information based on their selection and continues until the user chooses to exit.
*/
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

/**
    Notifies the seller about the successful purchase of their product.

    This method prints a message informing the seller that their product has been successfully sold 
    and has been added to their purchases list.

    @return Void. The function outputs a notification message to the console.
*/
void Seller::notify() {
    std::cout << "Dear " << username_ << ", your bid was successful! The product has been added to your purchases." << std::endl;
}

/**
    Displays the seller's purchase history.

    This method retrieves the seller's history from the driver instance and prints each entry to the console.
    The history includes the list of transactions related to the seller.

    @return Void. The function outputs the seller's history to the console.
*/
void Seller::history() {
    std::vector<std::string> temp = Driver::getInstance()->getSellerHistory();
    for (const auto &t : temp){
        std::cout << t << std::endl;
    }
}

/**
    Displays the seller's dashboard, where they can view and manage their account information, products, and transactions.

    This method provides a menu for the seller with options to:
    1. Check their account balance.
    2. Update their user information (address, phone number, etc.).
    3. View their products.
    4. Adjust bids for their products.
    5. Place new products for sale.
    6. View the seller's transaction history.
    7. Exit the dashboard.

    The method continuously loops to display the menu and handle the seller's input until they choose to exit.

    @return Void. The function modifies the seller's state and outputs information to the console, but does not return a value.
*/
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

/**
    Displays the list of products posted for sale by the seller.

    This method retrieves all products from the `Driver` and iterates through them to check if the product belongs to 
    the seller by matching the seller's username and password with the product's details. If a match is found, 
    the product is displayed in the console.

    @return Void. The function outputs information to the console but does not return a value.
*/
void Seller::productOverview() {
    std::cout << "Posting product for sale.\n";
    std::vector<Product*> products = Driver::getInstance()->getProducts();

    for (const auto &p : products){
        if (p->getUsername() == this->username_ && this->checkPassword(p->getPassword())){
            std::cout << *p << std::endl;
        }
    }
}

/**
    Displays the bid history for the seller's products.

    This method allows the seller to view the bid history for each of their listed products. It first prompts the user to 
    select a product from their own listings. Once a product is selected, the method checks if the bid history for the 
    selected product is available. If not, a message indicating that the history is unavailable is displayed. 

    @return Void. The function outputs information to the console but does not return a value.
*/
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

/**
    Allows the seller to adjust the bid status of their products.

    This method presents the seller with the option to either make a product biddable or non-biddable. The seller can 
    choose to enable or disable bids for each of their listed products. If the product is set to be biddable, 
    the product's bid status is updated accordingly. If the seller selects an invalid option, they are prompted to try again.

    @return Void. The function outputs information to the console but does not return a value.
*/
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

/**
    Allows the seller to place a product for sale.

    This method prompts the seller to choose a product type, specify its condition, and set a price for it. The seller 
    can cancel the action at any time. After selecting the product type, condition, and price, the method creates a new 
    product using the ProductFactory and adds it to the list of products for sale. If the product creation is successful, 
    it is added to the system and a confirmation message is displayed. If there is an error, the seller is notified and 
    prompted to try again.

    @return Void. The function does not return any value, but outputs information to the console regarding the 
            success or failure of the product placement.
*/
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

/**
    Notifies the buyer that their bid was successful and the product has been added to their purchases.

    This method outputs a message to the console informing the buyer that their bid was successful and that the 
    product they bid on has been added to their list of purchases.

    @return Void. This function does not return any value, but simply outputs a notification to the console.
*/
void Buyer::notify() {
    std::cout << "Dear " << username_ << ", your bid was successful! The product has been added to your purchases." << std::endl;
}

/**
    Displays the purchase history of the buyer.

    This method retrieves the purchase history for the current buyer from the Driver instance and 
    outputs each entry to the console.

    @return Void. This function does not return any value but prints each history entry to the console.
*/
void Buyer::history() {
    std::vector<std::string> temp = Driver::getInstance()->getBuyerHistory();
    for (const auto &t : temp){
        std::cout << t << std::endl;
    }
}

/**
    Displays the dashboard for the buyer and allows interaction with various buyer options.

    The dashboard presents a menu with options to view the buyer's account balance, update their
    user information, view bought items, view products for sale, place bids, view current bids, 
    check purchase history, or exit the dashboard. After each action, the dashboard is updated 
    based on the user's input.

    @return Void. This function does not return any value. It loops until the user exits the dashboard.
*/
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

/**
    Displays all the products available for sale in the product store.

    This function retrieves all the products from the system and prints their details, allowing
    the buyer to view the products currently available for purchase. Each product is displayed
    with a space between them for readability.

    @return Void. This function does not return any value.
*/
void Buyer::listProductsForSale() {
    std::cout << "PRODUCT STORE \n" << std::endl;
    std::vector<Product*> products = Driver::getInstance()->getProducts();

    for (const auto &p : products){
        std::cout << *p << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        
    }
}

/**
    Displays a list of products that the buyer has purchased.

    This function iterates through the `boughtProducts` collection and prints the name of each
    product (via `getClassName()`) along with its price (via `getProductPrice()`), allowing the
    buyer to review their past purchases.

    @return Void. This function does not return any value.
*/
void Buyer::listBoughtItems() {
    for (auto &b : boughtProducts){
        std::cout << b->getClassName() << " for " << b->getProductPrice() << std::endl;
    }
}

/**
    Allows the buyer to place a bid on a product.

    This function presents the buyer with a list of available products to bid on. The buyer 
    selects a product and enters a bid price. The bid price must be greater than zero. 
    If the input is valid, the bid is added to the system via the `Driver` instance. If 
    the buyer cancels the action (by selecting option `0`), the process is aborted.

    @return Void. This function does not return any value.
*/
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

/**
    Displays the current bids placed by the buyer.

    This function retrieves all bids and filters those associated with the current 
    buyer's username. It checks the bid's associated password for validity before 
    displaying the details of the bid. If the bid matches the buyer, it is printed 
    to the console. The list of bids is enclosed between separator lines for clarity.

    @return Void. This function does not return any value.
*/
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
