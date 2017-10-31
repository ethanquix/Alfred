cmake_minimum_required(VERSION 3.7)
project(Alfred)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE -g -ggdb -g3")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_UTILS src/Utils/Singleton.hpp src/Utils/NonCopyable.hpp src/config.hpp src/Utils/Defer.hpp src/Async/AsyncUnorderedMap.hpp)

set(SOURCE_TIMER ${SOURCE_UTILS} src/Timer/Timer.hpp)

set(SOURCE_PROMISE ${SOURCE_UTILS} src/Promise/Promise.hpp src/Network/Implem/ServerTCP.hpp)

set(SOURCE_LOGGER ${SOURCE_UTILS} src/Logger/Logger.hpp)

#set(SOURCE_NETWORK ${SOURCE_UTILS} ${SOURCE_LOGGER} ${SOURCE_RANDOM} src/Network/ISerializer.hpp src/Network/Serializer/BasicSerializer.hpp src/Network/IClient.hpp src/Network/IServer.hpp src/Network/Implem/ServerTCP.hpp src/Network/Implem/ClientTCP.hpp src/Network/ClientInfo.hpp src/Network/AClient.hpp src/Network/exceptions/BindFailed.hpp)
set(SOURCE_NETWORK ${SOURCE_UTILS} ${SOURCE_LOGGER} ${SOURCE_RANDOM} src/Network/ISerializer.hpp src/Network/Serializer/BasicSerializer.hpp src/Network/IClient.hpp src/Network/Implem/ClientTCP.hpp src/Network/AClient.hpp src/Network/exceptions/BindFailed.hpp src/Network/IServer.hpp src/Network/Implem/ServerTCP.hpp src/Network/AServer.hpp src/Network/premade/ClientPremade.hpp)

set(SOURCE_MERKLE ${SOURCE_UTILS} ${SOURCE_LOGGER} src/Merkle/Merkle.hpp)

set(SOURCE_MATH ${SOURCE_UTILS} src/Math/Math.hpp src/Math/Matrix.hpp src/Math/MatrixException.hpp src/Math/Fraction.hpp)

set(SOURCE_INFINITE_LIST ${SOURCE_UTILS} src/InfiniteList/InfiniteList.hpp)

set(SOURCE_EVENT_MANAGER ${SOURCE_UTILS} src/EventManager/EventManager.hpp src/EventManager/EventManagerExceptions.hpp)

set(SOURCE_RANDOM ${SOURCE_UTILS} src/Random/Random.hpp)


include_directories(src/ src/Timer src/Utils src/Promise src/Logger src/Network src/Merkle src/Math src/InfiniteList src/EventManager src/Random src/Async)



#--------- TESTS ---------#

add_executable(test_Timer ${SOURCE_TIMER} test/testTimer.cpp)

add_executable(test_Promise ${SOURCE_PROMISE} test/testPromise.cpp)
target_link_libraries(test_Promise Threads::Threads)

add_executable(test_Logger ${SOURCE_LOGGER} test/testLogger.cpp)

add_executable(test_Server ${SOURCE_NETWORK} test/testServer.cpp test/testServerClient.hpp)
target_link_libraries(test_Server Threads::Threads)

add_executable(test_Client ${SOURCE_NETWORK} test/testClient.cpp test/testClient.hpp)
target_link_libraries(test_Client Threads::Threads)

add_executable(test_Math ${SOURCE_MATH} test/testMath.cpp)

add_executable(test_Merkle ${SOURCE_MERKLE} test/testMerkle.cpp)

add_executable(test_InfiniteList ${SOURCE_INFINITE_LIST} test/test_InfiniteList.cpp)

add_executable(test_EventManager ${SOURCE_EVENT_MANAGER} test/test_EventManager.cpp)

add_executable(test_Random ${SOURCE_RANDOM} test/testRandom.cpp)

add_executable(test_Defer ${SOURCE_UTILS} test/testDefer.cpp)