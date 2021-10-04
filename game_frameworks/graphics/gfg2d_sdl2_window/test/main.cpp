#include "gfg2d_sdl2_window/sdl2_opengl_window.h"
#include <thread>
#include "spdlog/spdlog.h"

using namespace std::chrono_literals;

int main() {
    spdlog::info("Starting");
    {
        try {
            auto window = SDL2OpenglWindow({
                                .width = 1280,
                                .height = 720,
                                .openglMajorVersion = 4,
                                .openglMinorVersion = 6,
                                .windowTitle = "Test Window"
                        });

            while(!window.shouldClose) {
                window.pollEvents();
                glClearColor(0.f, 0.f, 0.f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT);
                window.swapBuffers();
            }
        } catch (const SDL2OpenglWindow::initialisation_error& init_error) {
            spdlog::error("Intitialisation Exception Caught: {}", init_error.what());
        } catch (const std::exception& ex) {
            spdlog::error("Exception Caught: {}", ex.what());
        }
    }
    spdlog::info("Shutting Down");
}
