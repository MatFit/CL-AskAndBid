#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <ostream>
#include <iostream>
#include <map>


enum PRODUCT_QUALITY {NEW, USED_VERY_GOOD, USED_GOOD, USED_OKAY};
enum PRODUCT_TYPE { ELECTRONICS_PHONE, MEDIA_AUDIOBOOK};



// Base
class Product {
    public:
        Product(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password) 
        : base_price(base_price), product_quality(product_quality), username(username), password(password) {}

        bool getOpenBid() { return is_open_bid; };
        void setOpenBid(const bool is_open_bid) { this->is_open_bid = is_open_bid; };
        double getProductPrice() { return base_price; }
        std::string getUsername() { return username; }
        std::string getPassword() { return password; }

    private:
        double base_price;
        PRODUCT_QUALITY product_quality;
        std::string username;
        std::string password;
        bool is_open_bid = false;
};




// 1st Layer
class Electronics : public Product {
    public:
        Electronics(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password) 
        : Product(base_price, product_quality, username, password) {}
};

class Phone : public Electronics {
    public:
        Phone(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password) 
        : Electronics(base_price, product_quality, username, password) {}
};




// 2nd Layer
class Media : public Product {
    public:
        Media(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password) 
        : Product(base_price, product_quality, username, password) {}
};

// MEDIA
class AudioBook : public Media {
    public:
        AudioBook(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password) 
        : Media(base_price, product_quality, username, password) {}
};


#endif
