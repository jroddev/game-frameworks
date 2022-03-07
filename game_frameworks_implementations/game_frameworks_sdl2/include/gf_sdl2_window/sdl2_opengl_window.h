#ifndef GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
#define GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H

#include <GL/glew.h>
#include "SDL.h"
#include <string>
#include <stdexcept>
#include <SDL_opengl.h>
#include <game_frameworks/interfaces/RenderingSurfaceApi.h>

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
    SDL2OpenglWindow(const SDL2OpenglWindow&) = delete;
    SDL2OpenglWindow(SDL2OpenglWindow&&) = delete;
    SDL2OpenglWindow& operator=(const SDL2OpenglWindow&) = delete;
    SDL2OpenglWindow& operator=(SDL2OpenglWindow&&) = delete;

    ~SDL2OpenglWindow();
    void pollEvents();
    void swapBuffers();
    [[nodiscard]] bool shouldClose() const{return _shouldClose;}

private:
    SDL_Window *window;
    SDL_GLContext glContext;
    bool _shouldClose = false;
};

static_assert(game_frameworks::RenderingSurfaceApi<SDL2OpenglWindow>);

#endif //GAME_FRAMEWORKS_SDL2_OPENGL_WINDOW_H
