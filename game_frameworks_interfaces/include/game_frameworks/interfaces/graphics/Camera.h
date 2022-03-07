#ifndef GAME_FRAMEWORKS__CAMERATYPES_H
#define GAME_FRAMEWORKS__CAMERATYPES_H

#include <game_frameworks/interfaces/Common.h>
#include <game_frameworks/interfaces/maths/Geometry.h>

namespace game_frameworks {

    enum class UP_AXIS {
        NEGATIVE_Y = -1,
        POSITIVE_Y = 1
    };

    template<typename C>
    concept Camera2DConcept = requires(C camera) {
        { camera.position } -> Vector2;
        { camera.rotation } -> FloatingPointRef;
        { camera.zoom } -> FloatingPointRef;
    };

    template<typename VP>
    concept ViewportPropertiesConcept = requires(VP viewport) {
        { viewport.size } -> Vector2;
        { viewport.up } -> std::same_as<UP_AXIS&>;
    };

}

#endif //GAME_FRAMEWORKS__CAMERATYPES_H
