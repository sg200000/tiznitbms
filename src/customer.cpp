#include "../inc/customer.hpp"
#include <cassert>
#include <unordered_map>

Customer::Customer(sqlite3* db, std::string userName){
    this->userName = userName;
    this->db = db;
}

bool Customer::signIn(){
    sqlite3_stmt* stmt;
    std::string password;
    std::string sql;
    std::cin >> password;
    int rc;

    sql = "SELECT id,accountId FROM customers WHERE userName='"+this->userName+"' AND password='"+password+"'";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        this->id = sqlite3_column_int(stmt, 0);
        this->accountId = sqlite3_column_int(stmt, 1);
        this->onlineState = true;
    }
    if (rc != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);

    return onlineState;
}

long Customer::viewBalance(){
    sqlite3_stmt *stmt;
    int balance;
    if (!onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return -1;
    }
    if (!this->accountId){
        std::cerr << "you don't have associated account" << std::endl;
    }

    std::string sql = "SELECT balance from accounts WHERE id="+std::to_string(this->accountId);
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        balance = sqlite3_column_int(stmt, 0);
    }
    if (rc != SQLITE_DONE){
        std::cout << "error : " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return balance;
}