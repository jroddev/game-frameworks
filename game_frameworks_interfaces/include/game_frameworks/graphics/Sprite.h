#ifndef GAME_FRAMEWORKS_SPRITE_H
#define GAME_FRAMEWORKS_SPRITE_H

#include <concepts>
#include <game_frameworks/maths/Geometry.h>
#include <game_frameworks/utils/EntityIdentifier.h>

namespace game_frameworks {

    template<typename S>
    concept SpriteConcept = requires(S sprite) {
        { sprite.pivotPointOffset} -> Vector2;
        { sprite.size } -> Vector2;
        { sprite.textureId } -> EntityIdentifierConceptRef;
        { sprite.textureColorTint } -> Vector4;
        { sprite.textureRegionOffset } -> Vector2;
        { sprite.textureRegionSize } -> Vector2;
    };
}

#endif //GAME_FRAMEWORKS_SPRITE_H
