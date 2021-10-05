#include "gfg2d_sdl2_window/sdl2_opengl_window.h"
#include <string>
#include <bit>
#include "spdlog/spdlog.h"


SDL2OpenglWindow::SDL2OpenglWindow(const SDL2OpenglWindow::InitProperties&& properties) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        throw initialisation_error("Unable to initialize SDL2.");
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, properties.openglMajorVersion);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, properties.openglMinorVersion);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, GL_TRUE);
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
        throw initialisation_error(std::string{"Could not create window: %s\n", SDL_GetError()});
    }

    glContext = SDL_GL_CreateContext(window);
    if(!glContext){
        throw initialisation_error(std::string{"OpenGL context could not be created! SDL Error: {}", SDL_GetError()});
    }

    //Initialize GLEW
    glewExperimental = GL_TRUE;
    if( GLenum glewError = glewInit() != GLEW_OK ){
        throw initialisation_error(
                std::string{"Error initializing GLEW: "} +
                std::bit_cast<const char *>(glewGetErrorString(glewError)));
    }

    //Use Vsync
    if( SDL_GL_SetSwapInterval( 1 ) < 0 ){
        spdlog::warn( "Unable to set VSync! SDL Error: {}", SDL_GetError() );
    }
}

SDL2OpenglWindow::~SDL2OpenglWindow() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDL2OpenglWindow::swapBuffers() {
    SDL_GL_SwapWindow(window);
}

void SDL2OpenglWindow::pollEvents() {
    SDL_Event event;
    while( SDL_PollEvent(&event) != 0 ){
        if(event.type == SDL_QUIT ) {
            _shouldClose = true;
        }
    }
}
