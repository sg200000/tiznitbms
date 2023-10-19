/*
 * Description : Utils implementation file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "utils.hpp"
#include <cctype>

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

bool utils::isDouble(const std::string& str) {
    try {
        std::stod(str);
        return true;
    } catch (const std::invalid_argument& e) {
        return false;
    }
}

int utils::choicePrompt(const std::vector<std::string>& choices){
    // Read mode as a ser input
    std::string input;
    int mode;
    for (int i = 0; i < choices.size(); i++){
        std::cout << "\t" << i+1 << " -> " << choices[i] << std::endl;
    }
    std::cin >> input;
    mode = utils::isNumeric(input) ? std::stoi(input) : -1; // if input is not a number mode is -1
    return mode;
}