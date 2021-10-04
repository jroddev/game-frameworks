cmake_minimum_required(VERSION 3.0)
include(FetchContent)


project(gfg2d_sdl2 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.0.16
)
FetchContent_MakeAvailable(sdl2)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.9.2
)
FetchContent_MakeAvailable(spdlog)

add_library(gfg2d_sdl2
        include/gfg2d_sdl2_window/sdl2_opengl_window.h
        src/sdl2_opengl_window.cpp
        )
target_include_directories(gfg2d_sdl2 PUBLIC
        include
        ${sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gfg2d_sdl2
        PRIVATE
        SDL2-static
        spdlog)


add_executable(gfg2d_sdl2_test test/main.cpp)
target_include_directories(gfg2d_sdl2_test PUBLIC
        include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gfg2d_sdl2_test
        PRIVATE
        gfg2d_sdl2)
