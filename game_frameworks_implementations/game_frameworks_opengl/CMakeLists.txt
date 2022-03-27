project(gf_opengl VERSION 0.1.0)

find_package(opengl_system)
find_package(GLEW)
find_package(glm)
find_package(stb)
find_package(fmt)
find_package(Freetype)

SET(gf_opengl_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(gf_opengl
        include/gf_opengl/opengl_render_api.h
        include/gf_opengl/camera.h
        include/gf_opengl/shader/shader.h
        include/gf_opengl/shader/shader_utils.h
        include/gf_opengl/font/font_loader.h
        src/opengl_render_api.cpp
        src/line_rendering.cpp
        src/quad_rendering.cpp
        src/sprite_rendering.cpp
        src/shader/shader_utils.cpp
        src/shader/shader.cpp
        src/texture.cpp
        src/font/font_loader.cpp
        include/gf_opengl/font/font_utils.h include/gf_opengl/font/font.h include/gf_opengl/common.h src/font/font.cpp src/font/font_util.cpp)
target_include_directories(gf_opengl PUBLIC
        ${gf_opengl_INCLUDE_DIRS}
        ${glm_INCLUDE_DIR}
        ${game_frameworks_SOURCE_DIR}/include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_GLEW_INCLUDE_DIRS}
        ${stb_INCLUDE_DIRS}
        ${fmt_INCLUDE_DIRS}
        ${freetype_INCLUDE_DIRS}
        )

target_link_libraries(gf_opengl game_frameworks
        opengl::opengl
        GLEW::GLEW
        Freetype::Freetype)

#####
add_subdirectory(example)

if(RUN_TESTS)
    add_subdirectory(test)
endif()

