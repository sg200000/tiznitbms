/*
 * Description : Person header file
 * Copyright (C) 2023 Said Guouihaj
 * Licence : GPLv3
*/

#include <iostream>
#include <string>

#ifndef PERSON_H
#define PERSON_H
class Person {
public:
    /**
     * @brief Construct a new Person object
     * 
     * @param firstName 
     * @param lastName 
     * @param email 
     * @param phone 
     */
    Person(const std::string& firstName = "", const std::string& lastName = "", const std::string& email = "", const std::string& phone = "");

    /**
     * @brief Get the First Name
     * 
     * @return const std::string& 
     */
    std::string getFirstName();

    /**
     * @brief Get the Last Name
     * 
     * @return std::string 
     */
    std::string getLastName();

    /**
     * @brief Get the Phone number
     * 
     * @return std::string 
     */
    std::string getPhone();

    /**
     * @brief Get the Email
     * 
     * @return std::string 
     */
    std::string getEmail();

    /**
     * @brief Set the First Name
     * 
     * @param firstName 
     */
    void setFirstName(const std::string& firstName);

    /**
     * @brief Set the Last Name
     * 
     * @param lastName 
     */
    void setLastName(const std::string& lastName);

    /**
     * @brief Set the Phone number
     * 
     * @param phone 
     */
    void setPhone(const std::string& phone);

    /**
     * @brief Set the Email
     * 
     * @param email 
     */
    void setEmail(const std::string& email);

private:
    std::string firstName, lastName;
    std::string phone, email;
};
#endif