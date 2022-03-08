project(game_frameworks VERSION 0.1.0)

find_package(spdlog)

SET(game_frameworks_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(game_frameworks src/utils/filename_cache.cpp)
target_include_directories(game_frameworks PUBLIC
        ${game_frameworks_INCLUDE_DIRS}
        ${game-frameworks-interfaces_SOURCE_DIR}/include
        ${spdlog_INCLUDE_DIR}/include
        )
target_link_libraries(game_frameworks spdlog::spdlog)


if(RUN_TESTS)
    add_subdirectory(test)
endif()
