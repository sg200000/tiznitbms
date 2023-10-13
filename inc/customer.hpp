#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>
#include "person.hpp"
#include "db.hpp"
class Customer : public Person {
private:
    std::string userName;
    int id, accountId;
    std::unique_ptr<DBManager> db;
    bool onlineState = false;
public:
    Customer(std::string dbPath);
    ~Customer(){};
    void signIn(std::string password);
    double viewBalance();
    bool submitCash(double amount);
    bool withdrawCash(double amount);
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