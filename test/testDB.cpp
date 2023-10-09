#include "../inc/sqlite3db.hpp"
#include <string>
#include <unordered_map>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

TEST_CASE("Test URID")
{
    Sqlite3DB db("../../bank.db");
    bool deleted = db.deleteData("accounts",{{"id","6336"}});
    CHECK(deleted == true);
    bool updated = db.updateData("accounts", {{"id","150"}},{{"id","104"}});
    CHECK(updated == true);

    std::unordered_map<std::string,std::string> data = {
        {"id", "3455606546500"},
        {"balance", "0"},
        {"min", "0"}
    };
    bool inserted = db.insertData("accounts", data);
    CHECK(inserted);

    std::vector<std::vector<std::string>> outData;
    std::vector<std::string> columns = {"id"};
    bool requested = db.requestData("accounts", columns, {{"balance", "0.0"}, {"min", "0.0"}}, &outData);
    CHECK(requested);
    for (auto row : outData){
        for (auto val : row){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}