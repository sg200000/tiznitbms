#include <iostream>
#include <sqlite3.h>
#include "inc/customer.hpp"

int mainCustomer(){
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("../bank.db", &db);

  if (rc) {
    std::cerr << sqlite3_errmsg(db);
    return 1;
  } 

  Customer customer(db, "saidg");
  bool signedIn = customer.signIn("hi123");

  if (signedIn){
    std::cout << "signIn success" << std::endl;
  }
  else {
    std::cout << "signIn failed" << std::endl;
  }

  std::cout << "initial balance : " << customer.viewBalance() << std::endl;
  customer.submitCash(1000);
  std::cout << "balance after submit : " << customer.viewBalance() << std::endl;
  customer.withdrawCash(500);
  std::cout << "balance after withdraw : " << customer.viewBalance() << std::endl;

  sqlite3_close(db);
  return 0;
}