#include <iostream>
#include <utility>
#include <sqlite3.h>
#include "main.hpp"
#include "inc/customer.hpp"


int main(){
  int mode;
  std::cout << "Hello this is the bank management system please choose the mode :" << std::endl;
  std::cout << "\t1 -> customer mode\n\t2 -> teller mode" << std::endl;
  std::cin >> mode;
  switch (mode){
    case 1:
      mainCustomer();
      break;
    case 2:
      mainTeller();
      break;
  }
  return 0;
}

std::pair<std::string,std::string> loginInterface(){
  std::string userName, password;
  std::cout << "User name : ";
  std::cin >> userName;
  std::cout << "password : ";
  std::cin >> password;
  return std::make_pair(userName, password);
}