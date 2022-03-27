#ifndef GAME_FRAMEWORKS_FONT_H
#define GAME_FRAMEWORKS_FONT_H

#include "game_frameworks/utils/entity_identifier.h"
#include "gf_opengl/common.h"
#include "gf_opengl/texture.h"

namespace game_frameworks {

    struct Font {
        struct CharacterInfo {
            glm::vec4 textureRegion;
            glm::ivec2 size;        // size of glyph in pixels
            glm::ivec2 bearing;     // offset from baseline to left/top of glyph
            unsigned int advance;   // offset to advance to next glyph
        };
        using CharacterInfoMap = std::unordered_map<char, CharacterInfo>;
        using FontMap = std::unordered_map<const EntityIdentifier, Font, EntityIdentifier::Hasher, EntityIdentifier::Compare>;

        std::string name;
        EntityIdentifier id;
        CharacterInfoMap characters;
        int size;

        static std::string getFontName(std::string_view fontFilePath, int fontSize);
        std::vector<PerInstanceData> generateSprites(std::string_view text, float boundingBoxWidth) const;
    };

}

#endif //GAME_FRAMEWORKS_FONT_H
