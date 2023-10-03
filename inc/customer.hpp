#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include "person.hpp"
#include "sqlite3db.hpp"

class Customer : public Person {
private:
    std::string userName;
    int id, accountId;
    Sqlite3DB db;
    bool onlineState = false;
public:
    Customer(std::string dbPath, std::string userName) : db(dbPath),userName(userName) {};
    ~Customer(){};
    bool signIn(std::string password);
    double viewBalance();
    bool submitCash(double amount);
    bool withdrawCash(double amount);
    void setUserName(std::string userName){
        this->userName = userName;
    }
    std::string getUserName(){
        return this->userName;
    }

};