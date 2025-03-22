/**
Nolan Tibbles and Mathis Fituwi
Homework 3
This is the header file that contains the implementaion of utility functions and some string casting
*/
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


/**
    Converts a PRODUCT_TYPE to its corresponding string representation.

    This function looks up the provided PRODUCT_TYPE in a map that associates each 
    product type with a string. If the type is found, its string representation is 
    returned. If the type is not found, an exception is thrown indicating an invalid 
    product type.

    @param type The PRODUCT_TYPE to convert.
    @return A string representing the product type.
    @throws std::invalid_argument If the product type is not found in the map.
*/
std::string Utils::productToString(const PRODUCT_TYPE& type) {
    auto it = typeToStringMap.find(type);
    if (it != typeToStringMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid product type");
}

/**
    Converts a string to its corresponding PRODUCT_TYPE.

    This function looks up the provided string in a map that associates each string 
    representation of a product type with the corresponding PRODUCT_TYPE. If the string 
    is found, the corresponding PRODUCT_TYPE is returned. If the string is not found, 
    an exception is thrown indicating that the provided product string is invalid.

    @param str The string to convert to a PRODUCT_TYPE.
    @return The corresponding PRODUCT_TYPE.
    @throws std::invalid_argument If the string is not found in the map.
*/
PRODUCT_TYPE Utils::stringToProduct(const std::string& str) {
    auto it = stringToTypeMap.find(str);
    if (it != stringToTypeMap.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid product string: " + str);
}

/**
    Splits a string into substrings based on a delimiter.

    This function divides the input string `s` into multiple substrings, each 
    occurring between instances of the specified `delimiter`. The substrings are 
    stored in a vector of strings. The function iterates through the string, finding 
    each occurrence of the delimiter and extracting the corresponding substring.

    @param s The string to be split. The input string is modified by this function.
    @param delimiter The delimiter used to split the string.
    @return A vector containing the substrings.
*/
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