/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is the header file that contains the structure of Users
*/
#ifndef USER_H
#define USER_H
#include "Bid.h"
#include <string>
#include <ostream>
#include <iostream>
#include <vector>



class User {
    public:
        User(std::string username_, std::string password_, std::string address_, std::string phone_no_, double account_balance_)
        :   username_(username_),
            password_(password_),
            address_(address_),
            phone_no_(phone_no_),
            account_balance_(account_balance_) {}

        virtual ~User();

        virtual void notify() = 0;    
        virtual void history() = 0; // Resolves undefined references
        virtual void dashboard() = 0; // Resolves undefined references

        void updateAccountInformation();
        void setAccountBalance(double price) { account_balance_ += price; }
        double getAccountBalance() const { return account_balance_; }
        std::string getUsername() { return username_; }
        std::string getPassword() { return password_; }
        std::string getAddress() { return address_; }
        std::string getNumber() { return phone_no_; }
        bool checkPassword(const std::string input) { return password_ == input; }

    protected:
        std::string username_;
        std::string password_;
        std::string address_;
        std::string phone_no_;
        double account_balance_;


    friend std::ostream& operator<<(std::ostream& os, const User &User){
        os << "              | Username : " << User.username_ << std::endl;
        os << "   User Info  | Phone Number : " << User.phone_no_ << std::endl;
        os << "              | Address : " << User.address_ << std::endl;

        return os;
    }
};




class Seller : public User {
    public:
        Seller(std::string username_, std::string password_, std::string address_, std::string phone_no_, double account_balance_)
        : User(username_, password_, address_, phone_no_, account_balance_) {}

        void productOverview(); // Sold or yet to be sold
        void adjustBidsforProducts();
        void placeProductforSale();
        void bidHistory();

        // Override Methods
        void history() override;
        void dashboard() override;
        void notify() override;

        bool checkPassword(const std::string input) { return password_ == input; }

        friend std::ostream& operator<<(std::ostream& os, const Seller &Seller){
            os << "              | Username : " << Seller.username_ << std::endl;
            os << "  Seller Info | Phone Number : " << Seller.phone_no_ << std::endl;
            os << "              | Address : " << Seller.address_ << std::endl;

            return os;
        }
};




class Buyer : public User {
    public:
    Buyer(std::string username_, std::string password_, std::string address_, std::string phone_no_, double account_balance_)
    : User(username_, password_, address_, phone_no_, account_balance_) {}


        void listProductsForSale(); // Finds product if bid is active for it
        void placeBidforProduct(); // places bid goes over to the vector in the Driver class
        void listBoughtItems();
        void viewBids();
        void addPurchasedProduct(Product *product) { boughtProducts.push_back(product); }

        // Override Methods
        void history() override;
        void dashboard() override;
        void notify() override;
        

        friend std::ostream& operator<<(std::ostream& os, const Buyer &Buyer){
            os << "              | Username : " << Buyer.username_ << std::endl;
            os << "  Buyer Info  | Phone Number : " << Buyer.phone_no_ << std::endl;
            os << "              | Address : " << Buyer.address_ << std::endl;

            return os;
        }
    private:
        std::vector<Product*> boughtProducts;
        
        // std::vector<Product*> boughtProducts = {new Phone(23, PRODUCT_QUALITY::NEW, "tenp", "teasdasd")}; was test this
};

#endif
