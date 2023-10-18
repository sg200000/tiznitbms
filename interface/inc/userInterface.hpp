/*
 * Description : The interface abstract class used as a polymorphic type
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// This is an alias of data map used in various read data operations
using data_mapper = std::unordered_map<std::string,std::string>;

class UserInterface {
protected:
    /**
     * @brief Read user input in a data map
     * 
     * @param toRead key data to read (vector of keys)
     * @return data_mapper A map of data (key, value)
     */
    data_mapper readUserInput(std::vector<std::string> toRead) {
        std::unordered_map<std::string,std::string> userData;
        std::string temp;
        for (std::string key : toRead){
            printToStdout(key, " : ");
            std::cin >> temp;
            userData.insert(std::make_pair(key,temp));
        }
        return userData;
    }

    /**
     * @brief Wrapper of print to stdout
     * 
     * @param text Message to print
     * @param sep separator at the end of the text
     */
    inline void printToStdout(std::string text, std::string sep = "\n") { std::cout << text << sep; }

    /**
     * @brief Main interface abstract method
     * 
     */
    virtual void mainInterface() = 0;

    /**
     * @brief Login interface abstract method
     * 
     */
    virtual void loginInterface() = 0;

public:
    virtual ~UserInterface() {}
};