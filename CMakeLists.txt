cmake_minimum_required(VERSION 3.14)
project(ComputerClub LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(task
    src/main.cpp
    src/Club.cpp
    src/Event.cpp
    src/Table.cpp
    src/ClubTime.cpp)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES tests/*.cpp)

add_executable(tests ${TEST_SOURCES})

target_sources(tests PRIVATE
    src/Club.cpp
    src/Event.cpp
    src/Table.cpp
    src/ClubTime.cpp
)

target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(tests
    gtest
    gtest_main
    pthread
)

add_test(NAME AllTests COMMAND tests)