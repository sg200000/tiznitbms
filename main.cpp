/*
 * Description : This is the main Bank management system interface
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <iostream>
#include <memory>
#include "userInterface.hpp"
#include "customerCLI.hpp"
#include "tellerCLI.hpp"

int main(){
  // User interface declaration (polymorphic type)
  std::unique_ptr<UserInterface> interface;

  // The mode to use (customer or teller)
  int mode;
  std::cout << "Hello this is the bank management system please choose the mode :" << std::endl;

  // Read mode as a ser input
  std::cout << "\t1 -> customer mode\n\t2 -> teller mode" << std::endl;
  std::cin >> mode;

  // Instanciate the interface based on user input
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