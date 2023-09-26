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
    char *zErrMsg = 0;
public:
    Customer(sqlite3* db, std::string userName);
    bool signIn();
    double viewBalance();
    bool submitCash(double amount);
    long withdrawCash(long amount);
};