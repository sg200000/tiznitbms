#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include "db.hpp"

enum class sqlType {
    TEXT,
    REAL,
    INT,
    UNKNOWN
};

class Sqlite3DB : public DBManager_base {
private:
    sqlite3* db;
public:
    Sqlite3DB(){}
    Sqlite3DB(std::string dbPath);
    bool requestData(std::string tableName, std::vector<std::string> columns, std::unordered_map<std::string, std::string> conditions, 
                     std::vector<std::vector<std::string>>* outData);
    bool insertData(std::string tableName, std::unordered_map<std::string,std::string> data);
    bool updateData(std::string tableName,
                    std::unordered_map<std::string,std::string> updates,
                    std::unordered_map<std::string,std::string> conditions);
    bool deleteData(std::string tableName, std::unordered_map<std::string,std::string> conditions);
    static int callback(void* outDataPtr, int count, char** inData, char** columns);
    ~Sqlite3DB();

protected:
    std::unordered_map<std::string,sqlType> requestTableHeader(std::string tableName);
    std::string prepareAndSerialize(std::unordered_map<std::string,std::string>& sqlData, std::unordered_map<std::string,sqlType> sqlTable, std::string sep = ",");
};

