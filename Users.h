#ifndef USER_H
#define USER_H
#include <string>
#include <ostream>
#include <iostream>

class User {
    public:
        User(long phone_no_, std::string username_, std::string address_, double account_balance_) : 
        phone_no_(phone_no_),
        username_(username_),
        address_(address_),
        account_balance_(account_balance_) {}

        virtual ~User();

        double getAccountBalance() const { return account_balance_; }
        virtual void updateAccountInformation() = 0; // Resolves undefined references
        virtual void history() = 0; // Resolves undefined references
        virtual void dashboard() = 0; // Resolves undefined references
    protected:
        long phone_no_;
        std::string username_;
        std::string address_;
        double account_balance_;

};




class Seller : public User {
    public:
        Seller(long phone_no_, std::string username_, std::string address_, double account_balance_) :
        User(phone_no_, username_, address_, account_balance_) {}

        void postProduct();
        void openBid();
        void closeBid();
        void updateAccountInformation() override;
        void history() override;
        void dashboard() override;



        friend std::ostream& operator<<(std::ostream& os, const Seller &Seller){
            os << "            | Username : " << Seller.username_ << std::endl;
            os << "Seller Info | Phone Number : " << Seller.phone_no_ << std::endl;
            os << "            | Address : " << Seller.address_ << std::endl;

            return os;
        }
    private:
        

};




class Buyer : public User {
    public:
    Buyer(long phone_no_, std::string username_, std::string address_, double account_balance_) :
    User(phone_no_, username_, address_, account_balance_) {}


        void findProductsForSale();
        void placeBid();
        void updateAccountInformation() override;
        void history() override;
        void dashboard() override;
        



        friend std::ostream& operator<<(std::ostream& os, const Buyer &Buyer){
            os << "            | Username : " << Buyer.username_ << std::endl;
            os << "Buyer Info  | Phone Number : " << Buyer.phone_no_ << std::endl;
            os << "            | Address : " << Buyer.address_ << std::endl;

            return os;
        }
    private:

};

#endif