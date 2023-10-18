/*
 * Description : The teller abstract interface abstract header file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#pragma once

#include <memory>
#include "userInterface.hpp"
#include "teller.hpp"


class tellerInterface : public UserInterface {
protected:
    /**
     * @brief Register new customer abstract interface
     * 
     */
    virtual void registerNewCustomerInterface() = 0;

    /**
     * @brief update customer information abstract interface
     * 
     */
    virtual void updateCustomerInformationInterface() = 0;

    /**
     * @brief Get the customer information abstract interface
     * 
     */
    virtual void getCustomerInformationInterface() = 0;

    /**
     * @brief Delete customer abstract inerface
     * 
     */
    virtual void deleteCustomerInterface() = 0;
    
    /**
     * @brief Teller operations pointer
     * 
     */
    std::unique_ptr<Teller> teller;

public:
    ~tellerInterface() {}
};