/*
 * Description : customer operations implementation
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "sqlite3db.hpp"
#include "customer.hpp"
#include <unordered_map>

Customer::Customer(const std::string& dbPath){
    this->db = std::unique_ptr<DBManager>(new Sqlite3DB(dbPath));
}

void Customer::signIn(const std::string& password){
    std::vector<std::vector<std::string>> outData;

    this->onlineState = this->db->requestData("customers",{"id","accountId"}, 
                                            {{"userName",this->userName},{"password",password}}, &outData);

    if (!this->onlineState){
        return;
    }

    this->id = stoi(outData[0][0]);
    this->account.id = stoi(outData[0][1]);

    outData.clear();
    bool rc = this->db->requestData("accounts",{"min","currency"}, {{"id",std::to_string(this->account.id)}}, &outData);
    if (!rc){
        std::cerr << "Error : Cannot fetch data" << std::endl;
        return;
    }

    this->account.min = std::stod(outData[0][0]);
    this->account.currency = outData[0][1];
}

Balance Customer::viewBalance(){
    bool rc;
    Balance balance;

    if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return balance;
    }
    if (!this->account.id){
        std::cerr << "you don't have associated account" << std::endl;
        return balance;
    }
    std::vector<std::vector<std::string>> outData;

    rc = this->db->requestData("accounts", {"balance","currency"}, {{"id", std::to_string(this->account.id)}}, &outData);

    if (!rc){
        std::cerr << "Cannot get account balance" << std::endl;
        return balance;
    }

    // Store balance value and currency
    balance.amount = std::stod(outData[0][0]);
    balance.currency = outData[0][1];
    this->account.currency = balance.currency;
    
    return balance;
}

bool Customer::submitCash(double amount){
    if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return false;
    }
    if (!this->account.id){
        std::cerr << "you don't have associated account" << std::endl;
        return false;
    }

    return this->db->updateData("accounts",{
        {"balance","balance+"+std::to_string(amount)}
    }, 
    {
        {"id",std::to_string(this->account.id)}
    });
}

bool Customer::withdrawCash(double amount){
   if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return false;
    }
    if (!this->account.id){
        std::cerr << "you don't have associated account" << std::endl;
        return false;
    }

    return this->db->updateData("accounts", {
        {"balance","balance-"+std::to_string(amount)}
    }, 
    {
        {"id",std::to_string(this->account.id)}
    }); 
}