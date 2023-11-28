/*
 * Description : sqlite3 database management implementation
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "sqlite3db.hpp"
#include "utils.hpp"

Sqlite3DB::Sqlite3DB(const std::string& dbPath)
{
    // Initialize sqlite3 database
    int rc = sqlite3_open(dbPath.c_str(), &(this->db));
    if (rc) {
        std::cerr << sqlite3_errmsg(this->db);
    }
}

Sqlite3DB::~Sqlite3DB()
{
    if (this->errMsg != nullptr){
        sqlite3_free(this->errMsg);
    }
    if (this->db != nullptr){
        sqlite3_close(this->db);
    }
}

bool Sqlite3DB::execute(std::string sql, void* outData){
    #ifdef _DEBUG
    std::cout << sql << std::endl;
    #endif
    
    // Guard the database is opened
    if (this->db == nullptr){
        std::cerr << "Error : Database is not opened" << std::endl;
        return false;
    }

    // Execute sql commands
    int rc = sqlite3_exec(this->db, sql.c_str(), &(Sqlite3DB::callback), outData, &(this->errMsg));
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << this->errMsg << std::endl;
        return false;
    }

    return true;
}

int Sqlite3DB::callback(void* outDataPtr, int count, char** inData, char** columns){
    // Guard if it is not a select statement
    if (outDataPtr == nullptr){
        return 0;
    }

    std::vector<std::vector<std::string>>* tempOutDataPtr = static_cast<std::vector<std::vector<std::string>>*>(outDataPtr);
    std::vector<std::string> row;

    // Push the row into outDataPtr vector
    for (int i=0;i<count;i++){
        row.push_back(inData[i]);
    }
    tempOutDataPtr->push_back(row);

    return 0;
}

std::unordered_map<std::string,sqlType> Sqlite3DB::requestTableHeader(const std::string& tableName){
    std::unordered_map<std::string,sqlType> tableHeader;
    std::vector<std::vector<std::string>> tableInfo;

    // request to get table information
    std::string sql = "SELECT name,type FROM pragma_table_info('"+tableName+"')";
    bool rc = this->execute(sql,&tableInfo);
    if (!rc){
        return tableHeader;
    }

    // add table column data to the map
    for (auto column : tableInfo){
        if (column[1] == "TEXT"){
            tableHeader.insert(std::make_pair(column[0],sqlType::TEXT));
        }
        else if (column[1] == "REAL"){
            tableHeader.insert(std::make_pair(column[0],sqlType::REAL));
        } 
        else if (column[1] == "INT"){
            tableHeader.insert(std::make_pair(column[0],sqlType::INT));
        }
        else {
            tableHeader.insert(std::make_pair(column[0],sqlType::UNKNOWN));
        }
    }

    return tableHeader;
}