---
project_name: tiznitbms
version: 1.0.0
licence: GPLv3
---
# Introduction

This is bank management system with 2 roles : **Teller** and **Customer**

- **Teller** : The person working on the bank and charged of serving customers. He/She can :
    - Register new customer
    - Update customer informations
    - Delete customer
    - Get customer informations 

- **Customer** : Bank account holder. He/She can :
    - Get balance information
    - Submit cash
    - Withdraw cash

The database contains 4 tables:
- **Customers** : Customers informations with each person has an account id
- **Accounts** : Contains account informations the id is the customer account id
- **Tellers** : Tellers informations (initialized with one teller with admin:admin as userName:password)

# Build and install software

To build and install software run the following command. set <custom_install_dir> to your target installation directory

```bash
mkdir build
cd build
```
To build with linux use the following build commands:
```bash
cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX=<custom_install_directoy> ..
cmake --build .
```

To build in Windows with visual studio use the following:
```bash
cmake -DCMAKE_INSTALL_PREFIX=<custom_install_directoy> ..
cmake --build . --config Release
```

Finally run the installation command:
```bash
cmake --install .
```

To run the software execute the following commands :

```bash
cd <custom_install_dir>
./main
```

For the first time an initialization step is done by generating a bank.db database file with necessary tables.

# User interface
This version is a CLI (Command-line interface). The main interface as following :

![main CLI](doc/images/mainCLI.png)

Log as a teller with the default userName and password :

![teller login](doc/images/tellerLogin.png)

Enjoy the control interface and create your first customer:

![teller interface](doc/images/tellerInterface.png)



