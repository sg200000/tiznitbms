#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <unordered_map>
#include <sqlite3.h>
#include "db.hpp"

class Sqlite3DB : public DBManager {
private:
    sqlite3* db;
public:
    Sqlite3DB(std::string dbPath);
    /*bool requestData();*/
    bool insertData(std::string tableName, std::unordered_map<std::string,std::string> data);
    bool updateData(std::string tableName, std::string key, std::string value, 
                    std::string condKey, std::string condValue);
    bool deleteData(std::string tableName, std::string key, std::string value);
    ~Sqlite3DB();
};

Sqlite3DB::Sqlite3DB(std::string dbPath)
{
    int rc = sqlite3_open(dbPath.c_str(), &(this->db));
    if (rc) {
        std::cerr << sqlite3_errmsg(this->db);
    }
}

Sqlite3DB::~Sqlite3DB()
{
    sqlite3_close(this->db);
}

bool Sqlite3DB::deleteData(std::string tableName, std::string key, std::string value){
    std::string sql;
    int rc;
    char* errmsg;
    sql = "DELETE FROM "+tableName+" WHERE "+key+"='"+value+"'";
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Sqlite3DB::updateData(std::string tableName, std::string key, std::string value,
                            std::string condKey, std::string condValue){
    char* errmsg;
    std::string sql = "UPDATE "+tableName+" SET "+key+"='"+value+"' WHERE "+condKey+"='"+condValue+"'";
    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Sqlite3DB::insertData(std::string tableName, std::unordered_map<std::string,std::string> data){
    std::stringstream sqlBuilder;
    std::string sql;
    char* errmsg;
    /*std::string sql = std::format("INSERT INTO customers (firstName,lastName,email,phone,accountId,userName,password)\
        VALUES ('{}','{}','{}','{}','{}','{}','{}');",customer.getFirstName(),
                                        customer.getLastName(),
                                        customer.getEmail(),
                                        customer.getPhone(),
                                        accountId,
                                        userName,
                                        password);*/

    sqlBuilder << "INSERT INTO "+tableName+" (";
    for (auto iter = data.begin(); iter != data.end();){
        sqlBuilder << iter->first;
        if (++iter != data.end()){
            sqlBuilder << ",";
        }
    }
    sqlBuilder << ") VALUES (";
    for (auto iter = data.begin(); iter != data.end();){
        sqlBuilder << iter->second;
        if (++iter != data.end()){
            sqlBuilder << ",";
        }
    }
    sqlBuilder << ")";
    sql = sqlBuilder.str();

    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}