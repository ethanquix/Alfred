cmake_minimum_required(VERSION 3.7)
project(Alfred)

set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG_MODE")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_UTILS src/Utils/Singleton.hpp src/Utils/NonCopyable.hpp)

set(SOURCE_TIMER src/Timer/Timer.hpp)

set(SOURCE_PROMISE src/Promise/Promise.hpp)

set(SOURCE_LOGGER ${SOURCE_UTILS} src/Logger/Logger.hpp test/testLogger.cpp)

include_directories(src/Timer src/Utils src/Promise src/Logger)


#--------- TESTS ---------#

add_executable(test_Timer ${SOURCE_TIMER} test/testTimer.cpp)

add_executable(test_Promise ${SOURCE_PROMISE} test/testPromise.cpp)
target_link_libraries(test_Promise pthread)

add_executable(test_Logger ${SOURCE_LOGGER} test/testLogger.cpp)

