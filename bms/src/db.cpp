/*
 * Description : Database manager abstract class source
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "db.hpp"
#include <sstream>

bool DBManager::deleteData(const std::string& tableName, std::unordered_map<std::string,std::string> conditions){
    // Guard if record does not exist
    std::vector<std::vector<std::string>> outData;
    if (!this->requestData(tableName,{},conditions,&outData)){
        std::cerr << "no record to be deleted" << std::endl;
        return false;
    }
    
    std::string sql;
    std::stringstream sqlBuilder;

    // Get column types
    std::unordered_map<std::string, sqlType> tableHeader = requestTableHeader(tableName);
    
    // Build SQL query with serialized data
    sqlBuilder << "DELETE FROM " << tableName;
    if (conditions.size() != 0){
        sqlBuilder << " WHERE " << prepareAndSerialize(conditions,tableHeader," AND ");
    }
    // stringify and execute the SQL query
    sql = sqlBuilder.str();
    return this->execute(sql);
}

bool DBManager::updateData(const std::string& tableName,
                           std::unordered_map<std::string,std::string> updates,
                           std::unordered_map<std::string,std::string> conditions){
    std::string sql;
    std::stringstream sqlBuilder;
    
    // Get column types
    std::unordered_map<std::string, sqlType> tableHeader = requestTableHeader(tableName);
    
    // Build SQL query with serialized data
    sqlBuilder << "UPDATE " << tableName;
    sqlBuilder << " SET " << prepareAndSerialize(updates,tableHeader);
    if (conditions.size() != 0){
        sqlBuilder << " WHERE " << prepareAndSerialize(conditions, tableHeader);
    }
    // stringify and execute the SQL query
    sql = sqlBuilder.str();
    return this->execute(sql);
}

bool DBManager::insertData(const std::string& tableName, std::unordered_map<std::string,std::string> data){
    std::string sql;
    std::stringstream sqlBuilder;

    // Build SQL query
    sqlBuilder << "INSERT INTO " << tableName << " (";
    for (auto iter = data.begin(); iter != data.end();){
        sqlBuilder << iter->first;
        if (++iter != data.end()){
            sqlBuilder << ",";
        }
    }
    sqlBuilder << ") VALUES (";
    for (auto iter = data.begin(); iter != data.end();){
        sqlBuilder << "'" << iter->second << "'";
        if (++iter != data.end()){
            sqlBuilder << ",";
        }
    }
    sqlBuilder << ")";

    // stringify and execute the SQL query
    sql = sqlBuilder.str();
    return this->execute(sql);
}

bool DBManager::requestData(const std::string& tableName, std::vector<std::string> columns, std::unordered_map<std::string,std::string> conditions, std::vector<std::vector<std::string>>* outData){
    std::string sql;
    bool rc;
    std::stringstream sqlBuilder;

    // Get column types
    std::unordered_map<std::string, sqlType> tableHeader = requestTableHeader(tableName);

    // Build SQL query with serialized data
    sqlBuilder << "SELECT " << (columns.size() != 0 ? utils::serialize(columns) : "*");
    sqlBuilder << " FROM " << tableName;
    if (conditions.size() != 0){
        sqlBuilder << " WHERE " << prepareAndSerialize(conditions,tableHeader," AND ");
    }
    
    // stringify and execute the SQL query
    sql = sqlBuilder.str();
    rc = this->execute(sql, outData);

    // Guard if the query is not executed successfulLY
    // OR if no data fetched return false
    if (!rc || outData->size() == 0){
        return false;
    }

    return true;
}

std::string DBManager::prepareAndSerialize(std::unordered_map<std::string,std::string>& sqlData, std::unordered_map<std::string,sqlType> sqlTable, std::string sep){
    // Add signle quote (') if the type of the column is text
    for (auto sqlRow : sqlData){
        if (sqlTable[sqlRow.first] == sqlType::TEXT){
            sqlData[sqlRow.first] = "'"+sqlData[sqlRow.first]+"'";
        }
    }

    // Serialize the data
    std::string serialized = utils::serialize(sqlData, sep);
    return serialized;
}
