#include <string>

class DBManager
{
public:
    DBManager(){};
/*    virtual bool requestData() = 0;*/
    virtual bool insertData(std::string tableName, std::unordered_map<std::string,std::string> data) = 0;
    virtual bool updateData(std::string tableName, std::string key, std::string value, 
                            std::string condKey, std::string condValue) = 0;
    virtual bool deleteData(std::string tableName, std::string key, std::string value) = 0;
};
