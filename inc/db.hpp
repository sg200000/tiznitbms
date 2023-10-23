/*
 * Description : Database manager abstract class
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

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
                             std::vector<std::vector<std::string>>* outData) = 0;

    /**
     * @brief Insert data to table
     * 
     * @param tableName The target insertion table 
     * @param data A map that to data that will be inserted
     * @return true If data inserted successfuly
     * @return false Otherwise
     */
    virtual bool insertData(const std::string& tableName, std::unordered_map<std::string,std::string> data) = 0;

    /**
     * @brief Update fields of table records
     * 
     * @param tableName Target update table
     * @param updates A key/value map of new field updates
     * @param condition A key/value map of updates conditions
     * @return true if the table updated successfully
     * @return false Otherwise
     */
    virtual bool updateData(const std::string& tableName,
                           std::unordered_map<std::string,std::string> updates,
                           std::unordered_map<std::string,std::string> condition) = 0;

    /**
     * @brief Delete records from a table
     * 
     * @param tableName Delete target table
     * @param conditions Conditions to delete records
     * @return true If records deleted successfully
     * @return false Otherwise
     */
    virtual bool deleteData(const std::string& tableName, std::unordered_map<std::string,std::string> conditions) = 0;

    /**
     * @brief Destroy the DBManager object
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
};
