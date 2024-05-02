cmake_minimum_required(VERSION 3.10)
project(BankSystem)
add_executable(BankSystem main.cpp)

find_package(SFML 2.5.1 REQUIRED graphics audio window system)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
add_subdirectory(src)
add_subdirectory(libraries)
target_link_libraries(BankSystem libraries)


target_link_libraries(BankSystem sql)
add_compile_options(-l sqlite3)
