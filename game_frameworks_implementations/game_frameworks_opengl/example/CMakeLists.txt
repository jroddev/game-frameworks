add_executable(gf_opengl_example main.cpp)
target_include_directories(gf_opengl_example PUBLIC
        include
        ${gf_sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gf_opengl_example
        PRIVATE
        gf_opengl
        gf_sdl2)

