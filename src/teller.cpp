#include "../inc/teller.hpp"
#include <sqlite3.h>
#include <format>

Teller::Teller(sqlite3* db, std::string userName){
    this->userName = userName;
    this->db = db;
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
    sqlite3_stmt* stmt;
    std::string sql;
    int rc;
    std::cout << "creating account" << std::endl;
    sql = std::format("INSERT INTO accounts (id,balance,min)\
            VALUES ('{}',0.0,0.0);",accountId);
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    
    /* Add a customer and associate created account */
    std::cout << "creating customer account" << std::endl;
    sql = std::format("INSERT INTO customers (firstName,lastName,email,phone,accountId,userName,password)\
        VALUES ('{}','{}','{}','{}','{}','{}','{}');",customer.getFirstName(),
                                        customer.getLastName(),
                                        customer.getEmail(),
                                        customer.getPhone(),
                                        accountId,
                                        userName,
                                        password);

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while ((rc = sqlite3_step(stmt)) != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    return true;
}