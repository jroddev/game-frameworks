cmake_minimum_required(VERSION 3.22)
include(FetchContent)
project(game_frameworks VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(BUILD_FLAGS "${BUILD_FLAGS} -Wall -Wextra -pedantic")
set(BUILD_FLAGS "${BUILD_FLAGS} -Werror") # Warnings as Errors
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g") # https://www.jetbrains.com/help/clion/google-sanitizers.html#makefiles-compdb

include(cmake/conan.cmake)
FetchContent_Declare(
        # Not Yet in Conan
        cpp_dummy
        GIT_REPOSITORY https://github.com/jroddev/cpp-dummy
)
FetchContent_MakeAvailable(cpp_dummy)


option(RUN_TESTS "Build the tests" ON)
if(RUN_TESTS)
    enable_testing()
    find_package(GTest)
endif()

add_subdirectory(game_frameworks_interfaces)
add_subdirectory(game_frameworks_implementations/game_frameworks)
add_subdirectory(game_frameworks_implementations/game_frameworks_sdl2)
add_subdirectory(game_frameworks_implementations/game_frameworks_opengl)

add_subdirectory(games/tic_tac_toe)

include(cmake/list_all_variables.cmake)