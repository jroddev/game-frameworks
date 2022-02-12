project(gf_sdl2 VERSION 0.1.0)

find_package(opengl_system)
find_package(GLEW)

# SDL2 takes 15-20 minutes to build on GitHub with Conan recipe
# Conan version also installs some system packages that are hard
# to cache.
# Use FetchContent instead
FetchContent_Declare(
        sdl2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.0.20
)
FetchContent_MakeAvailable(sdl2)

add_library(gf_sdl2
        include/gf_sdl2_window/sdl2_opengl_window.h
        src/sdl2_opengl_window.cpp
        )
target_include_directories(gf_sdl2 PUBLIC
        include
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${sdl2_SOURCE_DIR}/include
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        )

target_link_libraries(gf_sdl2 game_frameworks)
target_link_libraries(gf_sdl2 opengl::opengl)
target_link_libraries(gf_sdl2 GLEW::GLEW)
target_link_libraries(gf_sdl2 SDL2::SDL2)


#####
add_subdirectory(example)