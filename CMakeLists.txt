cmake_minimum_required(VERSION 3.7)
project(Alfred)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/Logger/Logger.cpp src/Logger/Logger.hpp)
add_executable(Alfred ${SOURCE_FILES})