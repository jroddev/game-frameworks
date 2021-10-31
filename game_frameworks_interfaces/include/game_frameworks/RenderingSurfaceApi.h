#ifndef GAME_FRAMEWORKS_RENDERINGSURFACE_H
#define GAME_FRAMEWORKS_RENDERINGSURFACE_H

namespace game_frameworks {

    template<typename T>
    concept RenderingSurfaceApi = requires(T surface, int value) {
        { surface.pollEvents() };
        { surface.swapBuffers() };
        { surface.shouldClose() } ->  std::same_as<bool>;
    };

}

#endif //GAME_FRAMEWORKS_RENDERINGSURFACE_H
