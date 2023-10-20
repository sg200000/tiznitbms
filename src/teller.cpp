/*
 * Description : Teller operations implementation
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "teller.hpp"
#include "sqlite3db.hpp"

Teller::Teller(const std::string& dbPath) {
    this->db = std::unique_ptr<DBManager>(new Sqlite3DB(dbPath));
}

bool Teller::signIn(const std::string& password){
    // Declare data vector to get userName and password from database if login valid
    // Otherwise the outData will remain empty
    std::vector<std::vector<std::string>> outData;
    this->onlineState = this->db->requestData("tellers",{"id"}, 
                                            {{"userName",this->userName},{"password",password}}, &outData);

    // Return false if login is not valid
    if (!this->onlineState){
        return false;
    }

    // If the login is valid get the teller id
    this->id = stoi(outData[0][0]);

    return true;
}

bool Teller::registerNewCustomer(Person customer, const std::string& userName, const std::string& password, int accountId){
    /* Create an account in accounts (initialized balance = 0) */
    bool rc = this->db->insertData("accounts", {
        {"id",std::to_string(accountId)},
        {"balance","0.0"},
        {"min","0.0"}
    });
    if (!rc){
        std::cerr << "Cannot create account" << std::endl;
        return false;
    }

    /* Add a customer and associate created account */
    rc = this->db->insertData("customers",{
        {"firstName", customer.getFirstName()},
        {"lastName", customer.getLastName()},
        {"email", customer.getEmail()},
        {"phone", customer.getPhone()},
        {"accountId", std::to_string(accountId)},
        {"userName",userName},
        {"password",password}
    });

    if (!rc){
        std::cerr << "Cannot add customer" << std::endl;
        return false;
    }

    return true;
}

std::unordered_map<std::string,std::string> Teller::getCustomerInformation(const std::string& userName){
    std::unordered_map<std::string,std::string> customerInfo; // Parsed customer information
    std::vector<std::vector<std::string>> outData; // Raw returned data
    std::vector<std::string> columns = {"id","firstName","lastName","email","phone","accountId","userName"};

    // Request data to the database
    bool rc = this->db->requestData("customers", columns, {{"userName",userName}}, &outData);
    if (!rc){
        return customerInfo;
    }

    // Map data to columns
    for (int i=0;i<columns.size();i++){
        customerInfo.insert(std::make_pair(columns[i], outData[0][i]));
    }

    return customerInfo;
}

bool Teller::updateCustomerInformation(const std::string& userName, const std::string& key, const std::string& value){
    bool rc = this->db->updateData("customers", {{key, value}}, {{"userName", userName}});

    if (!rc){
        std::cerr << "couldn't update " << key << " with " << value << std::endl;
        return false;
    }
    return true;
}

bool Teller::deleteCustomer(const std::string& userName){
    // Guard if the user doesn't exists
    std::unordered_map<std::string,std::string> customerInfo = this->getCustomerInformation(userName);
    if (customerInfo.empty()){
        std::cerr << "The customer doesn't exist" << std::endl;
        return false;
    }

    // Delete the customer
    bool rc = this->db->deleteData("customers",{{"userName", userName}}); 

    if (!rc){
        std::cerr << "Couldn't delete the customer " << userName << std::endl;
        return false;
    }

    // Get the accountId and delete the account record
    int accountId = std::stoi(customerInfo["accountId"]);
    rc = this->db->deleteData("accounts",{{"id", std::to_string(accountId)}});

    if (!rc){
        std::cout << "Couldn' delete account number " << accountId << std::endl;
        return false;
    }

    return true;
}