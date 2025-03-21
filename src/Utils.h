#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <map>
#include <vector>
#include "Product.h"

class Utils {
private:
    static const std::map<PRODUCT_TYPE, std::string> typeToStringMap;
    static const std::map<std::string, PRODUCT_TYPE> stringToTypeMap;

public:
    static std::string productToString(const PRODUCT_TYPE& type);
    static PRODUCT_TYPE stringToProduct(const std::string& str);
    static std::vector<std::string> split(std::string& s, const std::string& delimiter);
};

#endif


