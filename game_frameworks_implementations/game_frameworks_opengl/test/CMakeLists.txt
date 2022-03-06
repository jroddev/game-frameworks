
add_library(gf_opengl_dummy dummy.cpp)
target_include_directories(gf_opengl_dummy
        PRIVATE
        ${glm_INCLUDE_DIR}
        ${gf_opengl_INCLUDE_DIRS}
        ${game_frameworks_SOURCE_DIR}/include
        ${cpp_dummy_SOURCE_DIR}/include)
target_link_libraries(gf_opengl_dummy cpp_dummy)

add_executable(gf_opengl_test main.cpp texture.cpp)
target_include_directories(gf_opengl_test
        PRIVATE
        ${gf_opengl_INCLUDE_DIRS}
        ${cpp_dummy_SOURCE_DIR}/include
        ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(gf_opengl_test GTest::gtest_main cpp_dummy gf_opengl gf_opengl_dummy game_frameworks_dummy)
add_test(NAME gf_opengl_test
        COMMAND gf_opengl_test)
set_tests_properties(${conan_project_tests} PROPERTIES TIMEOUT 10)