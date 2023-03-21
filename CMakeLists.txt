cmake_minimum_required(VERSION 3.7)
project(Alfred VERSION 0.1 LANGUAGES CXX)

include(GNUInstallDirs)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE -g -ggdb -g3 -W -Wall -Wextra -Wno-comment -Wno-unknown-pragmas -Wno-unused-parameter -Wno-ignored-qualifiers -Wno-unused-function")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif (MSVC)

include_directories(src)

#--------- LIBRARY ---------#

add_library(Alfred INTERFACE)

target_include_directories(Alfred INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/> $<INSTALL_INTERFACE:src/>)

target_link_libraries(Alfred INTERFACE Threads::Threads)

target_compile_features(Alfred
        INTERFACE cxx_auto_type cxx_variadic_templates)

if (WIN32)
    target_link_libraries(Alfred INTERFACE wsock32 ws2_32)
endif ()

#--------- TESTING ---------#

if (EXISTS "${PROJECT_SOURCE_DIR}/test/googletest/CMakeLists.txt")

    add_subdirectory(test/googletest)

    enable_testing()

    file(GLOB TEST_SRC
            ${PROJECT_SOURCE_DIR}/test/*.cpp
            ${PROJECT_SOURCE_DIR}/test/*.hpp

            ${PROJECT_SOURCE_DIR}/test/ecs/*.cpp
            ${PROJECT_SOURCE_DIR}/test/ecs/*.hpp
            )

    add_executable(Alfred_TEST ${TEST_SRC})
    target_link_libraries(Alfred_TEST Alfred gtest gtest_main)
    add_test(all Alfred_TEST)

else ()
    message("[ALFRED] No googletest folder found in /test/googletest. Please clone it using submodules")
endif ()

#--------- EXAMPLES ---------#

if (NOT ALFRED_NO_EXEMPLES)

    message("[ALFRED] set(ALFRED_NO_EXEMPLES TRUE) to disable exemples")

    add_executable(example_InfiniteList_PrimeNumber examples/InfiniteList/example_InfiniteList_PrimeNumber.cpp)
    target_link_libraries(example_InfiniteList_PrimeNumber Alfred)

    add_executable(example_Partial examples/Function/example_Partial.cpp)
    target_link_libraries(example_Partial Alfred)

    add_executable(example_Defer examples/Utils/example_Defer.cpp)
    target_link_libraries(example_Defer Alfred)

    add_executable(example_Counter examples/Utils/example_Counter.cpp)
    target_link_libraries(example_Counter Alfred)

    add_executable(example_DynamicLibrary examples/Utils/example_DynamicLibrary.cpp)
    target_link_libraries(example_DynamicLibrary Alfred)

    add_executable(example_EventManager examples/EventManager/example_EventManager.cpp)
    target_link_libraries(example_EventManager Alfred)

    add_executable(example_Logger examples/Logger/example_Logger.cpp)
    target_link_libraries(example_Logger Alfred)

    add_executable(example_Timer_SimpleTimer examples/Timer/example_Timer_SimpleTimer.cpp)
    target_link_libraries(example_Timer_SimpleTimer Alfred)

    add_executable(example_Timer_Timer examples/Timer/example_Timer_Timer.cpp)
    target_link_libraries(example_Timer_Timer Alfred)

endif ()
#--------- INSTALL ---------#

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS Alfred EXPORT AlfredConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows

install(DIRECTORY src/Alfred DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT AlfredConfig DESTINATION share/Alfred/cmake)

# This makes the project importable from the build directory
export(TARGETS Alfred FILE AlfredConfig.cmake)