#include "Factory.h"
#include "Product.h"

Product* ProductFactory::createProduct(PRODUCT_TYPE type, double base_price, PRODUCT_QUALITY product_quality, std::string username, std::string password, bool is_bid_open) {
    switch (type) {
        case ELECTRONICS_PHONE:
            return new Phone(base_price, product_quality, username, password, is_bid_open);
        
        case MEDIA_AUDIOBOOK:
            return new AudioBook(base_price, product_quality, username, password, is_bid_open);
        
        default:
            throw std::invalid_argument("Invalid product type");
    }
}