#ifndef GAME_FRAMEWORKS_RENDERINGAPI_H
#define GAME_FRAMEWORKS_RENDERINGAPI_H

#include <game_frameworks/maths/Geometry.h>
#include <game_frameworks/graphics/Line.h>
#include <game_frameworks/graphics/Sprite.h>
#include <game_frameworks/graphics/Camera.h>

namespace game_frameworks {

    template<typename Renderer>
    concept RenderingApi =
            Camera2DConcept<typename Renderer::CameraType> &&
            ViewportPropertiesConcept<typename Renderer::ViewportType> &&
            LineConcept<typename Renderer::LineType> &&
            requires(
                Renderer renderer,
                typename Renderer::CameraType camera,
                typename Renderer::ViewportType viewport,
                typename Renderer::LineType line,
                float f
            ) {
        { renderer.setCamera(camera, viewport ) } -> std::same_as<void>;
        { renderer.drawLine(line, f) } -> std::same_as<void>;
    };

}

#endif //GAME_FRAMEWORKS_RENDERINGAPI_H
