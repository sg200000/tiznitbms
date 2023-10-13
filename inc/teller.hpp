#include <iostream>
#include "db.hpp"
#include "person.hpp"

class Teller : public Person {
private:
    std::string userName;
    int id;
    std::unique_ptr<DBManager> db;
    bool onlineState = false;
public:
    Teller(std::string dbPath);
    ~Teller() {}
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
    void setOnlineState(bool onlineState){
        this->onlineState = onlineState;
    }
    bool getOnlineState(){
        return this->onlineState;
    }
};