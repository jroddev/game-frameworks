cmake_minimum_required(VERSION 3.0)
include(FetchContent)

project(tic_tac_toe VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

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

##########################################
### APPLICATION
##########################################
project(tic_tac_toe_app)
add_executable(tic_tac_toe_app src/main.cpp)
target_include_directories(tic_tac_toe_app
        PRIVATE
        ${cpp_dummy_SOURCE_DIR}/include)
target_link_libraries(tic_tac_toe_app cpp_dummy)


##########################################
### TESTS
##########################################
add_executable(tic_tac_toe_test test/main.cpp)
target_include_directories(tic_tac_toe_test
        PRIVATE
        ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(tic_tac_toe_test gtest)
gtest_add_tests(tic_tac_toe_test "" AUTO)
set_tests_properties(${tic_tac_toe_test} PROPERTIES TIMEOUT 10)
