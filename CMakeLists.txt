cmake_minimum_required(VERSION 3.16.3)
project(MyTinyAlgorithm)

set(CMAKE_CXX_STANDARD 11)

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/Build) # 自定义路径变量
set(TEST_PATH ${CMAKE_SOURCE_DIR}/Test)
set(SOURCE_PATH ${CMAKE_SOURCE_DIR}/Algorithm)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_PATH}) # EXE
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_PATH}) # LIB

add_executable(TestAll ${TEST_PATH}/test_all.cpp)

if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    add_definitions(-DDEBUG)
endif()