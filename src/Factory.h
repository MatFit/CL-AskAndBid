/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is the header file that contains the structure of our factory class
*/
#ifndef FACTORY_H
#define FACTORY_H
#include "Product.h"
#include <string>
#include <memory>


// Factory class
class ProductFactory {
public:
    static Product* createProduct(PRODUCT_TYPE type, double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_bid_open);

private:
    ProductFactory() {} // Prevent instance of factory
};

#endif