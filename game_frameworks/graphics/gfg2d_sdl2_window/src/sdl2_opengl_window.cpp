#include "gfg2d_sdl2_window/sdl2_opengl_window.h"
#include <string>
#include <stdexcept>
#include "spdlog/spdlog.h"


SDL2OpenglWindow::SDL2OpenglWindow(const SDL2OpenglWindow::InitProperties&& properties) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        spdlog::error("Unable to initialize SDL2.");
        throw initialisation_error("Unable to initialize SDL2.");
    }
    window = SDL_CreateWindow(
            properties.windowTitle.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            properties.width,
            properties.height,
            SDL_WINDOW_OPENGL
    );

    // Check that the window was successfully created
    if (window == nullptr) {
        spdlog::error("Could not create window: %s\n", SDL_GetError());
        throw initialisation_error(std::string{"Failed to create SDL2 Window"});
    }
}

SDL2OpenglWindow::~SDL2OpenglWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}