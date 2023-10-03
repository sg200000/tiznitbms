#include "../inc/customer.hpp"
#include <cassert>
#include <unordered_map>

bool Customer::signIn(std::string password){
    std::vector<std::vector<std::string>> outData;

    this->onlineState = this->db.requestData("customers",{"id","accountId"}, 
                                            {{"userName",this->userName},{"password",password}}, &outData);

    std::cout << outData.size() << std::endl;

    if (!this->onlineState){
        return false;
    }

    this->id = stoi(outData[0][0]);
    this->accountId = stoi(outData[0][1]);

    return true;
}

double Customer::viewBalance(){
    bool rc;
    if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return -1;
    }
    if (!this->accountId){
        std::cerr << "you don't have associated account" << std::endl;
        return -1;
    }
    std::vector<std::vector<std::string>> outData;

    rc = this->db.requestData("accounts", {"balance"}, {{"id", std::to_string(this->accountId)}}, &outData);

    if (!rc){
        std::cerr << "Cannot get account balance" << std::endl;
        return -1;
    }
    double balance = stod(outData[0][0]);

    return balance;
}

bool Customer::submitCash(double amount){
    if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return false;
    }
    if (!this->accountId){
        std::cerr << "you don't have associated account" << std::endl;
        return false;
    }

    bool rc = this->db.updateData("accounts", "balance", "balance+"+std::to_string(amount), "id", std::to_string(this->accountId));

    return rc;
}

bool Customer::withdrawCash(double amount){
   if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return false;
    }
    if (!this->accountId){
        std::cerr << "you don't have associated account" << std::endl;
        return false;
    }

    bool rc = this->db.updateData("accounts", "balance", "balance-"+std::to_string(amount), "id", std::to_string(this->accountId));

    return rc; 
}