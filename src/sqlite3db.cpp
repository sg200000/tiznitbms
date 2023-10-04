#include "../inc/sqlite3db.hpp"
#include "../inc/utils.hpp"
#include <cassert>


Sqlite3DB::Sqlite3DB(std::string dbPath)
{
    int rc = sqlite3_open(dbPath.c_str(), &(this->db));
    if (rc) {
        std::cerr << sqlite3_errmsg(this->db);
    }
}

Sqlite3DB::~Sqlite3DB()
{
    sqlite3_close(this->db);
}

bool Sqlite3DB::deleteData(std::string tableName, std::string key, std::string value){
    std::string sql;
    int rc;
    char* errmsg;
    sql = "DELETE FROM "+tableName+" WHERE "+key+"='"+value+"'";
    rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Sqlite3DB::updateData(std::string tableName,
                           std::unordered_map<std::string,std::string> updates,
                           std::unordered_map<std::string,std::string> conditions){
    std::unordered_map<std::string, sqlType> tableHeader = resquestTableHeader(tableName);
    char* errmsg;
    std::stringstream sqlBuilder;
    sqlBuilder << "UPDATE " << tableName;
    sqlBuilder << " SET " << prepareAndSerialize(updates,tableHeader);
    sqlBuilder << " WHERE " << prepareAndSerialize(conditions, tableHeader);

    std::string sql = sqlBuilder.str();

    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Sqlite3DB::insertData(std::string tableName, std::unordered_map<std::string,std::string> data){
    std::stringstream sqlBuilder;
    std::string sql;
    char* errmsg;

    sqlBuilder << "INSERT INTO "+tableName+" (";
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
    sql = sqlBuilder.str();

    int rc = sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK){
        std::cerr << "error : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }
    return true;
}

bool Sqlite3DB::requestData(std::string tableName, std::vector<std::string> columns, std::unordered_map<std::string,std::string> conditions, std::vector<std::vector<std::string>>* outData){
    std::string sql;
    std::stringstream sqlBuilder;
    int rc;
    char* errmsg;
    sqlBuilder << "SELECT " << utils::serialize(columns);
    sqlBuilder << " FROM " << tableName << " WHERE ";
    for (auto iter = conditions.begin(); iter != conditions.end();){
        sqlBuilder << iter->first << "='" << iter->second << "'";
        if (++iter != conditions.end()){
            sqlBuilder << " AND ";
        }
    }
    sql = sqlBuilder.str();
    
    rc = sqlite3_exec(this->db, sql.c_str(), &(Sqlite3DB::callback), outData, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error " << rc << " : " << sqlite3_errmsg(this->db) << std::endl;
        return false;
    }

    if (outData->size() == 0){
        return false;
    }

    return true;
}

int Sqlite3DB::callback(void* outDataPtr, int count, char** inData, char** columns){
    std::vector<std::vector<std::string>>* tempOutDataPtr = static_cast<std::vector<std::vector<std::string>>*>(outDataPtr);
    std::vector<std::string> row;
    for (int i=0;i<count;i++){
        row.push_back(inData[i]);
    }
    tempOutDataPtr->push_back(row);
    return 0;
}

std::unordered_map<std::string,sqlType> Sqlite3DB::resquestTableHeader(std::string tableName){
    char * errmsg;
    std::unordered_map<std::string,sqlType> tableHeader;

    // request to get table information
    std::string sql = "SELECT name,type FROM pragma_table_info('"+tableName+"')";
    std::vector<std::vector<std::string>> tableInfo;

    int rc = sqlite3_exec(this->db, sql.c_str(), &(Sqlite3DB::callback), &tableInfo, &errmsg);
    
    if (rc != SQLITE_OK){
        std::cout << "error " << rc << " : " << sqlite3_errmsg(this->db) << std::endl;
        return tableHeader;
    }

    // add table column data to the map
    for (auto column : tableInfo){
        assert(column.size() == 2);
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

std::string Sqlite3DB::prepareAndSerialize(std::unordered_map<std::string,std::string>& sqlData, std::unordered_map<std::string,sqlType> sqlTable, std::string sep){
    for (auto sqlRow : sqlData){
        if (sqlTable[sqlRow.first] == sqlType::TEXT){
            sqlData[sqlRow.first] = "'"+sqlData[sqlRow.first]+"'";
        }
    }
    std::string serialized = utils::serialize(sqlData, sep);
    return serialized;
}