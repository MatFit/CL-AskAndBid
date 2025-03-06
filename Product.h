#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <ostream>
#include <iostream>

enum PRODUCT_QUALITY = {NEW, USED_VERY_GOOD, USED_GOOD, USED_OKAY};

// Base
class Product {
    public:
        Product();
    private:
        double base_price;
};




// 1st Layer
class Electronics : public Product {
    public:
        Electronics(double base_price) : Product(base_price) {};
    private:
        PRODUCT_QUALITY quality;
};

// In the mean time
// class Vehicles : public Product {
//     public:
//         Vehicles(double base_price) : Product(base_price) {};
//     private:
//         PRODUCT_QUALITY quality;
// };

// class Furniture : public Product {
//     public:
//     Furniture(double base_price) : Product(base_price) {};
//     private:
//         PRODUCT_QUALITY quality;
// };

// class Media : public Product {
//     public:
//         Media(double base_price) : Product(base_price) {};
//     private:
//         PRODUCT_QUALITY quality;
// };




// ELECTRONICS
class Phone : public Electronics {
    public:
        Electronics(double base_price) : Product(base_price) {};
    private:
        PRODUCT_QUALITY quality;
};

class Tablet : public Electronics {
    public:
        Electronics(double base_price) : Product(base_price) {};
    private:
        PRODUCT_QUALITY quality;
};

class Laptop : public Electronics {
    public:
        Electronics(double base_price) : Product(base_price) {};
    private:
        PRODUCT_QUALITY quality;
};




#endif