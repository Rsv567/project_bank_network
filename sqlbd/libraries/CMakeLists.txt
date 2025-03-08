cmake_minimum_required(VERSION 3.10)
add_library(sql SHARED sqlite3.c)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
install(TARGETS sql DESTINATION lib)
