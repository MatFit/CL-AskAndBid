#ifndef BID_H
#define BID_H
#include <string>
#include "Product.h"

class Bid {
    public:
        Bid(std::string username, std::string password, PRODUCT_TYPE product_type, double bid_price) :
        username(username),
        password(password),
        product_type(product_type),
        bid_price(bid_price) {}
    private:
        std::string username;
        std::string password;
        PRODUCT_TYPE product_type;
        double bid_price;
};

#endif

