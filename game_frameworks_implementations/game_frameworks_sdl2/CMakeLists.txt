cmake_minimum_required(VERSION 3.0)
include(FetchContent)

project(gf_sdl2 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_VERBOSE_MAKEFILE ON)
set(BUILD_FLAGS "${BUILD_FLAGS} -Wall -Wextra -pedantic")
# Warnings as Errors
set(BUILD_FLAGS "${BUILD_FLAGS} -Werror")

SET(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(STATUS "OPENGL_FOUND libs:${OPENGL_LIBRARIES}")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    message(STATUS "GLEW_FOUND version:${GLEW_VERSION} libs:${GLEW_LIBRARIES}")
endif()

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


add_library(gf_sdl2
        include/gf_sdl2_window/sdl2_opengl_window.h
        src/sdl2_opengl_window.cpp
        )
target_include_directories(gf_sdl2 PUBLIC
        include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        )

target_link_libraries(gf_sdl2 OpenGL::GL)
target_link_libraries(gf_sdl2 GLEW::GLEW)
target_link_libraries(gf_sdl2 spdlog)
target_link_libraries(gf_sdl2 SDL2-static)


add_executable(gf_sdl2_example example/main.cpp)
target_include_directories(gf_sdl2_example PUBLIC
        include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gf_sdl2_example
        PRIVATE
        gf_sdl2)
