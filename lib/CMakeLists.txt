add_library(sqlite3 STATIC src/sqlite3.c)
target_include_directories(sqlite3 INTERFACE inc)