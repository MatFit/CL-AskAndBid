#pragma once

#include "Bid.h"
#include "User.h"
#include "Product.h"

#include <fstream>
#include <iostream>
#include <sstream>

class Parser {
public:
  Parser();
  parseBids(std::string csvFile) {
    std::ifstream file(csvFile);
    if (!file) {
      throw std::runtime_error("Failed to open file, parser parseBids");
    }

    std::string line;
    vector<Bid> bids;

    while (std::getline(file, line)) {
      std::stringstream ss(line);
      std::string token;
      int counter = 0;

      std::string username;
      std::string password;
      PRODUCT_TYPE product_type;
      double bid_price;

      while (std::getline(ss, token, ',') {
        if (counter >= 4) throw std::runtime_error("Failed to parse file, parser parseBids");
        switch (counter) {
          case 0:
            username = token;
            break;
          case 1:
            password = token;
            break;
          case 2:
            product_type = product_type(token);
            break;
          case 3:
            bid_price = bid_price(token);
            break;
          default:
            throw std::runtime_error("Defualt case hit, parser parseBids");
            break;
        }
        counter++;
      }
      bids.push_back(Bid(username, password, product_type, bid_price));
      counter = 0;
    }
    
    return bids;
  }

private:

};
