/*
 * Description : This is file the database factory declaration
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <string>
#include <memory>
#include "db.hpp"
#include "sqlite3db.hpp"

class DbFactory {
public:
    /**
     * @brief Database supported types enumeration
     * 
     */
    enum dbType {
        SQLITE3
    };
    
    /**
     * @brief Create a Database object
     * 
     * @param db database supported type
     * @param dbName database name
     * @return std::unique_ptr<DBManager> a pointer to database initialized object
     */
    static std::unique_ptr<DBManager> createDb(dbType db, std::string dbName){
        if (db == SQLITE3){
            return std::unique_ptr<DBManager>(new Sqlite3DB("bank.db"));
        }
        return std::unique_ptr<DBManager>(nullptr);
    }
};