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
Manager* Driver::manager = nullptr; 

std::map<std::string, PRODUCT_TYPE> productMap = {
    {"ELECTRONICS_PHONE", PRODUCT_TYPE::ELECTRONICS_PHONE}
};

PRODUCT_TYPE stringToProduct(const std::string& str) {
    auto it = productMap.find(str);
    if (it != productMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid color string: " + str);
}



// Helper function to split csv with delimiter (",")
std::vector<std::string> split(std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t position = 0;
    std::string substring;
    
    while ((position = s.find(delimiter)) != std::string::npos) {
        substring = s.substr(0, position);
        tokens.push_back(substring);
        s.erase(0, position + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}




Driver::Driver() {
    manager = Manager::getInstance();
}

void Driver::Run() {
    Load();

    int input = 0;
    do {
        std::cout << "--------------------------------------" << std::endl;
        std::cout << "Log In or Create Account: \n";
        std::cout << "1.) Log In \n";
        std::cout << "2.) Create Account \n";
        std::cin >> input;
        std::cout << "--------------------------------------" << std::endl;


        if (input != 1 && input != 2){ std::cout << "Please choose valid input" << std::endl; }

    } while (input != 1 && input != 2);

    if (input == 1){ Login(); }
    else { CreateAccount(); }


    storeFront();

    if (activeUser == nullptr){ 
        std::cout << "No active user in session" << std::endl; 
        return;
    }

    std::cout << *activeUser << std::endl;
    activeUser->dashboard(); // -> handle the next phase stuff here?
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
    std::getline(buyer_data, row); // Skip first line with columns

    while (std::getline(buyer_data, row)) {
        std::vector<std::string> data = split(row, ",");
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

    std::getline(seller_data, row); // Skip first line with columns

    while (std::getline(seller_data, row)) {
        std::vector<std::string> data = split(row, ",");
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
    std::getline(bid_data, row); // Skip first line with columns

    while (std::getline(bid_data, row)) {
        std::vector<std::string> data = split(row, ",");
        Bid *bid = new Bid(data[0], data[1], stringToProduct(data[2]), std::stod(data[3]));
        bids.push_back(bid);
    }
    bid_data.close();




    
    // Product
    std::ifstream product_data("data/products.csv");
    if (!product_data.is_open()) {
        std::cout << "Error opening product file" << std::endl;
        return;
    }

    std::getline(product_data, row); // Skip first line with columns

    while (std::getline(product_data, row)) {
        std::vector<std::string> data = split(row, ",");
        Product *product = ProductFactory::createProduct(stringToProduct(data[2]), std::stod(data[3]), PRODUCT_QUALITY::NEW, data[0], data[1]);
        productsForSale.push_back(product);
    }
    product_data.close();




    std::cout << buyers.size() << std::endl;
    std::cout << sellers.size() << std::endl;
    std::cout << bids.size() << std::endl;
    std::cout << productsForSale.size() << std::endl;

}

void Driver::Login(){

    // Account type login
    int account_type = 0;
    while (true) {
        std::cout << "--------------------------------------" << std::endl;
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




    // File name
    std::string filename;
    if (account_type == 1){ filename = "data/buyer_data.csv"; }
    else { filename = "data/seller_data.csv"; }

    
    std::ifstream file(filename);
    if(!file.is_open()){ 
        std::cout << "Error opening file for Login" << std::endl; 
        return;
    }


    std::string input_username, input_password;
    int attempts = 3;

    do {
        std::cout << "Username : ";
        std::cin >> input_username;
        
        std::cout << "Password : ";
        std::cin >> input_password;



        std::string row;
        std::string delimiter = ",";
        bool found = false;
        
        while (std::getline(file, row)) {
            std::vector<std::string> data = split(row, delimiter);

            if (data[0] == input_username && data[1] == input_password) {
                std::cout << "account found" << std::endl;
                found = true;
                break;
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
    



    if (account_type == 1) { 
        for (const auto &b : buyers){
            if (b->getUsername() == input_username){
                activeUser = b;
            }
        }
    }
    else if (account_type == 2){
        for (const auto &s : sellers){
            if (s->getUsername() == input_username){
                activeUser = s;
            }
        }
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
        std::cout << "--------------------------------------" << std::endl;
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
