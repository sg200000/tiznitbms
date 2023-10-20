/*
 * Description : Teller command-line interface implementation
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <iostream>
#include "tellerCLI.hpp"
#include "utils.hpp"
#include "account.hpp"

tellerCLI::tellerCLI() {
    std::string dbPath = "C:/Users/saidg/source/tiznitbms/bank.db";
    this->teller = std::unique_ptr<Teller>(new Teller(dbPath));
    do {
        this->loginInterface();
    }
    while (!this->teller->getOnlineState());
    this->mainInterface();
}

void tellerCLI::mainInterface(){
    int mode;
    this->printToStdout("Welcome to the teller interface. Please select the operation :");
    do {
        mode = utils::choicePrompt({"Register a new customer","Get customer information",
                                    "Update a customer information","Delete a customer", "Exit"});
        switch(mode){
            case 1:
                this->registerNewCustomerInterface();
                break;
            case 2:
                this->getCustomerInformationInterface();
                break;
            case 3:
                this->updateCustomerInformationInterface();
                break;
            case 4:
                this->deleteCustomerInterface();
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "unsupported command Please enter a supported command : " << std::endl;
        }
    }
    while (mode != 5);
}

void tellerCLI::loginInterface(){
    data_mapper<std::string> creds = this->readUserInput<std::string>({"userName","password"});
    this->teller->setUserName(creds["userName"]);
    this->teller->signIn(creds["password"]);
    if (this->teller->getOnlineState()){
        this->printToStdout("login successful");
    }
    else {
        this->printToStdout("error : incorrect userName or password");
    }
}

void tellerCLI::registerNewCustomerInterface(){
    Person p;
    Account account;
    data_mapper<std::string> newCustomer = this->readUserInput<std::string>({
        "First name",
        "Last name",
        "Email",
        "Phone",
        "User name",
        "Password",
        "Account id",
        "Initial balance",
        "Minimum",
        "Currency"
    });
    p.setFirstName(newCustomer["First name"]);
    p.setLastName(newCustomer["Last name"]);
    p.setEmail(newCustomer["Email"]);
    p.setPhone(newCustomer["Phone"]);

    account.id = std::stoi(newCustomer["Account id"]);
    account.balance = std::stoi(newCustomer["Initial balance"]);
    account.min = std::stoi(newCustomer["minimum"]);
    account.currency = std::stoi(newCustomer["Currency"]);
    
    this->teller->registerNewCustomer(p, newCustomer["User name"],newCustomer["Password"], account);
}

void tellerCLI::updateCustomerInformationInterface(){
    data_mapper<std::string> updates = this->readUserInput<std::string>({"userName","key","value"});
    this->teller->updateCustomerInformation(updates["userName"], updates["key"], updates["value"]);
}

void tellerCLI::getCustomerInformationInterface(){
    data_mapper<std::string> customerInfo;
    data_mapper<std::string> keyInfo = readUserInput<std::string>({"userName"});
    customerInfo = this->teller->getCustomerInformation(keyInfo["userName"]);
    for (std::pair<std::string,std::string> info : customerInfo){
        this->printToStdout(info.first+" : "+info.second);
    }
}

void tellerCLI::deleteCustomerInterface(){
    data_mapper<std::string> delKey = readUserInput<std::string>({"userName"});
    this->teller->deleteCustomer(delKey["userName"]);
}