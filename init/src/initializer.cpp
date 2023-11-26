#include <iostream>
#include <fstream>
#include <sqlite3.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <memory>
#include "utils.hpp"
#include "db.hpp"
#include "dbFactory.hpp"

int initializer(int argc, char* argv[]) {
    const std::filesystem::path bankSql = "sql/bank.sql";
    const std::filesystem::path bankDb = "bank.db";
    
    if (!utils::initializeDb("tellers", bankSql)){
        std::cerr << "Cannot generate bank database" << std::endl;
        return -1;
    }

    nlohmann::json data = {
        {"db", "sqlite3"},
        {"bank", bankDb.string()},
    };

    // Specify the file path where you want to save the JSON data
    const std::filesystem::path filePath = "db.json";
    utils::saveToJsonFile(filePath, data);
    std::cout << "Bank database generated successfully." << std::endl;
    return 0;
}
