cmake_minimum_required(VERSION 3.5)
project(field_arithmetic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(LONG_ARITHMETIC_DIR ${CMAKE_SOURCE_DIR}/long_arithmetic)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

set(SOURCES
    ${SOURCE_DIR}/field_element.cpp
    ${SOURCE_DIR}/field.cpp
)
set(LONG_ARITHMETIC
    ${LONG_ARITHMETIC_DIR}/digit.cpp
    ${LONG_ARITHMETIC_DIR}/long_arithmetic.cpp
    ${LONG_ARITHMETIC_DIR}/operators.cpp
)

include_directories(${SOURCE_DIR})
include_directories(${LONG_ARITHMETIC_DIR})

add_executable(driver ${TEST_DIR}/driver.cpp 
${SOURCES} ${LONG_ARITHMETIC})
add_executable(benchmark ${TEST_DIR}/benchmark.cpp 
${SOURCES} ${LONG_ARITHMETIC})
add_executable(corr_test ${TEST_DIR}/corr_test.cpp 
${SOURCES} ${LONG_ARITHMETIC})