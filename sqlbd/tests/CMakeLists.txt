include(FetchContent)
project(Tests)
find_package(GTest QUIET)

if (NOT ${GTest_FOUND})
  MESSAGE(STATUS "GTest not found, fetching it from GitHub")
  FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG main
  )

  FetchContent_MakeAvailable(googletest)

  include_directories(${gtest_SOURCE_DIR}/include)

  MESSAGE(STATUS "GTest successfully fetched from GitHub")
endif (NOT ${GTest_FOUND})

add_executable(Tests EXCLUDE_FROM_ALL MainTests.cpp TestCollision.cpp)
target_link_libraries(Tests PUBLIC GTest::gtest_main libraries sql  sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

