cmake_minimum_required(VERSION 3.7)
project(Alfred)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_UTILS src/Utils/Singleton.hpp src/Utils/NonCopyable.hpp)

set(SOURCE_TIMER src/Timer/Timer.hpp)

set(SOURCE_PROMISE src/Promise/Promise.hpp)

set(SOURCE_LOGGER ${SOURCE_UTILS} src/Logger/Logger.hpp)

set(SOURCE_NETWORK ${SOURCE_UTILS} ${SOURCE_LOGGER} src/Network/INetwork.hpp src/Network/ISerializer.hpp src/Network/Serializer/BasicSerializer.hpp)

set(SOURCE_MERKLE ${SOURCE_UTILS} ${SOURCE_LOGGER} src/Merkle/Merkle.hpp)

set(SOURCE_MATH ${SOURCE_UTILS} src/Math/Math.hpp src/Math/Matrix.hpp src/Math/MatrixException.hpp)

set(SOURCE_INFINITE_LIST ${SOURCE_UTILS} src/InfiniteList/InfiniteList.hpp)

include_directories(src/Timer src/Utils src/Promise src/Logger src/Network src/Merkles src/Math src/InfiniteList)



#--------- TESTS ---------#

add_executable(test_Timer ${SOURCE_TIMER} test/testTimer.cpp)

add_executable(test_Promise ${SOURCE_PROMISE} test/testPromise.cpp)
target_link_libraries(test_Promise pthread)

add_executable(test_Logger ${SOURCE_LOGGER} test/testLogger.cpp)

add_executable(test_Network ${SOURCE_NETWORK} test/testNetwork.cpp)

add_executable(test_Math ${SOURCE_MATH} test/testMath.cpp)

add_executable(test_Merkle ${SOURCE_MERKLE} test/testMerkle.cpp)

add_executable(test_InfiniteList ${SOURCE_INFINITE_LIST} test/test_InfiniteList.cpp)
