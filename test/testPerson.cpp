#include "../inc/person.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

class testPerson : public Person {
public:
    bool constrReached[4] = {false, false, false, false};
    bool getReached[4] = {false, false, false, false};
    bool setReached[4] = {false, false, false, false};
    testPerson() {
        Person::Person();
        constrReached[0] = true;
    }
    testPerson(std::string firstName, std::string lastName){
        Person::Person(firstName, lastName);
        constrReached[1] = true;
    }
    testPerson(std::string firstName, std::string lastName, std::string email){
        Person::Person(firstName, lastName, email);
        constrReached[2] = true;
    }
    testPerson(std::string firstName, std::string lastName, std::string email, std::string phone){
        Person::Person(firstName, lastName, email, phone);
        constrReached[3] = true;
    }
    std::string getFirstName() override {
        std::string firstName = Person::getFirstName();
        getReached[0] = true;
        return firstName;
    }
    std::string getLastName() override {
        std::string lastName = Person::getLastName();
        getReached[1] = true;
        return lastName;
    }
    std::string getPhone() override {
        std::string phone = Person::getPhone();
        getReached[2] = true;
        return phone;
    }
    std::string getEmail() override {
        std::string email = Person::getEmail();
        getReached[3] = true;
        return email;
    }
    void setFirstName(std::string firstName) override {
        Person::setFirstName(firstName);
        setReached[0] = true;
    }
    void setLastName(std::string lastName) override {
        Person::setLastName(lastName);
        setReached[1] = true;
    }
    void setEmail(std::string email) override {
        Person::setEmail(email);
        setReached[2] = true;
    }
    void setPhone(std::string phone) override {
        Person::setPhone(phone);
        setReached[3] = true;
    }
};

TEST_CASE("check all methods reached"){
    testPerson person1;
    person1.setFirstName("said");
    person1.setLastName("guouihaj");
    person1.setEmail("saidguouihaj@gmail.com");
    person1.setPhone("0643789275");

    for (bool attr : person1.setReached){
        CHECK(attr == true);
    }

    testPerson person2("ahmed", "guouihaj");
    person2.setEmail("ahmedguouihaj@gmail.com");
    person2.setPhone("0145887589");

    for (int i=2;i<4;i++){
        CHECK(person2.setReached[i] == true);
    }

    testPerson person3("ali", "guouihaj", "aliguouihaj@gmail.com");
    person3.setPhone("0236588999");

    for (int i=3;i<4;i++){
        CHECK(person3.setReached[i] == true);
    }

    testPerson person4("mohamed","guouihaj","mohamedguouihaj@gmail.com", "0698447789");
    person4.getFirstName();
    person4.getLastName();
    person4.getEmail();
    person4.getPhone();

    for (bool attr : person4.getReached){
        CHECK(attr == true);
    }

}

