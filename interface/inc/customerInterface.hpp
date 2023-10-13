#pragma once

#include <iostream>
#include <memory>
#include "userInterface.hpp"
#include "customer.hpp"

class customerInterface : public UserInterface {
public:
    virtual void viewBalanceInterface(std::string currency) = 0;
    virtual void submitCashInterface(std::string currency) = 0;
    virtual void withdrawCashInterface(std::string currency) = 0;
    ~customerInterface() {}
protected:
    std::unique_ptr<Customer> customer;
};