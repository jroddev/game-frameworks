#ifndef GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
#define GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H

#include "SDL.h"
#include <string>
#include <stdexcept>

class SDL2OpenglWindow {
    struct initialisation_error: public std::runtime_error{
        using std::runtime_error::runtime_error ;
    };
    struct InitProperties {
        int width;
        int height;
        std::string windowTitle;
    };

public:
    SDL2OpenglWindow(const InitProperties&& properties);
    ~SDL2OpenglWindow();

private:
    SDL_Window *window;
};

#endif //GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
