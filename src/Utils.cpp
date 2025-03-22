#include "Utils.h"

const std::map<PRODUCT_TYPE, std::string> Utils::typeToStringMap = {
    {PRODUCT_TYPE::ELECTRONICS_PHONE, "ELECTRONICS_PHONE"},
    {PRODUCT_TYPE::MEDIA_AUDIOBOOK, "MEDIA_AUDIOBOOK"},
    {PRODUCT_TYPE::FURNITURE_COUCH, "FURNITURE_COUCH"},
    {PRODUCT_TYPE::TOY_ACTIONFIGURE, "TOY_ACTIONFIGURE"},
    {PRODUCT_TYPE::WEAPON_SUPERSWORD, "WEAPON_SUPERSWORD"}
};

const std::map<std::string, PRODUCT_TYPE> Utils::stringToTypeMap = {
    {"ELECTRONICS_PHONE", PRODUCT_TYPE::ELECTRONICS_PHONE},
    {"MEDIA_AUDIOBOOK", PRODUCT_TYPE::MEDIA_AUDIOBOOK},
    {"FURNITURE_COUCH", PRODUCT_TYPE::FURNITURE_COUCH},
    {"TOY_ACTIONFIGURE", PRODUCT_TYPE::TOY_ACTIONFIGURE},
    {"WEAPON_SUPERSWORD", PRODUCT_TYPE::WEAPON_SUPERSWORD}
};



std::string Utils::productToString(const PRODUCT_TYPE& type) {
    auto it = typeToStringMap.find(type);
    if (it != typeToStringMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid product type");
}

PRODUCT_TYPE Utils::stringToProduct(const std::string& str) {
    auto it = stringToTypeMap.find(str);
    if (it != stringToTypeMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid product string: " + str);
}

std::vector<std::string> Utils::split(std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t position = 0;
    std::string substring;
    
    while ((position = s.find(delimiter)) != std::string::npos) {
        substring = s.substr(0, position);
        tokens.push_back(substring);
        s.erase(0, position + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}