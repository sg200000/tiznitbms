#include <iostream>
#include <sqlite3.h>
#include "inc/teller.hpp"

int mainTeller(){
  sqlite3 *db;
  int rc;

  rc = sqlite3_open("../bank.db", &db);

  if (rc) {
    std::cerr << sqlite3_errmsg(db);
    return 1;
  } 

  Teller teller(db, "ahmedg");
  bool signedIn = teller.signIn("ahmed123");

  if (signedIn){
    std::cout << "signIn success" << std::endl;
  }
  else {
    std::cout << "signIn failed" << std::endl;
  }
  Person p("Ali", "Guouihaj","aliguouihaj@gmail.com", "0754565755");

  teller.registerNewCustomer(p, "alig", "ali123", 500);
  
  sqlite3_close(db);
  return 0;
}