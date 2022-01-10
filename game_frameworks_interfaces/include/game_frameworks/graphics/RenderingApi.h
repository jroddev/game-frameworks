#ifndef GAME_FRAMEWORKS_RENDERINGAPI_H
#define GAME_FRAMEWORKS_RENDERINGAPI_H

#include <game_frameworks/maths/Geometry.h>
#include <game_frameworks/graphics/Line.h>
#include <game_frameworks/graphics/Sprite.h>
#include <game_frameworks/graphics/Quad.h>
#include <game_frameworks/graphics/Camera.h>
#include <game_frameworks/utils/FunctionTraits.h>



namespace game_frameworks {

    template<typename Renderer>
    concept RenderingApi =
            LineConcept<typename Renderer::LineType> &&
            QuadConcept<typename Renderer::QuadType> &&
            TransformConcept<typename Renderer::TransformType> &&
            requires(
                Renderer renderer,
                typename function_param_type<1, decltype(&Renderer::setCamera)>::type camera,
                typename function_param_type<2, decltype(&Renderer::setCamera)>::type viewport,

                typename Renderer::TransformType transform,
                typename Renderer::LineType line,
                typename Renderer::QuadType quad,
                float lineWidth
            ) {
        { camera } -> Camera2DConcept;
        { stripConst(viewport)} -> ViewportPropertiesConcept;
        { renderer.setCamera(camera, viewport ) } -> std::same_as<void>;
        { renderer.draw(line, lineWidth) } -> std::same_as<void>;
        { renderer.draw(quad, transform) } -> std::same_as<void>;
        { renderer.drawWireframe(quad, transform, lineWidth) } -> std::same_as<void>;
    };

}

#endif //GAME_FRAMEWORKS_RENDERINGAPI_H
