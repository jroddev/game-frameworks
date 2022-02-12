project(gf_opengl VERSION 0.1.0)

find_package(opengl_system)
find_package(glm)

add_library(gf_opengl
        include/gf_opengl/opengl_render_api.h
        include/gf_opengl/camera.h
        include/gf_opengl/shader/shader.h
        include/gf_opengl/shader/shader_utils.h
        src/opengl_render_api.cpp
        src/line_rendering.cpp
        src/quad_rendering.cpp
        src/shader/shader_utils.cpp
        src/shader/shader.cpp
        )
target_include_directories(gf_opengl PUBLIC
        include
        ${glm_INCLUDE_DIR}
        ${game_frameworks_SOURCE_DIR}/include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
        )

target_link_libraries(gf_opengl game_frameworks opengl::opengl)

#####
add_subdirectory(example)
