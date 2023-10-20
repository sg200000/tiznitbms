#include <iostream>
#include "db.hpp"
#include "person.hpp"

class Teller : public Person {
private:
    std::string userName;
    int id;
    std::unique_ptr<DBManager> db;
    bool onlineState = false;
public:
    /**
     * @brief Construct a new Teller object
     * 
     * @param dbPath The bank database path
     */
    Teller(const std::string& dbPath);

    /**
     * @brief Destroy the Teller object
     * 
     */
    ~Teller() {}

    /**
     * @brief signIn to teller account
     * 
     * @param password the teller password
     * @return true if login successful
     * @return false otherwise
     */
    bool signIn(const std::string& password);

    /**
     * @brief Register a new customer
     * 
     * @param customer New customer informations
     * @param userName The new customer userName
     * @param password The new customer password
     * @param accountId The customer account id
     * @return true if the new customer successfuly registrated
     * @return false otherwise
     */
    bool registerNewCustomer(Person customer, const std::string& userName, const std::string& password, int accountId);

    /**
     * @brief Get the customer information
     * 
     * @param userName customer userName
     * @return std::unordered_map<std::string,std::string> customer information map
     */
    std::unordered_map<std::string,std::string> getCustomerInformation(const std::string& userName);

    /**
     * @brief Update customer information
     * 
     * @param userName customer userName
     * @param key The infrmation to update
     * @param value the new value
     * @return true if the information updated successfuly
     * @return false otherwise
     */
    bool updateCustomerInformation(const std::string& userName, const std::string& key, const std::string& value);

    /**
     * @brief Delete customer
     * 
     * @param userName customer userName
     * @return true if the customer deleted successfuly
     * @return false oherwise
     */
    bool deleteCustomer(const std::string& userName);

    /**
     * @brief Set the User Name
     * 
     * @param userName 
     */
    void setUserName(const std::string& userName){
        this->userName = userName;
    }

    /**
     * @brief Get the User Name
     * 
     * @return const std::string& 
     */
    const std::string& getUserName(){
        return this->userName;
    }

    /**
     * @brief Set the online state
     * 
     * @param onlineState 
     */
    void setOnlineState(bool onlineState){
        this->onlineState = onlineState;
    }

    /**
     * @brief Get the online state
     * 
     * @return true if the teller is online
     * @return false otherwise
     */
    bool getOnlineState() const {
        return this->onlineState;
    }
};