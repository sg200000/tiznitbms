#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <memory>
#include "utils.hpp"
#include "db.hpp"
#include "sqlite3db.hpp"

int initializer(int argc, char* argv[]) {
    std::string databaseFile = (argc > 1) ? argv[1] : "bank.db";
    const std::filesystem::path sqlFile = "sql/generate_db.sql";
    
    std::unique_ptr<DBManager> conn = std::unique_ptr<DBManager>(new Sqlite3DB(databaseFile));
    bool rc = conn->executeSqlFile(sqlFile);
    
    nlohmann::json data = {
        {"db", "sqlite3"},
        {"path", (std::filesystem::current_path() / databaseFile).string()}
    };

    // Specify the file path where you want to save the JSON data
    const std::filesystem::path filePath = std::filesystem::current_path() / "db.json";
    utils::saveToJsonFile(filePath, data);
    std::cout << "Bank database generated successfully." << std::endl;
    return 0;
}
