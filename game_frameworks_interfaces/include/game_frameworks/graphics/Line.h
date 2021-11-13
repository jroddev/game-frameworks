#ifndef GAME_FRAMEWORKS_LINE_H
#define GAME_FRAMEWORKS_LINE_H

#include <concepts>
#include <game_frameworks/maths/Geometry.h>
#include <game_frameworks/Common.h>

namespace game_frameworks {

    template<typename L>
    concept LineConcept = requires(L line) {
        { line.start} -> Vector2;
        { line.end } -> Vector2;
        { line.color } -> Vector4;
    };
}

#endif //GAME_FRAMEWORKS_LINE_H
