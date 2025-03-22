#include "Driver.h"
#include "Manager.h"
#include "Users.h"
#include "Bid.h"
#include "Product.h"
#include "Factory.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <string>


Driver* Driver::instance = nullptr;


Driver::Driver() {}

void Driver::Run() {
    Load();

    int input = 0;
    do {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Log In or Create Account: \n";
        std::cout << "1.) Log In \n";
        std::cout << "2.) Create Account \n";
        std::cin >> input;


        if (input != 1 && input != 2){ std::cout << "Please choose valid input" << std::endl; }

    } while (input != 1 && input != 2);

    std::cout << "\n\n\n";
    if (input == 1){ Login(); }
    else { CreateAccount(); }
    std::cout << "\n\n\n";

    storeFront();

    if (activeUser == nullptr){ 
        std::cout << "No active user in session" << std::endl; 
        return;
    }

    
    activeUser->dashboard(); // -> handle the next phase stuff here?

    Save(); // Once user exits their dashboard this method is responsible to rewrite data back into the csv's
}

void Driver::Load() {
    /*
        I believe this method properly stores all accounts in the appropriate vectors in the
        meantime
    */

    // Buyers
    std::ifstream buyer_data("data/buyer_data.csv");
    if (!buyer_data.is_open()) {
        std::cout << "Error opening buyer file" << std::endl;
        return;
    }

    std::string row;
    std::string data;

    while (std::getline(buyer_data, row)) {
        std::vector<std::string> data = Utils::split(row, ",");
        Buyer *buyer = new Buyer(data[0], data[1], data[2], data[3], std::stod(data[4]));
        buyers.push_back(buyer);
    }
    buyer_data.close();
    


    
    // Sellers
    std::ifstream seller_data("data/seller_data.csv");
    if (!seller_data.is_open()) {
        std::cout << "Error opening buyer file" << std::endl;
        return;
    }


    while (std::getline(seller_data, row)) {
        std::vector<std::string> data = Utils::split(row, ",");
        Seller *seller = new Seller(data[0], data[1], data[2], data[3], std::stod(data[4]));
        sellers.push_back(seller);
    }
    seller_data.close();



    // Bids
    std::ifstream bid_data("data/bids.csv");
    if (!bid_data.is_open()) {
        std::cout << "Error opening bid file" << std::endl;
        return;
    }

    while (std::getline(bid_data, row)) {
        std::vector<std::string> data = Utils::split(row, ",");
        Bid *bid = new Bid(data[0], data[1], Utils::stringToProduct(data[2]), std::stod(data[3]));
        bids.push_back(bid);
    }
    bid_data.close();




    
    // Product
    std::ifstream product_data("data/products.csv");
    if (!product_data.is_open()) {
        std::cout << "Error opening product file" << std::endl;
        return;
    }


    while (std::getline(product_data, row)) {
        std::vector<std::string> data = Utils::split(row, ",");
        Product *product = ProductFactory::createProduct(Utils::stringToProduct(data[2]), std::stod(data[3]), PRODUCT_QUALITY::NEW, data[0], data[1], std::stoi(data[4]));
        productsForSale.push_back(product);
    }
    product_data.close();


    // Buyer Logs
    std::ifstream buyer_history("data/buyer_history.csv");
    if (!buyer_history.is_open()) {
        std::cout << "Error opening buyer history file" << std::endl;
        return;
    }


    while (std::getline(buyer_history, row)) {
        buyerHistory.push_back(row);
    }
    buyer_history.close();

    // Seller Logs
    std::ifstream seller_history("data/seller_history.csv");
    if (!seller_history.is_open()) {
        std::cout << "Error opening buyer history file" << std::endl;
        return;
    }


    while (std::getline(seller_history, row)) {
        sellerHistory.push_back(row);
    }
    seller_history.close();



    std::cout << "✅ Loaded Buyers from CSV | Size: " << buyers.size() << std::endl;
    std::cout << "✅ Loaded Sellers from CSV | Size: " << sellers.size() << std::endl;
    std::cout << "✅ Loaded Bids from CSV | Size: " << bids.size() << std::endl;
    std::cout << "✅ Loaded Products for Sale from CSV | Size: " << productsForSale.size() << std::endl;
    std::cout << "✅ Loaded Seller Transaction History | Size: " << sellerHistory.size() << std::endl;
    std::cout << "✅ Loaded Buyer Transaction History | Size: " << buyerHistory.size() << std::endl;

}

