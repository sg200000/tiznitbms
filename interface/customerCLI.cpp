/*
 * Description : The implementation of customer command-line interface
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "customerCLI.hpp"
#include "utils.hpp"
#include <nlohmann/json.hpp>

customerCLI::customerCLI(){
    // Get the database path from db.json
    nlohmann::json db_json = utils::parseJsonFile("C:/Users/saidg/source/tiznitbms/db.json");
    if (db_json.empty()){
        std::cerr << "Cannot parse db.json";
        return;
    }
    std::string dbPath = db_json["path"];

    // initialize the customer
    this->customer = std::unique_ptr<Customer>(new Customer(dbPath));

    // try login
    do {
        this->loginInterface();
    }
    while (!customer->getOnlineState());

    // When the login is done run the main customer interface
    this->mainInterface();
}

void customerCLI::mainInterface(){
    // Print the guide and select the operation
    int mode;
    this->printToStdout("Welcome to the customer interface. Please select the operation :");
    do {
        mode = utils::choicePrompt({"View your account balance","Submit cash","Withdraw cash","Exit"});
        switch(mode){
        case 1:
            viewBalanceInterface();
            break;
        case 2:
            submitCashInterface();
            break;
        case 3:
            withdrawCashInterface();
            break;
        case 4:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "unsupported command Please enter a supported command : " << std::endl;
        }
    }
    while (mode != 4);
}

void customerCLI::loginInterface(){
    // Read userName and password as a map
    data_mapper<std::string> creds = this->readUserInput<std::string>({"userName","password"});

    // Set the userName to the customer an try signing in 
    this->customer->setUserName(creds["userName"]);
    this->customer->signIn(creds["password"]);

    // Print login state to the user
    if (this->customer->getOnlineState()){
        this->printToStdout("Login successful");
    }
    else {
        this->printToStdout("Error : incorrect userName or password");
    }
}

void customerCLI::viewBalanceInterface(){
    Balance balance = this->customer->viewBalance();
    this->printToStdout("Balance : "+balance.serialize());
}

void customerCLI::submitCashInterface(){
    data_mapper<double> cashData;

    // Read the amount of money to submit
    cashData = this->readUserInput<double>({"cash"});

    // Submit the amount to the customer account
    this->customer->submitCash(cashData["cash"]);
    this->printToStdout("You just submitted "+std::to_string(cashData["cash"])+this->customer->getAccount().currency);
}

void customerCLI::withdrawCashInterface(){
    // Read the amount of money to withdraw
    data_mapper<double> cashData;
    cashData = this->readUserInput<double>({"cash"});

    // Withdraw the amount from the customer account
    this->customer->withdrawCash(cashData["cash"]);
    this->printToStdout("You just withdrawed "+std::to_string(cashData["cash"])+this->customer->getAccount().currency);
}