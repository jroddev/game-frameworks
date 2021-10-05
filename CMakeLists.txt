cmake_minimum_required(VERSION 3.0)
project(game_frameworks VERSION 0.1.0)

include(GoogleTest)
enable_testing()

add_subdirectory(game_frameworks_implementations/game_frameworks_sdl2)

add_subdirectory(games/tic_tac_toe)