#include <iostream>
#include <string>
#include <sqlite3.h>
#include "db.hpp"

class Sqlite3DB : public DBManager {
private:
    sqlite3* db;
public:
    Sqlite3DB(std::string dbPath);
    /*bool requestData();
    bool insertData();*/
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