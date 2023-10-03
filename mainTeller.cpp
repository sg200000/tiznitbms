#include <iostream>
#include <string>
#include <sqlite3.h>
#include <unordered_map>
#include "inc/teller.hpp"
#include "main.hpp"

void registerNewCustomerInterface(Teller& teller){
  Person p;
  std::string userInput, userName, password;
  int accountId;

  std::cout << "First name : ";
  std::cin >> userInput;
  p.setFirstName(userInput);

  std::cout << "Last name : ";
  std::cin >> userInput;
  p.setLastName(userInput);

  std::cout << "Email : ";
  std::cin >> userInput;
  p.setEmail(userInput);

  std::cout << "Phone : ";
  std::cin >> userInput;
  p.setPhone(userInput);

  std::cout << "Username : ";
  std::cin >> userName;

  std::cout << "Password : ";
  std::cin >> password;

  std::cout << "accountId : ";
  std::cin >> accountId;
  
  teller.registerNewCustomer(p, userName, password, accountId);
}

void updateCustomerInformationInterface(Teller& teller){
  std::string userName, key, value;
  std::cout << "Enter the target userName : ";
  std::cin >> userName;
  std::cout << "Enter the information to update : ";
  std::cin >> key;
  std::cout << "Enter the new value : ";
  std::cin >> value;
  teller.updateCustomerInformation(userName, key, value);
}

void getCustomerInformationInterface(Teller& teller){
  std::unordered_map<std::string,std::string> customerInfo;
  std::string userName;
  std::cout << "Enter the userName : ";
  std::cin >> userName;
  customerInfo = teller.getCustomerInformation(userName);
  for (std::pair<std::string,std::string> info : customerInfo){
    std::cout << info.first << " : " << info.second << std::endl;
  }
}

void deleteCustomerInterface(Teller& teller){
  std::string userName;
  std::cout << "Enter the customer userName to delete : ";
  std::cin >> userName;
  teller.deleteCustomer(userName);
}

int mainTeller(){
  bool signedIn;

  std::pair<std::string,std::string> creds;
  Teller teller("../bank.db", creds.first);
  do {
    creds = loginInterface();
    teller.setUserName(creds.first);
    signedIn = teller.signIn(creds.second);
  }
  while (!signedIn);
  std::cout << "login successful" << std::endl;
  int mode;
  do {
    std::cout << "Welcome to the teller interface. Please select the operation :" << std::endl;
    std::cout << "\t1 -> register a new customer" << std::endl;
    std::cout << "\t2 -> get customer information" << std::endl;
    std::cout << "\t3 -> update a customer information" << std::endl;
    std::cout << "\t4 -> delete a customer" << std::endl;
    std::cin >> mode;
    switch(mode){
      case 1:
        registerNewCustomerInterface(teller);
        break;
      case 2:
        getCustomerInformationInterface(teller);
        break;
      case 3:
        updateCustomerInformationInterface(teller);
        break;
      case 4:
        deleteCustomerInterface(teller);
        break;
    }
  }
  while (mode != 0);
  
  return 0;
}