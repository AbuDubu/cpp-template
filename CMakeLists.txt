cmake_minimum_required(VERSION 3.25)

project(cpp_template VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(project_warnings INTERFACE)
target_compile_options(project_warnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wconversion
        -Wformat=2
)

add_library(core STATIC
        src/clamp.c
        src/stats.cpp
)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(core PRIVATE _GNU_SOURCE)
target_link_libraries(core PRIVATE project_warnings)

add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE core project_warnings)

option(BUILD_TESTING "Build the unit tests" ON)

if(BUILD_TESTING)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(googletest
        URL
        https://github.com/google/googletest/archive/refs/tags/v1.18.0.tar.gz
        URL_HASH
        SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
        SYSTEM
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(unit_tests
        tests/clamp_test.cpp
        tests/stats_test.cpp
    )
    target_link_libraries(unit_tests PRIVATE core
        project_warnings GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(unit_tests)
endif()

option(BUILD_BENCHMARKS "Build the benchmarks (use the bench preset)" OFF)

if(BUILD_BENCHMARKS)
    include(FetchContent)
    set(BENCHMARK_ENABLE_TESTING OFF)
    FetchContent_Declare(benchmark
        URL https://github.com/google/benchmark/archive/refs/tags/v1.10.0.tar.gz
        URL_HASH SHA256=acc5c7c0fbed855c4aaa2d7c3c36fb82b0c15c28f4e151e3f679c2fc0aa404af
        SYSTEM
    )
    FetchContent_MakeAvailable(benchmark)

    add_executable(stats_bench bench/stats_bench.cpp)
    target_link_libraries(stats_bench PRIVATE core project_warnings benchmark::benchmark)
endif()
