cmake_minimum_required(VERSION 3.0)
project(game_frameworks VERSION 0.1.0)

include(GoogleTest)
enable_testing()

add_subdirectory(game_frameworks/graphics/gfg2d_sdl2_window)

add_subdirectory(games/tic_tac_toe)