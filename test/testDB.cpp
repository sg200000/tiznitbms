#include <string>
#include <unordered_map>
#include "../inc/sqlite3db.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

TEST_CASE("Test URID")
{
    Sqlite3DB db("../../bank.db");
    bool deleted = db.deleteData("accounts","id","6336");
    CHECK(deleted == true);
    bool updated = db.updateData("accounts", "id","150","id","104");
    CHECK(updated == true);

    std::unordered_map<std::string,std::string> data = {
        {"id", "365"},
        {"balance", "455"},
        {"min", "0"}
    };
    bool inserted = db.insertData("accounts", data);
    CHECK(inserted);
}