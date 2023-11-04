/*
 * Description : Person class implementation
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include "person.hpp"

Person::Person(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& phone){
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->phone = phone;
}

std::string Person::getFirstName(){
    return this->firstName;
}

std::string Person::getLastName(){
    return this->lastName;
}

std::string Person::getEmail(){
    return this->email;
}

std::string Person::getPhone(){
    return this->phone;
}

void Person::setFirstName(const std::string& firstName){
    this->firstName = firstName;
}

void Person::setLastName(const std::string& lastName){
    this->lastName = lastName;
}

void Person::setEmail(const std::string& email){
    this->email = email;
}

void Person::setPhone(const std::string& phone){
    this->phone = phone;
}
