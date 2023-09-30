#include <iostream>
#include <sqlite3.h>
#include "inc/customer.hpp"
#include "main.hpp"

void viewBalanceInterface(double balance, std::string currency){
  std::cout << "Balance : " << balance << currency << std::endl; 
}

void submitCashInterface(Customer& customer, std::string currency){
  int cash;
  std::cout << "Enter the amount of cash : ";
  std::cin >> cash;
  std::cout << std::endl;
  customer.submitCash(cash);
  std::cout << "You just submitted " << cash << currency << std::endl;
}

void withdrawCashInterface(Customer& customer, std::string currency){
  int cash;
  std::cout << "Enter the amount of cash : ";
  std::cin >> cash;
  std::cout << std::endl;
  customer.withdrawCash(cash);
  std::cout << "You just withdrawed " << cash << currency << std::endl;
}

int mainCustomer(){
  bool signedIn;
  
  std::pair<std::string,std::string> creds;
  Customer customer("../bank.db", creds.first);
  do {
    creds = loginInterface();
    customer.setUserName(creds.first);
    signedIn = customer.signIn(creds.second);
  }
  while (!signedIn);
  std::cout << "login successful" << std::endl;
  int mode;
  do {
    std::cout << "Welcome to the customer interface. Please select the operation :" << std::endl;
    std::cout << "\t1 -> view your account balance" << std::endl;
    std::cout << "\t2 -> submit cash" << std::endl;
    std::cout << "\t3 -> withdraw cash" << std::endl;
    std::cin >> mode;
    switch(mode){
      case 1:
        viewBalanceInterface(customer.viewBalance(), "dh");
        break;
      case 2:
        submitCashInterface(customer, "dh");
        break;
      case 3:
        withdrawCashInterface(customer, "dh");
        break;
    }
  }
  while (mode != 0);

  return 0;
}