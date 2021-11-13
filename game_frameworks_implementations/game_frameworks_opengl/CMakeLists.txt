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

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.9.2
)
FetchContent_MakeAvailable(spdlog)


FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)


add_library(gf_opengl
        include/gf_opengl/opengl_render_api.h
        include/gf_opengl/camera.h
        include/gf_opengl/shader/shader.h
        include/gf_opengl/shader/shader_utils.h
        src/opengl_render_api.cpp
        src/line_rendering.cpp
        src/shader/shader_utils.cpp
        src/shader/shader.cpp
        )
target_include_directories(gf_opengl PUBLIC
        include
        ${glm_SOURCE_DIR}
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
        )

target_link_libraries(gf_opengl OpenGL::GL)
target_link_libraries(gf_opengl spdlog)


add_executable(gf_opengl_example example/main.cpp)
target_include_directories(gf_opengl_example PUBLIC
        include
        ${gf_sdl2_SOURCE_DIR}/include
        ${spdlog_SOURCE_DIR}/include)
target_link_libraries(gf_opengl_example
        PRIVATE
        gf_opengl
        gf_sdl2)

# https://www.jetbrains.com/help/clion/google-sanitizers.html#makefiles-compdb
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -g")
