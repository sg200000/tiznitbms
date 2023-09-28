#include <iostream>
#include <sqlite3.h>
#include "inc/customer.hpp"

int mainCustomer(void);
int mainTeller(void);

int main(){
  int mode;
  std::cout << "Hello this is the bank management system please choose the mode :" << std::endl;
  std::cout << "\t1 -> customer mode\n\t2 -> teller mode" << std::endl;
  std::cin >> mode;
  switch (mode){
    case 1:
      mainCustomer();
    case 2:
      mainTeller();
  }
  return 0;
}