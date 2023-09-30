#include "../inc/teller.hpp"
#include <sqlite3.h>
#include <format>
#include <sstream>

Teller::Teller(std::string dbPath, std::string userName){
    int rc = sqlite3_open(dbPath.c_str(), &(this->db));
    if (rc) {
        std::cerr << sqlite3_errmsg(this->db);
        return;
    }
    this->userName = userName;
}

Teller::~Teller(){
    sqlite3_close(this->db);
}

bool Teller::signIn(std::string password){
    sqlite3_stmt* stmt;
    std::string sql;
    int rc;

    sql = "SELECT id FROM tellers WHERE userName='"+this->userName+"' AND password='"+password+"'";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        this->id = sqlite3_column_int(stmt, 0);
        this->onlineState = true;
    }
    if (rc != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);

    return onlineState;
}

bool Teller::registerNewCustomer(Person customer, std::string userName, std::string password, int accountId){
    /* Create an account in accounts (initialized balance = 0) */
    std::string sql;
    int rc;

    sql = std::format("INSERT INTO accounts (id,balance,min)\
            VALUES ('{}',0.0,0.0);",accountId);
    char* errmsg;
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    
    /* Add a customer and associate created account */
    sql = std::format("INSERT INTO customers (firstName,lastName,email,phone,accountId,userName,password)\
        VALUES ('{}','{}','{}','{}','{}','{}','{}');",customer.getFirstName(),
                                        customer.getLastName(),
                                        customer.getEmail(),
                                        customer.getPhone(),
                                        accountId,
                                        userName,
                                        password);

    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    return true;
}

std::unordered_map<std::string,std::string> Teller::getCustomerInformation(std::string userName){
    std::unordered_map<std::string,std::string> customerInfo;
    sqlite3_stmt* stmt;
    std::string sql;
    int rc;

    sql = "SELECT * FROM customers WHERE userName='"+userName+"';";
    rc = sqlite3_prepare_v2(this->db, sql.c_str(),-1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return customerInfo;
    }

    int num_columns = sqlite3_column_count(stmt);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        std::string column;
        std::string data;
        for (int i=0;i<num_columns;i++){
            column = sqlite3_column_name(stmt, i);
            if (column == "password"){
                continue;
            }
            if (column == "id" || column == "accountId"){
                data = std::to_string(sqlite3_column_int(stmt, i));
            }
            else {
                data = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            }
            customerInfo.insert(std::make_pair(column, data));
        }
    }
    if (rc != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return customerInfo;
}

bool Teller::updateCustomerInformation(std::string userName, std::string key, std::string value){
    std::string sql;
    int rc;
    char *errmsg;

    sql = "UPDATE customers SET "+key+"='"+value+"' WHERE userName='"+userName+"'";
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Teller::deleteCustomer(std::string userName){
    std::string sql;
    int rc;
    char *errmsg;

    int accountId = std::stoi(this->getCustomerInformation(userName)["accountId"]);

    sql = "DELETE FROM customers WHERE userName='"+userName+"'";
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    sql = "DELETE FROM accounts WHERE id='"+std::to_string(accountId)+"'";
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    return true;
}