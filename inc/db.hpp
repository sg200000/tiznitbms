#include <string>

class DBManager
{
public:
    DBManager(){};
/*    virtual bool requestData() = 0;
    virtual bool insertData() = 0;
    virtual bool updateDate() = 0;*/
    virtual bool deleteData(std::string tableName, std::string key, std::string value) = 0;
};
