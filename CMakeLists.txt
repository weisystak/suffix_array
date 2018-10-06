project(DC3_test)

# for DC3.hpp
include_directories ("${PROJECT_SOURCE_DIR}")

# copy test data
file(COPY
  "${PROJECT_SOURCE_DIR}/unit_test/test_data"
  DESTINATION "${PROJECT_BINARY_DIR}/unit_test/"
  )

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS  "-std=c++17")
add_executable(DC3_test unit_test/DC3_test.cpp)
target_link_libraries(DC3_test gtest pthread gtest_main)
