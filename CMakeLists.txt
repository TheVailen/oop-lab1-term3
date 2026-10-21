cmake_minimum_required(VERSION 3.16)
project(lab1_variant2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(main_app main.cpp array_ops.cpp)
target_include_directories(main_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_variant test_variant.cpp array_ops.cpp)
target_include_directories(test_variant PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(test_variant GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_variant)
