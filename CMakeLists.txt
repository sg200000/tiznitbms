cmake_minimum_required(VERSION 3.14)
project(tiznitbms)


# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

## External libraries
# nlohamann_json
include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# sqlite3
add_subdirectory(lib)

## Build the executable
# Set sources 
set(INTERFACE_SOURCES
    interface/src/mainCLI.cpp
    interface/src/customerCLI.cpp
    interface/src/tellerCLI.cpp
)

set(SYSTEM_SOURCES
    bms/src/person.cpp 
    bms/src/customer.cpp
    bms/src/teller.cpp
)

set(DB_SOURCES
    bms/src/db.cpp
    bms/src/sqlite3db.cpp
)

set(UTILS_SOURCES
    bms/src/utils.cpp
)

set(INIT_SOURCES
    init/src/initializer.cpp
)

# Build the main executable
add_executable(main 
    main.cpp
    ${INTERFACE_SOURCES}
    ${INIT_SOURCES}
    ${SYSTEM_SOURCES}
    ${DB_SOURCES}
    ${UTILS_SOURCES}
)

## Link the main executable json and sqlite3 libraries
target_link_libraries(main nlohmann_json::nlohmann_json sqlite3)
target_include_directories(main PUBLIC interface/inc bms/inc init/inc)

## Install the target
install(TARGETS main DESTINATION ".")
install(FILES sql/bank.sql DESTINATION "sql")
