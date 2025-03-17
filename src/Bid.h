#ifndef BID_H
#define BID_H
#include <string>
#include "Product.h"

class Bid {
    public:
        Bid(std::string username, std::string password, Product* product) :
        username(username),
        password(password),
        product(product) {}
    private:
        std::string username;
        std::string password;
        Product* product;
};

#endif

