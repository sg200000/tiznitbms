cmake_minimum_required(VERSION 3.14)
project(tiznitbms)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_library(sqlite3 C:/sqlite3/sqlite3.c)

add_executable(main main.cpp src/person.cpp src/customer.cpp)
target_include_directories(main PUBLIC inc C:/sqlite3)
target_link_libraries(main PRIVATE sqlite3)