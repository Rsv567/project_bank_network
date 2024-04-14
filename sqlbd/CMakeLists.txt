cmake_minimum_required(VERSION 3.10)
project(BankSystem)

add_executable(BankSystem main.cpp)
add_subdirectory(src)
add_subdirectory(libraries)
target_link_libraries(BankSystem libraries)



target_link_libraries(BankSystem sql)
add_compile_options(-l sqlite3)

