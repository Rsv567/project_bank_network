cmake_minimum_required(VERSION 3.10)
if (NOT ${SFML_FOUND})
  MESSAGE(STATUS "SFML not found, fetching it from GitHub")

  FetchContent_Declare(
      sfml
      GIT_REPOSITORY https://github.com/SFML/SFML.git
      GIT_TAG 2.6.0
  )

  FetchContent_MakeAvailable(sfml)

  include_directories(SYSTEM ${sfml_SOURCE_DIR}/include)

  MESSAGE(STATUS "SFML successfully fetched from GitHub")
endif (NOT ${SFML_FOUND})
set(SOURCE_LIB AccountOpening.cpp bank_transfer.cpp Registration.cpp SQLStatement.cpp StateClient.cpp create_data_base.cpp)
add_library(libraries SHARED ${SOURCE_LIB})
target_include_directories(libraries PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../header)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
install(TARGETS libraries DESTINATION lib)
