#ifndef GAME_FRAMEWORKS_SPRITE_H
#define GAME_FRAMEWORKS_SPRITE_H

#include <concepts>
#include <game_frameworks/maths/Geometry.h>

namespace game_frameworks {

    template<typename S>
    concept Sprite = requires(S sprite) {
        { sprite.localTransform } -> Matrix4x4;
        { sprite.pivotPointOffset} -> Vector2;
        { sprite.size } -> Vector2;
        { sprite.textureCoords } -> Rect;
    };

}

#endif //GAME_FRAMEWORKS_SPRITE_H
