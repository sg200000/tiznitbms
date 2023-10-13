#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using data_mapper = std::unordered_map<std::string,std::string>;

class UserInterface {
public:
    std::unordered_map<std::string,std::string> readUserInput(std::vector<std::string> toRead) {
        std::unordered_map<std::string,std::string> userData;
        std::string temp;
        for (std::string key : toRead){
            printToStdout(key, " : ");
            std::cin >> temp;
            userData.insert(std::make_pair(key,temp));
        }
        return userData;
    }
    inline void printToStdout(std::string text, std::string sep = "\n") { std::cout << text << sep; }
    virtual void mainInterface() = 0;
    virtual void loginInterface() = 0;
    ~UserInterface() {}
};