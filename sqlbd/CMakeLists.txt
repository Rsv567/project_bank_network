cmake_minimum_required(VERSION 3.10)
project(BankSystem)
add_executable(BankSystem main.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_package(SFML 2.5.1 REQUIRED graphics audio window system)
target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
add_subdirectory(src)
add_subdirectory(libraries)

target_link_libraries(BankSystem libraries)


target_link_libraries(BankSystem sql)
add_compile_options(-l sqlite3)
add_subdirectory(tests)
