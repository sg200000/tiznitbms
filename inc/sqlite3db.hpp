/*
 * Description : sqlite3 database manager (see db.hpp for overriden methods)
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <sqlite3.h>
#include "db.hpp"

class Sqlite3DB : public DBManager {
public:
    Sqlite3DB(){}
    Sqlite3DB(const std::string& dbPath);
    bool requestData(const std::string& tableName, std::vector<std::string> columns, std::unordered_map<std::string, std::string> conditions, 
                     std::vector<std::vector<std::string>>* outData) override;
    bool insertData(const std::string& tableName, std::unordered_map<std::string,std::string> data) override;
    bool updateData(const std::string& tableName,
                    std::unordered_map<std::string,std::string> updates,
                    std::unordered_map<std::string,std::string> conditions) override;
    bool deleteData(const std::string& tableName, std::unordered_map<std::string,std::string> conditions) override;

    /**
     * @brief sqlite3 callback
     * 
     * @param outDataPtr Pointer to the data fetched by the callback
     * @param count The number of columns fetched
     * @param inData Rows feteched
     * @param columns Column fetched data
     * @return int return code
     */
    static int callback(void* outDataPtr, int count, char** inData, char** columns);

    /**
     * @brief Destroy the Sqlite3DB object
     * 
     */
    ~Sqlite3DB();

protected:
    std::unordered_map<std::string,sqlType> requestTableHeader(const std::string& tableName) override;
    /**
     * @brief Convert data maps to SQL adapted string
     * 
     * @param sqlData A map of data
     * @param sqlTable SQL map of table columns/columnType
     * @param sep Separator of serialized data
     * @return std::unordered_map<std::string,sqlType>  Serialized data
     */
    std::string prepareAndSerialize(std::unordered_map<std::string,std::string>& sqlData, std::unordered_map<std::string,sqlType> sqlTable, std::string sep = ",");
private:
    sqlite3* db; // Pointer to sqlite3 database
};

