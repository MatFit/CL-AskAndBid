#ifndef FACTORY_H
#define FACTORY_H

#include "Product.h"
#include <string>
#include <memory>

// Product types enum
enum PRODUCT_TYPE {
    ELECTRONICS_PHONE,
    MEDIA_AUDIOBOOK
};

// Factory class
class ProductFactory {
public:
    static Product* createProduct(PRODUCT_TYPE type, double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password);

private:
    ProductFactory() {} // Prevent instance of factory
};

#endif