void Driver::Save() {
    // Save Buyers
    std::ofstream buyer_data("data/buyer_data.csv");
    if (!buyer_data.is_open()) {
        std::cout << "Error opening buyer file for writing" << std::endl;
        return;
    }

    for (const auto& buyer : buyers) {
        buyer_data << buyer->getUsername() << "," 
                   << buyer->getPassword() << "," 
                   << buyer->getAddress() << "," 
                   << buyer->getNumber() << "," 
                   << buyer->getAccountBalance() << std::endl;
    }
    buyer_data.close();


    
    // Save Sellers
    std::ofstream seller_data("data/seller_data.csv");
    if (!seller_data.is_open()) {
        std::cout << "Error opening seller file for writing" << std::endl;
        return;
    }

    for (const auto& seller : sellers) {
        seller_data << seller->getUsername() << "," 
                    << seller->getPassword() << "," 
                    << seller->getAddress() << "," 
                    << seller->getNumber() << "," 
                    << seller->getAccountBalance() << std::endl;
    }
    seller_data.close();
    


    // Save Bids
    std::ofstream bid_data("data/bids.csv");
    if (!bid_data.is_open()) {
        std::cout << "Error opening bid file for writing" << std::endl;
        return;
    }

    for (const auto& bid : bids) {
        bid_data << bid->getUsername() << "," 
                 << bid->getPassword() << "," 
                 << Utils::productToString(bid->getProductType()) << "," 
                 << bid->getBidPrice() << std::endl;
    }
    bid_data.close();
    


    // Save Products
    std::ofstream product_data("data/products.csv");
    if (!product_data.is_open()) {
        std::cout << "Error opening product file for writing" << std::endl;
        return;
    }

    for (const auto& product : productsForSale) {
        product_data << product->getUsername() << "," 
                     << product->getPassword() << "," 
                     << Utils::productToString(product->getProductType()) << "," 
                     << product->getProductPrice() << "," 
                     << product->getOpenBid() << std::endl;
    }
    product_data.close();
    

    // Save Buyer History
    std::ofstream buyer_history("data/buyer_history.csv");
    if (!buyer_history.is_open()) {
        std::cout << "Error opening buyer history file for writing" << std::endl;
        return;
    }

    for (const auto& history : buyerHistory) {
        buyer_history << history << std::endl;
    }
    buyer_history.close();
    

    
    // Save Seller History
    std::ofstream seller_history("data/seller_history.csv");
    if (!seller_history.is_open()) {
        std::cout << "Error opening seller history file for writing" << std::endl;
        return;
    }

    for (const auto& history : sellerHistory) {
        seller_history << history << std::endl;
    }
    seller_history.close();
}

void Driver::Login(){

    // Account type login
    int account_type = 0;
    while (true) {
        std::cout << "Log In Account Type? \n";
        std::cout << "1) Buyer\n";
        std::cout << "2) Seller\n";
        std::cout << "--------------------------------------" << std::endl;
        if (std::cin >> account_type && (account_type == 1 || account_type == 2)) {
            break;
        }

        std::cout << "Invalid input. Please enter 1 or 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }





    std::string input_username, input_password;
    int attempts = 3;
    bool found = false;
    

    do {
        std::cout << "Username : ";
        std::cin >> input_username;
        
        std::cout << "Password : ";
        std::cin >> input_password;



        if (account_type == 1){
            for (const auto &b : buyers) {
                if (b->getUsername() == input_username && b->checkPassword(input_password)) {
                    std::cout << "Account found!" << std::endl;
                    activeUser = b;
                    found = true;
                    break;
                }
            }
        }

        if (account_type == 2){
            for (const auto &s : sellers) {
                if (s->getUsername() == input_username && s->checkPassword(input_password)) {
                    std::cout << "Account found!" << std::endl;
                    activeUser = s;
                    found = true;
                    break;
                }
            }
        }

        if (!found){
            std::cout << "Invalid credientials. Try again" << std::endl;
            attempts -= 1; 
        }
        else { break; }
        

    } while(attempts > 0);

    if (attempts <= 0) {
        std::cout << "Maximum attempts reached." << std::endl;
        return;
    }

    if (activeUser == nullptr) {
        std::cout << "User found in file but not in memory" << std::endl;
    }
}

void Driver::CreateAccount() {
    std::cout << "We creating in baby" << std::endl;

    std::string username, password, address, phone_number;
    double account_balance;
    int account_type = 0;

    // Account type validation
    while (true) {
        std::cout << "Enter Account Type:\n";
        std::cout << "1) Buyer\n";
        std::cout << "2) Seller\n";
        std::cout << "--------------------------------------" << std::endl;
        if (std::cin >> account_type && (account_type == 1 || account_type == 2)) {
            break;
        }

        std::cout << "Invalid input. Please enter 1 or 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Clear buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone_number);

    // Get account balance
    while (true) {
        std::cout << "Enter account balance: ";
        if (std::cin >> account_balance){ break; }
        std::cout << "Invalid input. Please enter a number.\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    
    // File path
    std::string filename;

    if (account_type == 1){ filename = "data/buyer_data.csv"; }
    else { filename = "data/seller_data.csv"; }


    // Writing
    std::ofstream file(filename, std::ios::app); // Open file at the end of it (std::ios::append)
    if (file.is_open()) {
        file << username << "," << password << "," << address << "," << phone_number << "," << account_balance << "\n";
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing!\n";
    }



    // Create User object
    if (account_type == 1) {
        Buyer *buyer = new Buyer(phone_number, password, username, address, account_balance);
        buyers.push_back(buyer);
        activeUser = buyer;
    } else {
        Seller *seller = new Seller(phone_number, password, username, address, account_balance);
        sellers.push_back(seller);
        activeUser = seller;
    }
}

void Driver::storeFront() {
    std::string line;
    std::ifstream store_front;
    store_front.open("arts/storefront.txt");

    if (store_front.is_open()) {
        while (std::getline(store_front, line)) {
            std::cout << line << std::endl;
        }
        store_front.close();
    }
}
