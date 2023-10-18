/*
 * Description : Util functions header
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace utils {
    /**
     * @brief Serialize a map
     * 
     * @param map The map to serialize
     * @param sep key=values separator
     * @return std::string The serialized map
     */
    std::string serialize(std::unordered_map<std::string, std::string> map, std::string sep = ",");

    /**
     * @brief Serialize a vector of string
     * 
     * @param vec The vector to serialize
     * @param sep The separator of vector elements
     * @return std::string The serialized vector
     */
    std::string serialize(std::vector<std::string> vec, std::string sep = ",");
}