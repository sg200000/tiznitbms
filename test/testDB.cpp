#include "../inc/sqlite3db.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

TEST_CASE("Test URID")
{
    Sqlite3DB db("../../bank.db");
    bool deleted = db.deleteData("accounts","id","101");
    CHECK(deleted == true);
    bool updated = db.updateData("accounts", "id","130","id","103");
    CHECK(updated == true);
}