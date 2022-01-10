#ifndef GAME_FRAMEWORKS_SPRITE_H
#define GAME_FRAMEWORKS_SPRITE_H

#include <concepts>
#include <game_frameworks/maths/Geometry.h>

namespace game_frameworks {

    template<typename S>
    concept SpriteConcept = requires(S sprite) {
        { sprite.pivotPointOffset} -> Vector2;
        { sprite.size } -> Vector2;
        { sprite.textureTint } -> Vector4;
        { sprite.textureCoords } -> Rect;
    };

}

#endif //GAME_FRAMEWORKS_SPRITE_H
