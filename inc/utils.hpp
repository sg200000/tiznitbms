#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace utils {
    std::string serialize(std::unordered_map<std::string, std::string> map, std::string sep = ",");
    std::string serialize(std::vector<std::string> vec, std::string sep = ",");
}