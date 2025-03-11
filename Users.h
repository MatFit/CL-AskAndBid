#ifndef USER_H
#define USER_H
#include <string>
#include <ostream>
#include <iostream>
#include <vector>

class User {
    public:
        User(std::string phone_no_, std::string username_, std::string address_, double account_balance_)
        :   phone_no_(phone_no_),
            username_(username_),
            address_(address_),
            account_balance_(account_balance_) {}

        virtual ~User();

        
        virtual void history() = 0; // Resolves undefined references
        virtual void dashboard() = 0; // Resolves undefined references

        void updateAccountInformation();

        double getAccountBalance() const { return account_balance_; }
        void setPhoneNumber(std::string phone_no_);
        void setAddress(std::string address_);

    protected:
        std::string phone_no_;
        std::string username_;
        std::string address_;
        double account_balance_;


    friend std::ostream& operator<<(std::ostream& os, const User &User){
        os << "              | Username : " << User.username_ << std::endl;
        os << "   User Info  | Phone Number : " << User.phone_no_ << std::endl;
        os << "              | Address : " << User.address_ << std::endl;

        return os;
    }
};




class Seller : public User {
    public:
        Seller(std::string phone_no_, std::string username_, std::string address_, double account_balance_)
        : User(phone_no_, username_, address_, account_balance_) {}

        void productOverview(); // Sold or yet to be sold
        void openBidforProduct();
        void closeBidforProduct();
        void history() override;
        void dashboard() override;


 
        friend std::ostream& operator<<(std::ostream& os, const Seller &Seller){
            os << "              | Username : " << Seller.username_ << std::endl;
            os << "  Seller Info | Phone Number : " << Seller.phone_no_ << std::endl;
            os << "              | Address : " << Seller.address_ << std::endl;

            return os;
        }
    private:
        std::vector<int*> activeProductsforSale; // Temp datatype, will be Products
        

};




class Buyer : public User {
    public:
    Buyer(std::string phone_no_, std::string username_, std::string address_, double account_balance_)
    : User(phone_no_, username_, address_, account_balance_) {}


        void findProductsForSale(); // Depends if product is open or closed
        void placeBidforProduct();
        void history() override;
        void dashboard() override;
        



        friend std::ostream& operator<<(std::ostream& os, const Buyer &Buyer){
            os << "              | Username : " << Buyer.username_ << std::endl;
            os << "  Buyer Info  | Phone Number : " << Buyer.phone_no_ << std::endl;
            os << "              | Address : " << Buyer.address_ << std::endl;

            return os;
        }
    private:
        std::vector<int*> activeBids; // temp rn, will be Bids
};

#endif