cmake_minimum_required(VERSION 3.10)

add_executable(main main.cpp src/person.cpp)

target_include_directories(main PUBLIC inc)