#pragma once

#include <string>

class DBManager_base
{
public:
    virtual bool requestData(std::string tableName, std::vector<std::string> columns, std::unordered_map<std::string, std::string> conditions, 
                             std::vector<std::vector<std::string>>* outData) = 0;
    virtual bool insertData(std::string tableName, std::unordered_map<std::string,std::string> data) = 0;
    virtual bool updateData(std::string tableName,
                           std::unordered_map<std::string,std::string> updates,
                           std::unordered_map<std::string,std::string> condition) = 0;
    virtual bool deleteData(std::string tableName, std::unordered_map<std::string,std::string> conditions) = 0;
    virtual ~DBManager_base() {}
};
