#include "../inc/teller.hpp"
#include "../inc/sqlite3db.hpp"

Teller::Teller(std::string dbPath) {
    this->db = std::unique_ptr<DBManager>(new Sqlite3DB(dbPath));
}

bool Teller::signIn(std::string password){
    std::vector<std::vector<std::string>> outData;

    this->onlineState = this->db->requestData("tellers",{"id"}, 
                                            {{"userName",this->userName},{"password",password}}, &outData);

    if (!this->onlineState){
        return false;
    }

    this->id = stoi(outData[0][0]);

    return true;
}

bool Teller::registerNewCustomer(Person customer, std::string userName, std::string password, int accountId){
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

std::unordered_map<std::string,std::string> Teller::getCustomerInformation(std::string userName){
    std::unordered_map<std::string,std::string> customerInfo;
    std::vector<std::vector<std::string>> outData;
    std::vector<std::string> columns = {"id","firstName","lastName","email","phone","accountId","userName"};
    bool rc = this->db->requestData("customers", columns, {{"userName",userName}}, &outData);
    if (!rc){
        return customerInfo;
    }
    for (int i=0;i<columns.size();i++){
        customerInfo.insert(std::make_pair(columns[i], outData[0][i]));
    }
    return customerInfo;
}

bool Teller::updateCustomerInformation(std::string userName, std::string key, std::string value){
    bool rc = this->db->updateData("customers", {{key, value}}, {{"userName", userName}});

    if (!rc){
        std::cerr << "couldn't update " << key << " with " << value << std::endl;
        return false;
    }
    return true;
}

bool Teller::deleteCustomer(std::string userName){
    int accountId = std::stoi(this->getCustomerInformation(userName)["accountId"]);
    
    bool rc = this->db->deleteData("customers",{{"userName", userName}});
    
    if (!rc){
        std::cerr << "Couldn't delete the customer " << userName << std::endl;
        return false;
    }

    rc = this->db->deleteData("accounts",{{"id", std::to_string(accountId)}});
    
    if (!rc){
        std::cout << "Couldn' delete account number " << accountId << std::endl;
        return false;
    }

    return true;
}