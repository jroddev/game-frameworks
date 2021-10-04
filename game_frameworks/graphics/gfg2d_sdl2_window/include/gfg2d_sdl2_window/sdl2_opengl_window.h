#ifndef GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
#define GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H

#include <GL/glew.h>
#include "SDL.h"
#include <string>
#include <stdexcept>
#include <SDL_opengl.h>

class SDL2OpenglWindow {
public:
    struct initialisation_error: public std::runtime_error{
        using std::runtime_error::runtime_error ;
    };
    struct InitProperties {
        int width;
        int height;
        int openglMajorVersion;
        int openglMinorVersion;
        std::string windowTitle;
    };

    explicit SDL2OpenglWindow(const InitProperties&& properties);
    ~SDL2OpenglWindow();
    void pollEvents();
    void swapBuffers();
    bool shouldClose = false;

private:
    SDL_Window *window;
    SDL_GLContext glContext;

};

#endif //GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
