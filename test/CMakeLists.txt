cmake_minimum_required(VERSION 3.10)

project(tiznitbms)

add_library(sqlite3 C:/sqlite3/sqlite3.c)

add_executable(testUtils testUtils.cpp ../src/utils.cpp)
add_executable(testDB testDB.cpp ../src/sqlite3db.cpp ../src/utils.cpp)

target_include_directories(testDB PUBLIC ../inc C:/sqlite3)
target_link_libraries(testDB PRIVATE sqlite3)

target_include_directories(testUtils PUBLIC ../inc)