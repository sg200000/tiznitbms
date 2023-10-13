#pragma once

#include <iostream>
#include <memory>
#include "tellerInterface.hpp"

class tellerCLI : public tellerInterface {
public:
    tellerCLI();
    void mainInterface() override;
    void loginInterface() override;
    void registerNewCustomerInterface() override;
    void updateCustomerInformationInterface() override;
    void getCustomerInformationInterface() override;
    void deleteCustomerInterface() override;
};