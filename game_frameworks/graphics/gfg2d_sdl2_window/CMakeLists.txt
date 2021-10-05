cmake_minimum_required(VERSION 3.0)
include(FetchContent)

set(CI $ENV{CI})
message(STATUS "CI: ${CI}")

project(gfg2d_sdl2 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

#UNSET(GLEW_NO_GLU)
#UNSET(OpenGL_GL_PREFERENCE)
if(CI)
    message(STATUS "Skipping OpenGL as Build is running in CI: ${CI}")
else()
    SET(OpenGL_GL_PREFERENCE GLVND)
    find_package(OpenGL REQUIRED)
    if (OPENGL_FOUND)
        message(STATUS "OPENGL_FOUND libs:${OPENGL_LIBRARIES}")
    endif()


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


add_library(gfg2d_sdl2
        include/gfg2d_sdl2_window/sdl2_opengl_window.h
        src/sdl2_opengl_window.cpp
        )
target_include_directories(gfg2d_sdl2 PUBLIC
        include
        ${sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        )

if (NOT CI)
    target_link_libraries(gfg2d_sdl2 OpenGL::GL)

endif()
target_link_libraries(gfg2d_sdl2 GLEW::GLEW)
target_link_libraries(gfg2d_sdl2 spdlog)
target_link_libraries(gfg2d_sdl2 SDL2-static)




add_executable(gfg2d_sdl2_example example/main.cpp)
target_include_directories(gfg2d_sdl2_example PUBLIC
        include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gfg2d_sdl2_example
        PRIVATE
        gfg2d_sdl2)
