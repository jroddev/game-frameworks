#include "spdlog/spdlog.h"

#include "gf_sdl2_window/sdl2_opengl_window.h"
#include "gf_opengl/opengl_render_api.h"

void run(
        game_frameworks::RenderingSurfaceApi auto& window,
        game_frameworks::RenderingApi auto& renderer
        ) {
    const auto pixelPerfectCamera = Camera2D{
            .position = {256, -256},
            .zoom=1.F
    };
    const auto viewport = ViewportProperties{
            .size={512,512},
            .up=game_frameworks::UP_AXIS::NEGATIVE_Y
    };
    renderer.setCamera(pixelPerfectCamera, viewport);

    while(!window.shouldClose()) {
        window.pollEvents();
        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw line/s
        renderer.drawLine({
            .start=glm::vec2{0.F, 256.F},
            .end=glm::vec2{512.F, 256.F},
            .color=glm::vec4{1.F, 0.F, 0.F, 1.F}
        }, 1.F);
        renderer.drawLine({
            .start=glm::vec2{256.F, 0.F},
            .end=glm::vec2{256.F, 512.F},
            .color=glm::vec4{0.F, 1.F, 0.F, 1.F}
        }, 1.F);

        // draw sprite/s

        // draw text

        window.swapBuffers();
    }
}


int main() {
    spdlog::info("Starting");
    try {
        game_frameworks::RenderingSurfaceApi auto window = SDL2OpenglWindow({
               .width = 512,
               .height = 512,
               .openglMajorVersion = 4,
               .openglMinorVersion = 6,
               .windowTitle = "Game Frameworks OpenGL Example"
        });
        game_frameworks::RenderingApi auto renderer = OpenGL_RenderApi{};
        run(window, renderer);

    } catch (const SDL2OpenglWindow::initialisation_error& init_error) {
        spdlog::error("Intitialisation Exception Caught: {}", init_error.what());
    } catch (const std::exception& ex) {
        spdlog::error("Exception Caught: {}", ex.what());
    }
    spdlog::info("Shutting Down");
    return 0;
}
