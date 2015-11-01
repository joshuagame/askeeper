cmake_minimum_required(VERSION 3.3)
project(askeeper)

# Add local CMake module paths
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# source code
set(SOURCE_FILES main.cpp)

# include directories
include(FindPoco)
INCLUDE_DIRECTORIES(${Poco_INCLUDE_DIRS})

# libraries and target
add_executable(askeeper ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(askeeper ${Poco_LIBRARIES})
