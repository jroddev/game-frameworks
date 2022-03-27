#ifndef GAME_FRAMEWORKS_INTERFACE_FONT_H
#define GAME_FRAMEWORKS_INTERFACE_FONT_H

#include <concepts>
#include <game_frameworks/interfaces/maths/Geometry.h>
#include <game_frameworks/interfaces/utils/EntityIdentifier.h>

namespace game_frameworks {

    template<typename F>
    concept FontConcept = requires(F font, std::string s, float f) {
        { font.id } -> EntityIdentifierConceptRef;
        { font.name } -> std::same_as<std::string&>;
        { font.size } -> IntegralRef;
        { font.generateSprites(s, f) } -> SpriteInstanceIterableConcept;
    };

    template<typename ID>
    concept FontConceptRef = requires {
        FontConcept <std::remove_reference<ID>>;
    };
}


#endif //GAME_FRAMEWORKS_INTERFACE_FONT_H
