cmake_minimum_required(VERSION 3.10)

add_executable(testPerson testPerson.cpp ../src/person.cpp)

target_include_directories(testPerson PUBLIC ../inc .)