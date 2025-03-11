#include "Driver.h"
#include "BidManager.h"
#include "Users.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>
#include <string>

Driver* Driver::instance = nullptr;
BidManager* Driver::bidManager = nullptr; 


Driver::Driver() {
    bidManager = BidManager::getInstance();
}


void Driver::Run() {
    loadAccounts();

    int input = 0;
    do {
        
        std::cout << "Log In or Create Account: \n";
        std::cout << "1.) Log In \n";
        std::cout << "2.) Create Account \n";
        std::cin >> input;

        std::cout << "INPUT : " << input << std::endl;

        if (input != 1 && input != 2){ std::cout << "Please choose valid input" << std::endl; }

    } while (input != 1 && input != 2);


    if (input == 1){ Login(); }
    else { CreateAccount(); }


    storeFront();
    std::cout << *activeUser << std::endl;
    activeUser->dashboard(); // -> handle the next phase stuff here?

}



void Driver::loadAccounts() {
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
    std::vector<std::string> temp;
    std::getline(buyer_data, row); // Skip first line with columns

    while (std::getline(buyer_data, row)) {
        std::istringstream ss(row);
        
        while (std::getline(ss, data, ',')) {
            temp.push_back(data);
        }

        Buyer *buyer = new Buyer(temp[3], temp[0], temp[2], std::stod(temp[4]));
        buyers.push_back(buyer);
    }

    // Cleans
    row = "";
    data = "";
    temp.clear();
    

    // Sellers
    std::ifstream seller_data("data/seller_data.csv");
    if (!seller_data.is_open()) {
        std::cout << "Error opening buyer file" << std::endl;
        return;
    }

    std::getline(seller_data, row); // Skip first line with columns

    while (std::getline(seller_data, row)) {
        std::istringstream ss(row);
        
        while (std::getline(ss, data, ',')) {
            temp.push_back(data);
        }

        Seller *seller = new Seller(temp[3], temp[0], temp[2], std::stod(temp[4]));
        sellers.push_back(seller);
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
    else{
        std::cout << "asdasJHUIAYGSKDBJ" << std::endl;
    }
}


void Driver::Login(){
    std::cout << "We logging in baby" << std::endl;
    //




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
        if (std::cin >> account_type && (account_type == 1 || account_type == 2)) {
            break;
        }

        std::cout << "Invalid input. Please enter 1 or 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Get username
    std::cout << "Enter username: ";
    std::cin >> username;

    // Get password
    std::cout << "Enter password: ";
    std::cin >> password;

    // Clear buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Get address
    std::cout << "Enter address: ";
    std::getline(std::cin, address);

    // Get phone number
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phone_number);

    // Get account balance
    while (true) {
        std::cout << "Enter account balance: ";
        if (std::cin >> account_balance) break;
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    
    // File path
    const std::string filename = (account_type == 1) 
        ? "data/buyer_data.csv" 
        : "data/seller_data.csv";


    // Writing
    std::ofstream file(filename, std::ios::app); // Open in append mode
    if (file.is_open()) {
        file // Ensure the data starts on a new line
            << username << ","
            << password << ","
            << address << ","
            << phone_number << ","
            << account_balance << "\n";
        file.close();
    } else {
        std::cerr << "Error: Could not open file for writing!\n";
    }



    // Create User object
    if (account_type == 1) {
        Buyer *buyer = new Buyer(phone_number, username, address, account_balance);
        buyers.push_back(buyer);
        activeUser = buyer;
    } else {
        Seller *seller = new Seller(phone_number, username, address, account_balance);
        sellers.push_back(seller);
        activeUser = seller;
    }
}