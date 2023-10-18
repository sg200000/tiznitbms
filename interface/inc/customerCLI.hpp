/*
 * Description : The customer command-line interface header file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/


#pragma once

#include <iostream>
#include <memory>
#include "customerInterface.hpp"
#include "customer.hpp"

class customerCLI : public customerInterface {
public:
    /**
     * @brief Construct a new customerCLI object
     * 
     */
    customerCLI();
    
protected:
    /**
     * @brief The main user role for the customer role
     * 
     */
    void mainInterface() override;

    /**
     * @brief The login interface of the customers
     * 
     */
    void loginInterface() override;

    /**
     * @brief View customer balance 
     * 
     * @param currency The currency used
     */
    void viewBalanceInterface(const std::string& currency) override;

    /**
     * @brief Submit cash to customer account
     * 
     * @param currency the currency used
     */
    void submitCashInterface(const std::string& currency) override;

    /**
     * @brief Withdraw cash from customer account
     * 
     * @param currency The currency used
     */
    void withdrawCashInterface(const std::string& currency) override;
};