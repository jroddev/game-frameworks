#ifndef GAME_FRAMEWORKS_SPRITE_H
#define GAME_FRAMEWORKS_SPRITE_H

#include <concepts>
#include <game_frameworks/interfaces/maths/Geometry.h>
#include <game_frameworks/interfaces/utils/EntityIdentifier.h>

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

    template<typename S>
    concept SpriteInstanceConcept = requires(S sprite) {
        { sprite.pivotPointOffset} -> Vector2;
        { sprite.size } -> Vector2;
        { sprite.textureRegion } -> Vector4;
        { sprite.colorTint } -> Vector4;
        { sprite.modelMatrix } -> Matrix4x4;
    };

    template<typename I>
    concept SpriteInstanceIterableConcept = requires(I i, int index) {
        {i[index] } -> SpriteInstanceConcept;
    };

}

#endif //GAME_FRAMEWORKS_SPRITE_H
