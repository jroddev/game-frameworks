project(gf_opengl VERSION 0.1.0)

find_package(opengl_system)
find_package(GLEW)
find_package(glm)
find_package(stb)
find_package(fmt)

SET(gf_opengl_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(gf_opengl
        include/gf_opengl/opengl_render_api.h
        include/gf_opengl/camera.h
        include/gf_opengl/shader/shader.h
        include/gf_opengl/shader/shader_utils.h
        src/opengl_render_api.cpp
        src/line_rendering.cpp
        src/quad_rendering.cpp
        src/sprite_rendering.cpp
        src/shader/shader_utils.cpp
        src/shader/shader.cpp
        src/texture.cpp
        )
target_include_directories(gf_opengl PUBLIC
        ${gf_opengl_INCLUDE_DIRS}
        ${glm_INCLUDE_DIR}
        ${game_frameworks_SOURCE_DIR}/include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_GLEW_INCLUDE_DIRS}
        ${stb_INCLUDE_DIRS}
        ${fmt_INCLUDE_DIRS}
        )

target_link_libraries(gf_opengl game_frameworks
        opengl::opengl
        GLEW::GLEW)

#####
add_subdirectory(example)

if(RUN_TESTS)
    add_subdirectory(test)
endif()

