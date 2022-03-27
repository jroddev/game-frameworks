#include "gf_opengl/font/font_utils.h"

namespace game_frameworks::font {

    PerInstanceData characterDatatoInstanceData(const PerCharacterData &character) {
        return {
                .pivotPointOffset=quad_pivot_offset::TOP_LEFT,
                .size=character.size,
                .textureRegion=character.textureRegion,
                .colorTint=glm::vec4{0.F, 1.F, 0.F, 1.F},
                .modelMatrix=character.modelMatrix
        };
    }

    std::vector<PerInstanceData> convertTextToInstancedSprites(
            const Font &font,
            const std::string_view text,
            const float boundingBoxWidth) {

        float x = 0.F;
        float y = 0.F;
        const auto textToCharacterData = [&font, &x, &y, &boundingBoxWidth](auto c) {
            const auto cleanedChar = c == '\n' ? ' ' : c;
            const auto cd = font.characters.at(cleanedChar);
            const auto output = PerCharacterData{
                    .size={cd.size},
                    .textureRegion={cd.textureRegion},
                    .modelMatrix={Transform::from(
                            x + static_cast<float>(cd.bearing.x),
                            y - static_cast<float>(cd.bearing.y + font.size),
                            0.F, 1.F, 1.F
                    ).toMatrix()}
            };

            // Advance position for the next character
            // Bitshift by 6 to get value in pixels (2^6 = 64)
            x += static_cast<float>(cd.advance >> 6);

            // Wrap to next line if required
            if (c == '\n' || (x > boundingBoxWidth && c == ' ')) {
                x = 0;
                y += static_cast<float>(font.size);
            }

            return output;
        };

        using std::ranges::views::transform;
        const auto characters = text
                                | transform(textToCharacterData)
                                | transform(characterDatatoInstanceData);
        return {characters.begin(), characters.end()};
    }

}