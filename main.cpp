/*
 * Description : This is the main Bank management system interface
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <filesystem>
#include "initializer.hpp"
#include "mainCLI.hpp"

int main(int argc, char* argv[]){
  // initiaze database for the first time
  std::filesystem::path dbJson = "db.json";
  if (!std::filesystem::exists(dbJson)) {
    initializer(argc,argv);
  }

  // Run main interface
  mainCLI();
  
  return 0;
}