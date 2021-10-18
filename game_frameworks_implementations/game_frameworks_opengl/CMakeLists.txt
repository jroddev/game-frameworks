cmake_minimum_required(VERSION 3.0)
include(FetchContent)

project(gf_opengl VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_VERBOSE_MAKEFILE ON)

SET(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message(STATUS "OPENGL_FOUND libs:${OPENGL_LIBRARIES}")
endif()

#find_package(GLEW REQUIRED)
#if (GLEW_FOUND)
#    message(STATUS "GLEW_FOUND version:${GLEW_VERSION} libs:${GLEW_LIBRARIES}")
#endif()

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.9.2
)
FetchContent_MakeAvailable(spdlog)


add_library(gf_opengl
        src/gf_opengl.cpp
        )
target_include_directories(gf_opengl PUBLIC
        include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
#        ${GLEW_INCLUDE_DIRS}
        )

target_link_libraries(gf_opengl OpenGL::GL)
#target_link_libraries(gf_opengl GLEW::GLEW)
target_link_libraries(gf_opengl spdlog)


add_executable(gf_opengl_example example/main.cpp)
target_include_directories(gf_opengl_example PUBLIC
        include
        ${sdl2_SOURCE_DIR}/include
        ${gf_sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gf_opengl_example
        PRIVATE
        gf_opengl
        gf_sdl2)
