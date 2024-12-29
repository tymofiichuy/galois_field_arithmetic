cmake_minimum_required(VERSION 3.5)
project(field_arithmetic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${SOURCE_DIR})

add_executable(driver ${TEST_DIR}/driver.cpp 
${SOURCE_DIR}/field_element.cpp ${SOURCE_DIR}/field.cpp)