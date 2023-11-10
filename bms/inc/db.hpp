/*
 * Description : Database manager abstract class header
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "utils.hpp"

// SQL types enumeration
enum class sqlType {
    TEXT,
    REAL,
    INT,
    UNKNOWN
};

class DBManager
{
public:
    /**
     * @brief Execute an SQL file
     * 
     * @param sqlFile The path to the SQL file
     * @return true if the file executed successfully
     * @return false otherwise
     */
    bool executeSqlFile(const std::filesystem::path sqlFile){
        // Get commands from SQL file
        std::string sqlCommands = utils::serialize(sqlFile);

        // Execute commands
        return this->execute(sqlCommands);

    }
    /**
     * @brief Execute an SQL command
     * 
     * @param sql SQL command
     * @param outData Pointer to output data if it is a select statement
     * @return true if the query executed successfully
     * @return false otherwise
     */
    virtual bool execute(std::string sqlCommands, void* outData = nullptr) = 0;

    /**
     * @brief Request data from the database
     * 
     * @param tableName The table containing the data
     * @param columns the columns to select 
     * @param conditions select conditions
     * @param outData Pointer to the map that will contain the data
     * @return true If the data fetched successfuly
     * @return false Otherwise
     */
    virtual bool requestData(const std::string& tableName, std::vector<std::string> columns, std::unordered_map<std::string, std::string> conditions, 
                             std::vector<std::vector<std::string>>* outData);

    /**
     * @brief Insert data to table
     * 
     * @param tableName The target insertion table 
     * @param data A map that to data that will be inserted
     * @return true If data inserted successfuly
     * @return false Otherwise
     */
    bool insertData(const std::string& tableName, std::unordered_map<std::string,std::string> data);

    /**
     * @brief Update fields of table records
     * 
     * @param tableName Target update table
     * @param updates A key/value map of new field updates
     * @param condition A key/value map of updates conditions
     * @return true if the table updated successfully
     * @return false Otherwise
     */
    bool updateData(const std::string& tableName,
                           std::unordered_map<std::string,std::string> updates,
                           std::unordered_map<std::string,std::string> condition);

    /**
     * @brief Delete records from a table
     * 
     * @param tableName Delete target table
     * @param conditions Conditions to delete records
     * @return true If records deleted successfully
     * @return false Otherwise
     */
    bool deleteData(const std::string& tableName, std::unordered_map<std::string,std::string> conditions);

    /**
     * @brief Destroy DBManager object
     * 
     */
    virtual ~DBManager() {}

protected:
    /**
     * @brief Get table column names and their types
     * 
     * @param tableName The target table name
     * @return std::unordered_map<std::string,sqlType> A map of column/columnType
     */
    virtual std::unordered_map<std::string,sqlType> requestTableHeader(const std::string& tableName) = 0;

    /**
     * @brief Convert data maps to SQL adapted string
     * 
     * @param sqlData A map of data
     * @param sqlTable SQL map of table columns/columnType
     * @param sep Separator of serialized data
     * @return std::unordered_map<std::string,sqlType>  Serialized data
     */
    std::string prepareAndSerialize(std::unordered_map<std::string,std::string>& sqlData, std::unordered_map<std::string,sqlType> sqlTable, std::string sep = ",");
};
