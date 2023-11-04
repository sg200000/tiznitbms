/*
 * Description : Main command-line interface source
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <iostream>
#include <string>
#include <memory>
#include "utils.hpp"
#include "userInterface.hpp"
#include "customerCLI.hpp"
#include "tellerCLI.hpp"

void mainCLI(){
    // User interface declaration (polymorphic type)
    std::unique_ptr<UserInterface> interface;

    // The mode to use (customer or teller)
    int mode;
    std::cout << "Hello this is the bank management system please choose the mode :" << std::endl;
    // Read user input and instanciate the interface based on user input
    do {
        // Read mode as a user input
        mode = utils::choicePrompt({"Customer mode", "Teller mode", "Exit"});
        switch (mode){
        case 1:
            interface = std::unique_ptr<UserInterface>(new customerCLI());
            return;
        case 2:
            interface = std::unique_ptr<UserInterface>(new tellerCLI());
            return;
        case 3:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Unsupported command. Please enter a supported command : " << std::endl;
        }
    }
    while(mode != 3);
}