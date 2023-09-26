#include <iostream>
#include <string>

#ifndef PERSON_H
#define PERSON_H
class Person {
private:
    std::string firstName, lastName;
    std::string phone, email;
public:
    Person(){}
    Person(std::string firstName, std::string lastName);
    Person(std::string firstName, std::string lastName, std::string email);
    Person(std::string firstName, std::string lastName, std::string email, std::string phone);
    virtual std::string getFirstName();
    virtual std::string getLastName();
    virtual std::string getPhone();
    virtual std::string getEmail();
    virtual void setFirstName(std::string firstName);
    virtual void setLastName(std::string lastName);
    virtual void setPhone(std::string phone);
    virtual void setEmail(std::string email);
};

#endif