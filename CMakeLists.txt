cmake_minimum_required(VERSION 3.7)
project(AlfredBase VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE -g -ggdb -g3")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_UTILS src/AlfredBase/Utils/Singleton.hpp src/AlfredBase/Utils/NonCopyable.hpp src/AlfredBase/config.hpp src/AlfredBase/Utils/Defer.hpp src/AlfredBase/Async/AsyncUnorderedMap.hpp)

set(SOURCE_TIMER ${SOURCE_UTILS} src/AlfredBase/Timer/Timer.hpp)

set(SOURCE_PROMISE ${SOURCE_UTILS} src/AlfredBase/Async/Promise.hpp src/AlfredBase/Network/Implem/ServerTCP.hpp)

set(SOURCE_LOGGER ${SOURCE_UTILS} src/AlfredBase/Logger/Logger.hpp)

set(SOURCE_NETWORK ${SOURCE_UTILS} ${SOURCE_LOGGER} ${SOURCE_RANDOM} src/AlfredBase/Network/ISerializer.hpp src/AlfredBase/Network/Serializer/BasicSerializer.hpp src/AlfredBase/Network/IClient.hpp src/AlfredBase/Network/Implem/ClientTCP.hpp src/AlfredBase/Network/AClient.hpp src/AlfredBase/Network/exceptions/BindFailed.hpp src/AlfredBase/Network/IServer.hpp src/AlfredBase/Network/Implem/ServerTCP.hpp src/AlfredBase/Network/AServer.hpp src/AlfredBase/Network/premade/ClientPremade.hpp)

set(SOURCE_MATH ${SOURCE_UTILS} src/AlfredBase/Math/Math.hpp src/AlfredBase/Math/Matrix.hpp src/AlfredBase/Math/MatrixException.hpp src/AlfredBase/Math/Fraction.hpp)

set(SOURCE_INFINITE_LIST ${SOURCE_UTILS} src/AlfredBase/Infinite/InfiniteList.hpp src/AlfredBase/Infinite/premade/InfiniteListPremade.hpp)

set(SOURCE_EVENT_MANAGER ${SOURCE_UTILS} src/AlfredBase/EventManager/EventManager.hpp src/AlfredBase/EventManager/EventManagerExceptions.hpp)

set(SOURCE_RANDOM ${SOURCE_UTILS} src/AlfredBase/Random/Random.hpp)


include_directories(src)


#--------- TESTS ---------#

add_executable(test_Timer ${SOURCE_TIMER} test/testTimer.cpp)
target_link_libraries(test_Timer Threads::Threads)

add_executable(test_Promise ${SOURCE_PROMISE} test/testPromise.cpp)
target_link_libraries(test_Promise Threads::Threads)

add_executable(test_Logger ${SOURCE_LOGGER} test/testLogger.cpp)

add_executable(test_Server ${SOURCE_NETWORK} test/testServer.cpp test/testServerClient.hpp)
target_link_libraries(test_Server Threads::Threads)

add_executable(test_Client ${SOURCE_NETWORK} test/testClient.cpp test/testClient.hpp)
target_link_libraries(test_Client Threads::Threads)

add_executable(test_Math ${SOURCE_MATH} test/testMath.cpp)

add_executable(test_InfiniteList ${SOURCE_INFINITE_LIST} test/testInfiniteList.cpp)

add_executable(test_EventManager ${SOURCE_EVENT_MANAGER} test/testEventManager.cpp)

add_executable(test_Random ${SOURCE_RANDOM} test/testRandom.cpp)

add_executable(test_Defer ${SOURCE_UTILS} test/testDefer.cpp)

#--------- LIBRARY ---------#

add_library(AlfredBase INTERFACE)

target_include_directories(AlfredBase INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/AlfredBase>)

target_link_libraries(AlfredBase INTERFACE Threads::Threads)

target_compile_features(AlfredBase
        INTERFACE cxx_auto_type cxx_variadic_templates)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS AlfredBase EXPORT AlfredBase
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY src/AlfredBase DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT AlfredBase DESTINATION share/AlfredBase/cmake)

# This makes the project importable from the build directory
export(TARGETS AlfredBase FILE AlfredBase.cmake)