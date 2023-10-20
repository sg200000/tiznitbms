/*
 * Description : The customer abstract interface header
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <memory>
#include "userInterface.hpp"
#include "customer.hpp"

class customerInterface : public UserInterface {
protected:
    /**
     * @brief View balance abstract interface
     * 
     * @param currency the currency used
     */
    virtual void viewBalanceInterface(const std::string& currency) = 0;

    /**
     * @brief Submit cash abstract interface
     * 
     * @param currency The currency used
     */
    virtual void submitCashInterface(const std::string& currency) = 0;

    /**
     * @brief Withdraw cash abstract interface
     * 
     * @param currency The currency used
     */
    virtual void withdrawCashInterface(const std::string& currency) = 0;

    /**
     * @brief The pointer to customer
     * 
     */
    std::unique_ptr<Customer> customer; 
    
public:
    ~customerInterface() {}
};