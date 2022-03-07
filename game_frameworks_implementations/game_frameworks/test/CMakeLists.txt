add_library(game_frameworks_dummy dummy.cpp)
target_include_directories(game_frameworks_dummy
        PRIVATE
        ${game_frameworks_INCLUDE_DIRS}
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${cpp_dummy_SOURCE_DIR}/include)

add_executable(game_frameworks_test main.cpp utils/entity_identifier.cpp utils/filename_cache.cpp)
target_include_directories(game_frameworks_test
        PRIVATE
        ${game_frameworks_INCLUDE_DIRS}
        ${cpp_dummy_SOURCE_DIR}/include
        ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(game_frameworks_test GTest::gtest_main cpp_dummy game_frameworks game_frameworks_dummy)
add_test(NAME game_frameworks_test
        COMMAND game_frameworks_test)
set_tests_properties(${conan_project_tests} PROPERTIES TIMEOUT 10)