#include "gfg2d_sdl2_window/sdl2_opengl_window.h"
#include <thread>
#include <chrono>
#include "spdlog/spdlog.h"

using namespace std::chrono_literals;

int main() {
    spdlog::info("Starting");
    {
        auto windows = SDL2OpenglWindow({
            1280, 720, "Test Window"
        });
        std::this_thread::sleep_for(5s);
    }
    spdlog::info("Shutting Down");
    std::this_thread::sleep_for(1s);
}
