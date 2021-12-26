#ifndef GAME_FRAMEWORKS_QUAD_H
#define GAME_FRAMEWORKS_QUAD_H

#include <concepts>
#include <game_frameworks/maths/Geometry.h>

namespace game_frameworks {

    template<typename Q>
    concept QuadConcept = requires(Q quad) {
        { quad.pivotPointOffset} -> Vector2;
        { quad.size } -> Vector2;
        { quad.color } -> Vector4;
    };
}

#endif //GAME_FRAMEWORKS_QUAD_H
