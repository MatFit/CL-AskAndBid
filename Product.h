#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <ostream>
#include <iostream>

enum PRODUCT_QUALITY {NEW, USED_VERY_GOOD, USED_GOOD, USED_OKAY};

// Base
class Product {
    public:
        Product(double base_price, PRODUCT_QUALITY product_quality) 
        : base_price(base_price), product_quality(product_quality) {}
    private:
        double base_price;
        PRODUCT_QUALITY product_quality;
};




// 1st Layer
class Electronics : public Product {
    public:
        Electronics(double base_price, PRODUCT_QUALITY product_quality) 
        : Product(base_price, product_quality) {}
};

class Phone : public Electronics {
    public:
        Phone(double base_price, PRODUCT_QUALITY product_quality) 
        : Electronics(base_price, product_quality) {}
};

class Tablet : public Electronics {
    public:
        Tablet(double base_price, PRODUCT_QUALITY product_quality) 
        : Electronics(base_price, product_quality) {}
};

class Laptop : public Electronics {
    public:
        Laptop(double base_price, PRODUCT_QUALITY product_quality) 
        : Electronics(base_price, product_quality) {}
};







// 2nd Layer
class Media : public Product {
    public:
        Media(double base_price, PRODUCT_QUALITY product_quality) 
        : Product(base_price, product_quality) {}
};

// MEDIA
class AudioBook : public Media {
    public:
        AudioBook(double base_price, PRODUCT_QUALITY product_quality) 
        : Media(base_price, product_quality) {}
};

class Podcast : public Media {
    public:
        Podcast(double base_price, PRODUCT_QUALITY product_quality) 
        : Media(base_price, product_quality) {}
};

class Song : public Media {
    public:
        Song(double base_price, PRODUCT_QUALITY product_quality) 
        : Media(base_price, product_quality) {}
};

#endif
