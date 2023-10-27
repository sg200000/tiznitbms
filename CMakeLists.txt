cmake_minimum_required(VERSION 3.14)
project(tiznitbms)


# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(sqlite3 STATIC lib/src/sqlite3.c)

# Create a constant of current project path
set(BASE_PATH "${CMAKE_CURRENT_LIST_DIR}")

# Generate a config header file with the The base project path
configure_file(
    ${CMAKE_SOURCE_DIR}/inc/config.hpp.in
    ${CMAKE_SOURCE_DIR}/inc/config.hpp
)

add_executable(main 
    main.cpp
    interface/customerCLI.cpp
    interface/tellerCLI.cpp
    
    src/person.cpp 
    src/customer.cpp
    src/teller.cpp
    src/sqlite3db.cpp
    src/utils.cpp)


target_include_directories(main PUBLIC inc interface/inc lib/inc)
target_link_libraries(main PRIVATE sqlite3 nlohmann_json::nlohmann_json)

include(CPack)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CPACK_GENERATOR "NSIS")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if (EXISTS "/etc/debian_version")
        message("CMake is running on a Debian-based distribution.")
        set(CPACK_GENERATOR "DEB")
    endif()
endif()

# Set other CPack options (e.g., package information)
set(CPACK_PACKAGE_NAME "tiznitbms")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION "This is my bank management system")

# Define a CPack component (required for NSIS generator)
set(CPACK_COMPONENTS_ALL app)

install(TARGETS main DESTINATION bin)
install(TARGETS sqlite3 DESTINATION lib)
install(FILES automation/generate_db.py automation/generate_db.sql DESTINATION automation)