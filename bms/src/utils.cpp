/*
 * Description : Utils implementation file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "utils.hpp"
#include <cctype>
#include <fstream>
#include <memory>
#include <filesystem>
#include <nlohmann/json.hpp>
#include "db.hpp"
#include "dbFactory.hpp"

std::string utils::serialize(std::unordered_map<std::string,std::string> map, std::string sep){
    std::stringstream serialized;
    for (auto iter = map.begin(); iter != map.end();){
        serialized << iter->first << "=" << iter->second;
        if (++iter != map.end()){
            serialized << sep;
        }
    }
    return serialized.str();
}

std::string utils::serialize(std::vector<std::string> vec, std::string sep){
    std::stringstream serialized;
    for (auto iter = vec.begin(); iter != vec.end();){
        serialized << *iter;
        if (++iter != vec.end()){
            serialized << sep;
        }
    }
    return serialized.str();
}

bool utils::isNumeric(const std::string& str) {
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}

int utils::choicePrompt(const std::vector<std::string>& choices){
    // Read mode as a user input
    std::string input;
    int mode;
    for (int i = 0; i < choices.size(); i++){
        std::cout << "\t" << i+1 << " -> " << choices[i] << std::endl;
    }
    std::cin >> input;
    mode = utils::isNumeric(input) ? std::stoi(input) : -1; // if input is not a number mode is -1
    return mode;
}

nlohmann::json utils::parseJsonFile(const std::filesystem::path& filePath){
    // Initlialize empty JSON object
    nlohmann::json jsonData = nlohmann::json::object();

    // Try opening file
    std::ifstream jsonFile(filePath);
    if (!jsonFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return jsonData;
    }

    // Parse the JSON data
    jsonFile >> jsonData;

    // Close the file
    jsonFile.close();

    return jsonData;
}

std::string utils::serialize(const std::filesystem::path filePath){
    std::string serialized;

    // try openeing the file
    std::ifstream file(filePath);

    // Guard if the file is not opened
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return serialized;
    }

    // Serialize line by line
    std::string line;
    while (std::getline(file, line)) {
        serialized += line + "\n";
    }
    file.close();

    return serialized;
}

void utils::saveToJsonFile(const std::filesystem::path filePath, nlohmann::json data){
    // Serialize and save the data to the file
    std::ofstream jsonFile(filePath);
    jsonFile << data.dump(4);  // The argument 4 is for pretty-printing the JSON
    jsonFile.close();
}

bool utils::initializeDb(std::string dbName, std::filesystem::path sqlPath){
    std::unique_ptr<DBManager> conn = DbFactory::createDb(DbFactory::SQLITE3, dbName);
    return conn->executeSqlFile(sqlPath);
}