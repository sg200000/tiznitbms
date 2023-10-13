#pragma once

#include <iostream>
#include <memory>
#include "userInterface.hpp"
#include "teller.hpp"


class tellerInterface : public UserInterface {
public:
    virtual void registerNewCustomerInterface() = 0;
    virtual void updateCustomerInformationInterface() = 0;
    virtual void getCustomerInformationInterface() = 0;
    virtual void deleteCustomerInterface() = 0;
    ~tellerInterface() {}
protected:
    std::unique_ptr<Teller> teller;
};