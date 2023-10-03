cmake_minimum_required(VERSION 3.10)

add_library(sqlite3 C:/sqlite3/sqlite3.c)

add_executable(testPerson testPerson.cpp ../src/person.cpp)
add_executable(testDB testDB.cpp)

target_include_directories(testPerson PUBLIC ../inc .)
target_include_directories(testDB PUBLIC ../inc C:/sqlite3)
target_link_libraries(testDB PRIVATE sqlite3)