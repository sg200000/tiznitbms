#pragma once

#include <iostream>
#include <memory>
#include "tellerInterface.hpp"

class tellerCLI : public tellerInterface {
public:
    tellerCLI() {
        std::string dbPath = "C:/Users/saidg/source/tiznitbms/bank.db";
        this->teller = std::unique_ptr<Teller>(new Teller(dbPath));
        do {
            this->loginInterface();
        }
        while (!this->teller->getOnlineState());
        this->mainInterface();
    }

    void mainInterface() override {
        int mode;
        do {
            this->printToStdout("Welcome to the teller interface. Please select the operation :");
            this->printToStdout("\t1 -> register a new customer");
            this->printToStdout("\t2 -> get customer information");
            this->printToStdout("\t3 -> update a customer information");
            this->printToStdout("\t4 -> delete a customer");
            std::cin >> mode;
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
            }
        }
        while (mode != 0);
    }

    void loginInterface() override {
        data_mapper creds = this->readUserInput({"userName","password"});
        this->teller->setUserName(creds["userName"]);
        this->teller->signIn(creds["password"]);
        if (this->teller->getOnlineState()){
            this->printToStdout("login successful");
        }
        else {
            this->printToStdout("error : incocrrect userName or password");
        }
    }

    void registerNewCustomerInterface() override {
        Person p;
        data_mapper newCustomer = this->readUserInput({
            "First name",
            "Last name",
            "Email",
            "Phone",
            "User name",
            "Password",
            "Account id"
        });
        p.setFirstName(newCustomer["First name"]);
        p.setLastName(newCustomer["Last name"]);
        p.setEmail(newCustomer["Email"]);
        p.setPhone(newCustomer["Phone"]);
        
        this->teller->registerNewCustomer(p, newCustomer["User name"], newCustomer["Password"], stoi(newCustomer["Account id"]));
    }

    void updateCustomerInformationInterface() override {
        data_mapper updates = this->readUserInput({"userName","key","value"});
        this->teller->updateCustomerInformation(updates["userName"], updates["key"], updates["value"]);
    }

    void getCustomerInformationInterface() override {
        data_mapper customerInfo;
        data_mapper keyInfo = readUserInput({"userName"});
        customerInfo = this->teller->getCustomerInformation(keyInfo["userName"]);
        for (std::pair<std::string,std::string> info : customerInfo){
            this->printToStdout(info.first+" : "+info.second);
        }
    }

    void deleteCustomerInterface() override {
        data_mapper delKey = readUserInput({"userName"});
        this->teller->deleteCustomer(delKey["userName"]);
    }
};