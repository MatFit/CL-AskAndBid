#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <ostream>
#include <iostream>
#include <map>

enum PRODUCT_QUALITY {NEW, USED_VERY_GOOD, USED_GOOD, USED_OKAY};
enum PRODUCT_TYPE {ELECTRONICS_PHONE, MEDIA_AUDIOBOOK};

inline std::string qualityToString(PRODUCT_QUALITY quality) {
    switch(quality) {
        case NEW: return "New";
        case USED_VERY_GOOD: return "Used - Very Good";
        case USED_GOOD: return "Used - Good";
        case USED_OKAY: return "Used - Okay";
        default: return "Unknown";
    }
}

// Base
class Product {
    public:
        Product(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_open_bid, PRODUCT_TYPE product_type) 
        : base_price(base_price), product_quality(product_quality), username(username), password(password), is_open_bid(is_open_bid), product_type(product_type) {}

        bool getOpenBid() { return is_open_bid; }
        void setOpenBid(const bool is_open_bid) { this->is_open_bid = is_open_bid; }
        double getProductPrice() { return base_price; }
        std::string getUsername() { return username; }
        std::string getPassword() { return password; }
        PRODUCT_QUALITY getProductQuality() { return product_quality; }
        PRODUCT_TYPE getProductType() { return product_type; }

        virtual std::string getClassName() const { return "Product"; }
        friend std::ostream& operator<<(std::ostream& os, const Product& product);
    
    private:
        double base_price;
        PRODUCT_QUALITY product_quality;
        std::string username;
        std::string password;
        bool is_open_bid;
        PRODUCT_TYPE product_type;
};

inline std::ostream& operator<<(std::ostream& os, const Product& product) {
    os << "------------------------------------------" << std::endl;
    os << product.getClassName() << std::endl;
    os << "     Username: " << product.username << std::endl;
    os << "     Price: " << product.base_price << std::endl;
    os << "     Quality: " << qualityToString(product.product_quality) << std::endl;
    os << "     Is On Bid: " << (product.is_open_bid ? "Yes" : "No") << std::endl;
    os << "------------------------------------------" << std::endl;
    return os;
}

// 1st Layer
class Electronics : public Product {
    public:
        Electronics(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_open_bid, PRODUCT_TYPE product_type) 
        : Product(base_price, product_quality, username, password, is_open_bid, product_type) {}

        std::string getClassName() const override { return "Electronics"; }
};

class Phone : public Electronics {
    public:
        Phone(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_open_bid, PRODUCT_TYPE product_type) 
        : Electronics(base_price, product_quality, username, password, is_open_bid, product_type) {}

        std::string getClassName() const override { return "Phone"; }
};

// 2nd Layer
class Media : public Product {
    public:
        Media(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_open_bid, PRODUCT_TYPE product_type) 
        : Product(base_price, product_quality, username, password, is_open_bid, product_type) {}

        std::string getClassName() const override { return "Media"; }
};

class AudioBook : public Media {
    public:
        AudioBook(double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_open_bid, PRODUCT_TYPE product_type) 
        : Media(base_price, product_quality, username, password, is_open_bid, product_type) {}

        std::string getClassName() const override { return "Audiobook"; }
};

#endif
