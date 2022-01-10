cmake_minimum_required(VERSION 3.0)
include(FetchContent)

project(game_frameworks VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(BUILD_FLAGS "${BUILD_FLAGS} -Wall -Wextra -pedantic")
# Warnings as Errors
set(BUILD_FLAGS "${BUILD_FLAGS} -Werror")

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.9.2
)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        cpp_dummy
        GIT_REPOSITORY https://github.com/jroddev/cpp-dummy
)
FetchContent_MakeAvailable(cpp_dummy)


add_library(game_frameworks
        src/utils/filename_cache.cpp)
target_include_directories(game_frameworks PUBLIC
        include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include
        )

target_link_libraries(game_frameworks spdlog)


##########################################
### TESTS
##########################################
add_executable(game_frameworks_test test/main.cpp test/utils/entity_identifier.cpp test/utils/filename_cache.cpp)
target_include_directories(game_frameworks_test
        PRIVATE
        include
        ${cpp_dummy_SOURCE_DIR}/include
        ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(game_frameworks_test gtest cpp_dummy game_frameworks)
gtest_add_tests(game_frameworks_test "" AUTO)
set_tests_properties(${game_frameworks_test} PROPERTIES TIMEOUT 10)
