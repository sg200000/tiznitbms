#include "../inc/person.hpp"

Person::Person(std::string firstName, std::string lastName){
    this->firstName = firstName;
    this->lastName = lastName;
}

Person::Person(std::string firstName, std::string lastName, std::string email){
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
}

Person::Person(std::string firstName, std::string lastName, std::string email, std::string phone){
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

void Person::setFirstName(std::string firstName){
    this->firstName = firstName;
}

void Person::setLastName(std::string lastName){
    this->lastName = lastName;
}

void Person::setEmail(std::string email){
    this->email = email;
}

void Person::setPhone(std::string phone){
    this->phone = phone;
}
