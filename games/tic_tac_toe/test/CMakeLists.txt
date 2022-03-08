add_executable(tic_tac_toe_test main.cpp)
target_include_directories(tic_tac_toe_test
        PRIVATE
        ${GTest_INCLUDE_DIRS})
target_link_libraries(tic_tac_toe_test gtest)
add_test(NAME tic_tac_toe_test
        COMMAND tic_tac_toe_test)
set_tests_properties(${tic_tac_toe_test} PROPERTIES TIMEOUT 10)