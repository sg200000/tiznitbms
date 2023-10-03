#pragma once

#include <string>

class DBManager_base
{
public:
    DBManager_base(){};
    virtual bool requestData(std::string tableName, std::vector<std::string> columns, std::unordered_map<std::string, std::string> conditions, 
                             std::vector<std::vector<std::string>>* outData) = 0;
    virtual bool insertData(std::string tableName, std::unordered_map<std::string,std::string> data) = 0;
    virtual bool updateData(std::string tableName, std::string key, std::string value, 
                            std::string condKey, std::string condValue) = 0;
    virtual bool deleteData(std::string tableName, std::string key, std::string value) = 0;
};
