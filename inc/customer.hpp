#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <sqlite3.h>
#include "person.hpp"

class Customer : public Person {
private:
    std::string userName;
    int id, accountId;
    sqlite3* db;
    bool onlineState = false;
public:
    Customer(sqlite3* db, std::string userName);
    bool signIn(std::string password);
    double viewBalance();
    bool submitCash(double amount);
    bool withdrawCash(double amount);
};