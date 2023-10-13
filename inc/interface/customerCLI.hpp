#pragma once

#include <iostream>
#include <memory>
#include "customerInterface.hpp"
#include "customer.hpp"

class customerCLI : public customerInterface {
public:
    customerCLI() {
        std::string dbPath = "C:/Users/saidg/source/tiznitbms/bank.db";
        this->customer = std::unique_ptr<Customer>(new Customer(dbPath));
        do {
            this->loginInterface();
        }
        while (!customer->getOnlineState());
        this->mainInterface();
    }

    void mainInterface() override {
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

    void loginInterface() override {
        data_mapper creds = this->readUserInput({"userName","password"});
        this->customer->setUserName(creds["userName"]);
        this->customer->signIn(creds["password"]);
        if (this->customer->getOnlineState()){
            this->printToStdout("login successful");
        }
        else {
            this->printToStdout("error : incocrrect userName or password");
        }
    }

    void viewBalanceInterface(std::string currency) override {
        this->printToStdout("Balance : "+std::to_string(this->customer->viewBalance())+currency);
    }

    void submitCashInterface(std::string currency) override {
        data_mapper cashData = this->readUserInput({"cash"});
        this->customer->submitCash(stoi(cashData["cash"]));
        this->printToStdout("You just submitted "+cashData["cash"]+currency);
    }

    void withdrawCashInterface(std::string currency) override {
        data_mapper cashData = this->readUserInput({"cash"});
        this->customer->withdrawCash(stoi(cashData["cash"]));
        this->printToStdout("You just withdrawed "+cashData["cash"]+currency);
    }
};