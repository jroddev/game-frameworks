include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(game-frameworks-interfaces
        VERSION 0.1.0
        LANGUAGES CXX
        DESCRIPTION "Small header-only extensible 2D rendering interface."
        HOMEPAGE_URL "https://github.com/jroddev/game-frameworks")

add_library(${PROJECT_NAME} INTERFACE include/game_frameworks/utils/EntityIdentifier.h)
set(BUILD_FLAGS "${BUILD_FLAGS} -Wall -Wextra -pedantic")
# Warnings as Errors
set(BUILD_FLAGS "${BUILD_FLAGS} -Werror")


target_include_directories(
        ${PROJECT_NAME}
        INTERFACE $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}_Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

install(EXPORT ${PROJECT_NAME}_Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}/cmake)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/game-frameworks-interfaces_main DESTINATION include)


# game_frameworks_interfaces_main is just used for compiler errors
add_library(game_frameworks_interfaces_main main.cpp)

set_target_properties(game_frameworks_interfaces_main PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
target_include_directories(game_frameworks_interfaces_main PRIVATE include)