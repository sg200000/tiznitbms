#include "../inc/customer.hpp"
#include <cassert>
#include <unordered_map>

void Customer::signIn(std::string password){
    std::vector<std::vector<std::string>> outData;

    this->onlineState = this->db.requestData("customers",{"id","accountId"}, 
                                            {{"userName",this->userName},{"password",password}}, &outData);

    if (!this->onlineState){
        return;
    }

    this->id = stoi(outData[0][0]);
    this->accountId = stoi(outData[0][1]);
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
    return stod(outData[0][0]);
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

    return this->db.updateData("accounts",{
        {"balance","balance+"+std::to_string(amount)}
    }, 
    {
        {"id",std::to_string(this->accountId)}
    });
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

    return this->db.updateData("accounts", {
        {"balance","balance-"+std::to_string(amount)}
    }, 
    {
        {"id",std::to_string(this->accountId)}
    }); 
}