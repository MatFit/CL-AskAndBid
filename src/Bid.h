/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is the header file that contains the structure of our bids
*/
#ifndef BID_H
#define BID_H
#include <string>
#include "Product.h"
#include "Utils.h"


class Bid {
    public:
        Bid(std::string username, std::string password, PRODUCT_TYPE product_type, double bid_price) :
        username(username),
        password(password),
        product_type(product_type),
        bid_price(bid_price) {}


        std::string getUsername() { return username; }
        std::string getPassword() { return password; }
        double getBidPrice() { return bid_price; }
        PRODUCT_TYPE getProductType() { return product_type; }

        friend std::ostream& operator<<(std::ostream& os, const Bid& bid) {
            os << "Product Type: " << Utils::productToString(bid.product_type) << " Bid Amount: " << bid.bid_price;
            return os;
        };

        friend bool operator<(const Bid& lhs, const Bid& rhs) {
            return lhs.bid_price > rhs.bid_price;
        };

    private:
        std::string username;
        std::string password;
        PRODUCT_TYPE product_type;
        double bid_price;
};

#endif

