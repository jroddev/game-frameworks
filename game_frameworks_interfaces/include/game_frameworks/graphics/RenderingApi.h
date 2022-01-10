#ifndef GAME_FRAMEWORKS_RENDERINGAPI_H
#define GAME_FRAMEWORKS_RENDERINGAPI_H

#include <game_frameworks/maths/Geometry.h>
#include <game_frameworks/graphics/Line.h>
#include <game_frameworks/graphics/Sprite.h>
#include <game_frameworks/graphics/Quad.h>
#include <game_frameworks/graphics/Camera.h>

namespace game_frameworks {

    template<typename Renderer>
    concept RenderingApi =
            Camera2DConcept<typename Renderer::CameraType> &&
            ViewportPropertiesConcept<typename Renderer::ViewportType> &&
            LineConcept<typename Renderer::LineType> &&
            QuadConcept<typename Renderer::QuadType> &&
            TransformConcept<typename Renderer::TransformType> &&
            requires(
                Renderer renderer,
                typename Renderer::CameraType camera,
                typename Renderer::ViewportType viewport,
                typename Renderer::LineType line,
                typename Renderer::QuadType quad,
                typename Renderer::TransformType transform,
                float lineWidth
            ) {
        { renderer.setCamera(camera, viewport ) } -> std::same_as<void>;
        { renderer.draw(line, lineWidth) } -> std::same_as<void>;
        { renderer.drawWireframe(quad, transform, lineWidth) } -> std::same_as<void>;
    };

}

#endif //GAME_FRAMEWORKS_RENDERINGAPI_H
