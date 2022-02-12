project(tic_tac_toe VERSION 0.1.0)

find_package(spdlog)

project(tic_tac_toe_app)
add_executable(tic_tac_toe_app src/main.cpp)
target_include_directories(tic_tac_toe_app
        PRIVATE
        ${cpp_dummy_SOURCE_DIR}/include
        ${spdlog_INCLUDE_DIR})
target_link_libraries(tic_tac_toe_app
        cpp_dummy
        spdlog::spdlog
        )


if(RUN_TESTS)
    add_subdirectory(test)
endif()
