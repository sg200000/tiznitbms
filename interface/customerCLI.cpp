/*
 * Description : The implementation of customer command-line interface
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "customerCLI.hpp"

customerCLI::customerCLI(){
    // Bank database filepath (note that this version uses sqlite3)
    std::string dbPath = "C:/Users/saidg/source/tiznitbms/bank.db";

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
    do {
        this->printToStdout("Welcome to the customer interface. Please select the operation :");
        this->printToStdout("\t1 -> view your account balance");
        this->printToStdout("\t2 -> submit cash");
        this->printToStdout("\t3 -> withdraw cash");
        std::cin >> mode;
        switch(mode){
        case 1:
            viewBalanceInterface("dh");
            break;
        case 2:
            submitCashInterface("dh");
            break;
        case 3:
            withdrawCashInterface("dh");
            break;
        }
    }
    while (mode != 0);
}

void customerCLI::loginInterface(){
    // Read userName and password as a map
    data_mapper creds = this->readUserInput({"userName","password"});

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

inline void customerCLI::viewBalanceInterface(const std::string& currency){
    this->printToStdout("Balance : "+std::to_string(this->customer->viewBalance())+currency);
}

void customerCLI::submitCashInterface(const std::string& currency){
    // Read the amount of money to submit
    data_mapper cashData = this->readUserInput({"cash"});

    // Submit the amount to the customer account
    this->customer->submitCash(stoi(cashData["cash"]));
    this->printToStdout("You just submitted "+cashData["cash"]+currency);
}

void customerCLI::withdrawCashInterface(const std::string& currency){
    // Read the amount of money to withdraw
    data_mapper cashData = this->readUserInput({"cash"});

    // Withdraw the amount from the customer account
    this->customer->withdrawCash(stoi(cashData["cash"]));
    this->printToStdout("You just withdrawed "+cashData["cash"]+currency);
}