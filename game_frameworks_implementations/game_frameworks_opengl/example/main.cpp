#include <filesystem>
#include <chrono>
#include "spdlog/spdlog.h"

#include "gf_sdl2_window/sdl2_opengl_window.h"
#include "gf_opengl/opengl_render_api.h"
#include "gf_opengl/mesh/mesh_quad.h"

using namespace game_frameworks;
using namespace std::chrono;

void run(
        RenderingSurfaceApi auto& window,
        RenderingApi auto& renderer
        ) {
    const auto pixelPerfectCamera = Camera2D{
            .position = {256, -256},
            .zoom=1.F
    };
    const auto viewport = ViewportProperties{
            .size={512,512},
            .up=UP_AXIS::NEGATIVE_Y
    };
    renderer.setCamera(pixelPerfectCamera, viewport);
    glClearColor(0.5f, 0.5f, 0.5f, 1.f);

    renderer.loadTexture("assets/textures/input_prompts.png");
    const auto inputPromptTexelSize = glm::vec2 {16.F/544.F, 16.F/384.F};

    while(!window.shouldClose()) {
        window.pollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // draw lines for screen center
        renderer.draw({
            .start=glm::vec2{0.F, 256.F},
            .end=glm::vec2{512.F, 256.F},
            .color=glm::vec4{1.F, 0.F, 0.F, 1.F}
        }, 1.F);
        renderer.draw({
            .start=glm::vec2{256.F, 0.F},
            .end=glm::vec2{256.F, 512.F},
            .color=glm::vec4{0.F, 1.F, 0.F, 1.F}
        }, 1.F);

        // draw origin lines
        renderer.draw({
            .start=glm::vec2{0.F, 0.F},
            .end=glm::vec2{100.F, 0.F},
            .color=glm::vec4{1.F, 0.F, 0.F, 1.F}
        }, 5.F);
        renderer.draw({
            .start=glm::vec2{0.F, 0.F},
            .end=glm::vec2{0.F, 100.F},
            .color=glm::vec4{0.F, 1.F, 0.F, 1.F}
        }, 5.F);


        // draw quad/s
        auto t = Transform{};
        t.position.x = viewport.size.x * 0.5F;
        t.position.y = viewport.size.y * 0.5F;
        renderer.draw(Quad{
                .pivotPointOffset=quad_pivot_offset::TOP_LEFT,
                .size={50.F, 50.F},
                .color={0.F, 1.F, 1.F, 1.F}
        }, t);

        renderer.draw(Quad{
                .pivotPointOffset=quad_pivot_offset::BOTTOM_RIGHT,
                .size={50.F, 50.F},
                .color={1.F, 1.F, 0.F, 1.F}
        }, t);


        renderer.drawWireframe(Quad{
                .pivotPointOffset=quad_pivot_offset::CENTER,
                .size={50.F, 50.F},
                .color={0.F, 0.F, 1.F, 1.F}
        }, t, 2.0F);

        // draw sprite/s
        // Loop through a set of sprites from atlas and adjust tint
        const auto time = steady_clock::now().time_since_epoch();
        const auto frame = duration_cast<seconds>(time).count() % 4;
        const auto tint = static_cast<float>(frame) / 4.F;
        const auto spritePosition = glm::vec2{ 1 + frame, 9 };
        renderer.draw(Sprite{
                .pivotPointOffset=quad_pivot_offset::TOP_LEFT,
                .size={16.F, 16.F},
                .textureId{EntityIdentifier("assets/textures/input_prompts.png")},
                .textureColorTint{1.F-tint, tint, 1.F, 0.8F},
                .textureRegionOffset{
                        (spritePosition.x) * inputPromptTexelSize.x,
                        (spritePosition.y-1) * inputPromptTexelSize.y
                },
                .textureRegionSize{inputPromptTexelSize.x, inputPromptTexelSize.y}
        }, Transform::from(100.F, 10.F, 0.F, 3.F, 3.F));

//        // draw text

        window.swapBuffers();
    }
}


int main() {
    spdlog::info("Starting");
    spdlog::info("Running from: {}", std::filesystem::current_path().string());
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
