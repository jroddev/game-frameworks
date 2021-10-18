#include "spdlog/spdlog.h"

#include "gf_sdl2_window/sdl2_opengl_window.h"

int main() {
    spdlog::info("Starting");
    try {
        RenderingSurfaceApi auto window = SDL2OpenglWindow({
            .width = 512,
            .height = 512,
            .openglMajorVersion = 4,
            .openglMinorVersion = 6,
            .windowTitle = "Game Frameworks OpenGL Example"
        });

        while(!window.shouldClose()) {
            window.pollEvents();
            glClearColor(0.5f, 0.5f, 0.5f, 1.f);
            glClear(GL_COLOR_BUFFER_BIT);
            window.swapBuffers();
        }
    } catch (const SDL2OpenglWindow::initialisation_error& init_error) {
        spdlog::error("Intitialisation Exception Caught: {}", init_error.what());
    } catch (const std::exception& ex) {
        spdlog::error("Exception Caught: {}", ex.what());
    }
    spdlog::info("Shutting Down");
    return 0;
}
