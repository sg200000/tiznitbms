#pragma once

#include <iostream>
#include <memory>
#include "userInterface.hpp"

class tellerInterface : public UserInterface {
public:
    virtual void loginInterface() = 0;
    virtual void registerNewCustomerInterface() = 0;
    virtual void updateCustomerInformationInterface() = 0;
    virtual void getCustomerInformationInterface() = 0;
    virtual void deleteCustomerInterface() = 0;
    ~tellerInterface() {}
};