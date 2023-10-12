#include <iostream>
#include <utility>
#include <memory>
#include <sqlite3.h>
#include "inc/interface/userInterface.hpp"
#include "inc/interface/customerCLI.hpp"
#include "inc/interface/tellerCLI.hpp"

int main(){
  std::unique_ptr<UserInterface> interface;
  int mode;
  std::cout << "Hello this is the bank management system please choose the mode :" << std::endl;
  std::cout << "\t1 -> customer mode\n\t2 -> teller mode" << std::endl;
  std::cin >> mode;
  switch (mode){
    case 1:
      interface = std::unique_ptr<UserInterface>(new customerCLI());
      break;
    case 2:
      interface = std::unique_ptr<UserInterface>(new tellerCLI());
      break;
  }
  return 0;
}