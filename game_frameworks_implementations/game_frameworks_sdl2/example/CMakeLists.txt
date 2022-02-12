add_executable(gf_sdl2_example main.cpp)
target_include_directories(gf_sdl2_example PUBLIC
        include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gf_sdl2_example
        PRIVATE
        gf_sdl2)
