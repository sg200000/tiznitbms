#pragma once

#include <iostream>
#include <memory>
#include "customerInterface.hpp"
#include "customer.hpp"

class customerCLI : public customerInterface {
public:
    customerCLI();
    void mainInterface() override;
    void loginInterface() override;
    void viewBalanceInterface(std::string currency) override;
    void submitCashInterface(std::string currency) override;
    void withdrawCashInterface(std::string currency) override;
};