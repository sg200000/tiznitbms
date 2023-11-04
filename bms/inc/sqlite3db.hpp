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
    bool execute(std::string sql, void* outData = nullptr) override;

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
private:
    sqlite3* db; // Pointer to sqlite3 database
    char* errMsg = nullptr;
};

