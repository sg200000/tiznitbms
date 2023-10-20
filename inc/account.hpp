/*
 * Description : This file contains DAO data structures
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/


#pragma once
#include <string>

struct Account {
    std::string currency;
    double balance;
    double min;
    int id;
};

struct Balance {
    double amount = -1;
    std::string currency;
    inline std::string serialize(){
        return std::to_string(amount)+currency;
    }
};