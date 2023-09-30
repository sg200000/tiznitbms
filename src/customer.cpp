#include "../inc/customer.hpp"
#include <cassert>
#include <unordered_map>

Customer::Customer(std::string dbPath, std::string userName){
    int rc = sqlite3_open(dbPath.c_str(), &(this->db));
    if (rc) {
        std::cerr << sqlite3_errmsg(this->db);
        return;
    }
    this->userName = userName;
}

Customer::~Customer(){
    sqlite3_close(this->db);
}
bool Customer::signIn(std::string password){
    sqlite3_stmt* stmt;
    std::string sql;
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

double Customer::viewBalance(){
    sqlite3_stmt *stmt;
    double balance;
    if (!this->onlineState){
        std::cerr << "you are not signed in" << std::endl;
        return -1;
    }
    if (!this->accountId){
        std::cerr << "you don't have associated account" << std::endl;
        return -1;
    }

    std::string sql = "SELECT balance from accounts WHERE id="+std::to_string(this->accountId);
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(db) << std::endl;
        return -1;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
        balance = sqlite3_column_int(stmt, 0);
    }
    if (rc != SQLITE_DONE){
        std::cerr << "error : " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
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
    
    std::string sql = "UPDATE accounts SET balance=balance+"+std::to_string(amount)+" WHERE id="+std::to_string(this->accountId);
    char* errmsg;
    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    return true;
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
    std::string sql = "UPDATE accounts SET balance=balance-"+std::to_string(amount)+" WHERE id="+std::to_string(this->accountId);
    char* errmsg;
    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    return true; 
}