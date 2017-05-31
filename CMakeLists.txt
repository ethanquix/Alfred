cmake_minimum_required(VERSION 3.7)
project(Alfred)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_PROMISE main.cpp src/Promise/Promise.hpp src/DecisionTree/DecisionTree.hpp src/Timer/Timer.hpp)
add_executable(Alfred ${SOURCE_PROMISE})
target_link_libraries(Alfred pthread)

set(SOURCE_LOGGER main.cpp src/Logger/Logger.hpp test/testLogger.cpp)
add_executable(Logger ${SOURCE_LOGGER})