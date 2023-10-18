/*
 * Description : Teller command line interface header file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <iostream>
#include <memory>
#include "tellerInterface.hpp"

class tellerCLI : public tellerInterface {
public:
    /**
     * @brief Construct a new tellerCLI object
     * 
     */
    tellerCLI();

protected:

    /**
     * @brief The main teller interface
     * 
     */
    void mainInterface() override;

    /**
     * @brief The login interface of tellers
     * 
     */
    void loginInterface() override;

    /**
     * @brief Register new customers
     * 
     */
    void registerNewCustomerInterface() override;

    /**
     * @brief  Update customer information
     * 
     */
    void updateCustomerInformationInterface() override;

    /**
     * @brief Get customer information
     * 
     */
    void getCustomerInformationInterface() override;

    /**
     * @brief Delete customer
     * 
     */
    void deleteCustomerInterface() override;
};