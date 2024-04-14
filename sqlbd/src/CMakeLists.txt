cmake_minimum_required(VERSION 3.10)
set(SOURCE_LIB AccountOpening.cpp bank_transfer.cpp Registration.cpp SQLStatement.cpp StateClient.cpp create_data_base.cpp)
add_library(libraries SHARED ${SOURCE_LIB})
target_include_directories(libraries PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../header)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
install(TARGETS libraries DESTINATION lib)
