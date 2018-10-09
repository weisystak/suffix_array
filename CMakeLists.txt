cmake_minimum_required(VERSION 3.10)

# for header file
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}")


# copy test data
file(COPY
  "${CMAKE_CURRENT_SOURCE_DIR}/unit_test/test_data"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/unit_test/"
  )

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS  "-std=c++17")

project(DC3_test)
add_executable(DC3_test unit_test/DC3_test.cpp)
target_link_libraries(DC3_test gtest pthread gtest_main)


project(SAIS_test)
add_executable(SAIS_test unit_test/SAIS_test.cpp)
target_link_libraries(SAIS_test gtest pthread gtest_main)
