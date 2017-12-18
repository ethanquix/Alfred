cmake_minimum_required(VERSION 3.7)
project(AlfredBase VERSION 0.1 LANGUAGES CXX)

#Signature
include(Header.cmake)
PRINT_HEADER()

include(GNUInstallDirs)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__STRICT_ANSI__")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_MODE -g -ggdb -g3 -W -Wall -Wextra -Wno-comment -Wno-unknown-pragmas -Wno-unused-parameter -Wno-ignored-qualifiers")

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    set(CMAKE_CXX_FLAGS_RELEASE "/MT")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
endif (MSVC)

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
