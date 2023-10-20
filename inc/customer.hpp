/*
 * Description : Customer operations header file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "person.hpp"
#include "db.hpp"

class Customer : public Person {
public:
    /**
     * @brief Construct a new Customer object
     * 
     * @param dbPath The path of bank database
     */
    Customer(const std::string& dbPath);

    /**
     * @brief Destroy the Customer object
     * 
     */
    ~Customer(){};

    /**
     * @brief Sign in to customer account
     * 
     * @param password entered user password
     */
    void signIn(const std::string& password);

    /**
     * @brief get the actual user account balance
     * 
     * @return double The value of the balance
     */
    double viewBalance();

    /**
     * @brief Submit cash to user account
     * 
     * @param amount The amount to submit
     * @return true When the cash submitted successfuly
     * @return false Otherwise
     */
    bool submitCash(double amount);

    /**
     * @brief Withdraw cash from user account
     * 
     * @param amount The amount to withdraw
     * @return true If the amount withdrawed successfully
     * @return false Otherwise
     */
    bool withdrawCash(double amount);

    /**
     * @brief Set the customer user name 
     * 
     * @param userName The userName
     */
    void setUserName(const std::string& userName){
        this->userName = userName;
    }

    /**
     * @brief Get the customer user name
     * 
     * @return std::string 
     */
    const std::string& getUserName(){
        return this->userName;
    }

    /**
     * @brief Set the customer online state
     * 
     * @param onlineState whether the customer is online or not
     */
    void setOnlineState(bool onlineState){
        this->onlineState = onlineState;
    }

    /**
     * @brief Get the customer online state
     * 
     * @return true if the customer is online
     * @return false otherwise
     */
    bool getOnlineState(){
        return this->onlineState;
    }

private:
    std::string userName; // customer userName
    int id, accountId; // id and accountId are successively customer and account ids 
    std::unique_ptr<DBManager> db; // A pointer to the database
    bool onlineState = false; // the customer online state initialized to false
};