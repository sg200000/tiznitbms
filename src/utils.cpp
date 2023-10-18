/*
 * Description : Utils implementation file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "utils.hpp"

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