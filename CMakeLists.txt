cmake_minimum_required(VERSION 3.14)
project(tiznitbms)


# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(sqlite3 C:/sqlite3/sqlite3.c)

add_executable(main 
    main.cpp
    interface/customerCLI.cpp
    interface/tellerCLI.cpp
    
    src/person.cpp 
    src/customer.cpp
    src/teller.cpp
    src/sqlite3db.cpp
    src/utils.cpp)


target_include_directories(main PUBLIC inc C:/sqlite3 interface/inc)
target_link_libraries(main PRIVATE sqlite3 nlohmann_json::nlohmann_json)