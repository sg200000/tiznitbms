/*
 * Description : The interface abstract class used as a polymorphic type
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// This is an alias of data map used in various read data operations
template<typename Type>
using data_mapper = std::unordered_map<std::string,Type>;

class UserInterface {
protected:
    /**
     * @brief Read user input in a data map
     * 
     * @param toRead key data to read (vector of keys)
     * @return data_mapper A map of data (key, value)
     */
    template<typename T>
    data_mapper<T> readUserInput(std::vector<std::string> toRead) {
        std::unordered_map<std::string,T> userData;
        std::string rawInput;
        T validInput;
        bool state;

        // Read each requested value and insert
        for (std::string key : toRead){
            // Loop until a valid value read
            do {
                printToStdout(key, " : ");
                std::cin >> rawInput;
                std::istringstream ss(rawInput);
                state = (bool)(ss >> validInput);
                if (!state){
                    printToStdout("Invalid input");
                }
            }
            while(!state);
            userData.insert(std::make_pair(key,validInput));
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