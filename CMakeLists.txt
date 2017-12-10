cmake_minimum_required(VERSION 3.7)
project(AlfredBase VERSION 0.1 LANGUAGES CXX)

#Signature
include(Header.cmake)
PRINT_HEADER()

include(GNUInstallDirs)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE -g -ggdb -g3")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif (MSVC)

set(SOURCE_UTILS src/AlfredBase/Utils/Singleton.hpp src/AlfredBase/Utils/NonCopyable.hpp src/AlfredBase/config.hpp src/AlfredBase/Utils/Defer.hpp src/AlfredBase/Async/AsyncUnorderedMap.hpp src/AlfredBase/Utils/Counter.hpp src/AlfredBase/Utils/MapSingleton.hpp)

set(SOURCE_TIMER ${SOURCE_UTILS} src/AlfredBase/Timer/Timer.hpp)

#/!\ Disabled because need rework (capture during initialization
#set(SOURCE_PROMISE ${SOURCE_UTILS} src/AlfredBase/Async/Promise.hpp src/AlfredBase/Network/Implem/ServerTCP.hpp)

set(SOURCE_LOGGER ${SOURCE_UTILS} src/AlfredBase/Logger/Logger.hpp)

set(SOURCE_NETWORK ${SOURCE_UTILS} ${SOURCE_LOGGER} ${SOURCE_RANDOM} src/AlfredBase/Network/ISerializer.hpp src/AlfredBase/Network/Serializer/BasicSerializer.hpp src/AlfredBase/Network/IClient.hpp src/AlfredBase/Network/Implem/ClientTCP.hpp src/AlfredBase/Network/AClient.hpp src/AlfredBase/Network/exceptions/BindFailed.hpp src/AlfredBase/Network/IServer.hpp src/AlfredBase/Network/Implem/ServerTCP.hpp src/AlfredBase/Network/AServer.hpp src/AlfredBase/Network/premade/ClientPremade.hpp)

set(SOURCE_MATH ${SOURCE_UTILS} src/AlfredBase/Math/Math.hpp src/AlfredBase/Math/Matrix.hpp src/AlfredBase/Math/MatrixException.hpp src/AlfredBase/Math/Fraction.hpp)

set(SOURCE_INFINITE_LIST ${SOURCE_UTILS} src/AlfredBase/Infinite/InfiniteList.hpp src/AlfredBase/Infinite/premade/InfiniteListPremade.hpp)

set(SOURCE_EVENT_MANAGER ${SOURCE_UTILS} src/AlfredBase/EventManager/EventManagerExceptions.hpp src/AlfredBase/EventManager/EventManager.hpp)

set(SOURCE_RANDOM ${SOURCE_UTILS} src/AlfredBase/Random/Random.hpp)

set(SOURCE_ECS ${SOURCE_UTILS} src/AlfredBase/Ecs/Entity.hpp src/AlfredBase/Ecs/Manager.hpp src/AlfredBase/Ecs/Component.hpp src/AlfredBase/Ecs/EcsCounter.hpp)

include_directories(src)

#--------- LIBRARY ---------#

add_library(AlfredBase INTERFACE)

target_include_directories(AlfredBase INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/AlfredBase> $<INSTALL_INTERFACE:src/>)

target_link_libraries(AlfredBase INTERFACE Threads::Threads)

target_compile_features(AlfredBase
        INTERFACE cxx_auto_type cxx_variadic_templates)

if(WIN32)
    target_link_libraries(AlfredBase INTERFACE wsock32 ws2_32)
endif()

#--------- TESTING ---------#

if(EXISTS "${PROJECT_SOURCE_DIR}/test/googletest/CMakeLists.txt")

    add_subdirectory(test/googletest)

    enable_testing()

    file(GLOB TEST_SRC
            ${PROJECT_SOURCE_DIR}/test/*.cpp
            ${PROJECT_SOURCE_DIR}/test/*.hpp

            ${PROJECT_SOURCE_DIR}/test/ecs/*.cpp
            ${PROJECT_SOURCE_DIR}/test/ecs/*.hpp
            )

    add_executable(AlfredBase_TEST ${TEST_SRC})
    #add_executable(AlfredBase_TEST test/testDefer.cpp test/main.cpp)
    target_link_libraries(AlfredBase_TEST AlfredBase gtest)
    add_test(all AlfredBase_TEST)

else()

    message("No googletest folder found un /test/googletest. Please clone it using submodules")

endif()


#--------- INSTALL ---------#

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS AlfredBase EXPORT AlfredBaseConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY src/AlfredBase DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT AlfredBaseConfig DESTINATION share/AlfredBase/cmake)

# This makes the project importable from the build directory
export(TARGETS AlfredBase FILE AlfredBaseConfig.cmake)
