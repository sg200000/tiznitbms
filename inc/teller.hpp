#include <iostream>
#include <sqlite3.h>
#include "person.hpp"
#include "customer.hpp"

class Teller : public Person {
private:
    std::string userName, id;
    sqlite3* db;
    bool onlineState = false;
public:
    Teller(std::string dbPath, std::string userName);
    ~Teller();
    bool signIn(std::string password);
    bool registerNewCustomer(Person customer, std::string userName, std::string password, int accountId);
    std::unordered_map<std::string,std::string> getCustomerInformation(std::string userName);
    bool updateCustomerInformation(std::string userName, std::string key, std::string value);
    bool deleteCustomer(std::string userName);
    void setUserName(std::string userName){
        this->userName = userName;
    }
    std::string getUserName(){
        return this->userName;
    }
};