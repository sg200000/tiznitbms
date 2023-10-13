#include "inc/customerCLI.hpp"

customerCLI::customerCLI(){
    std::string dbPath = "C:/Users/saidg/source/tiznitbms/bank.db";
    this->customer = std::unique_ptr<Customer>(new Customer(dbPath));
    do {
        this->loginInterface();
    }
    while (!customer->getOnlineState());
    this->mainInterface();
}

void customerCLI::mainInterface(){
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
    data_mapper creds = this->readUserInput({"userName","password"});
    this->customer->setUserName(creds["userName"]);
    this->customer->signIn(creds["password"]);
    if (this->customer->getOnlineState()){
        this->printToStdout("login successful");
    }
    else {
        this->printToStdout("error : incorrect userName or password");
    }
}

void customerCLI::viewBalanceInterface(std::string currency){
    this->printToStdout("Balance : "+std::to_string(this->customer->viewBalance())+currency);
}

void customerCLI::submitCashInterface(std::string currency){
    data_mapper cashData = this->readUserInput({"cash"});
    this->customer->submitCash(stoi(cashData["cash"]));
    this->printToStdout("You just submitted "+cashData["cash"]+currency);
}

void customerCLI::withdrawCashInterface(std::string currency){
    data_mapper cashData = this->readUserInput({"cash"});
    this->customer->withdrawCash(stoi(cashData["cash"]));
    this->printToStdout("You just withdrawed "+cashData["cash"]+currency);
}