#ifndef GAME_FRAMEWORKS_FONT_UTILS_H
#define GAME_FRAMEWORKS_FONT_UTILS_H

#include "gf_opengl/opengl_render_api.h"
#include "gf_opengl/font/font_loader.h"

#include <array>
#include <ranges>

namespace game_frameworks::font {

    struct PerCharacterData {
        glm::vec2 size;
        glm::vec4 textureRegion;
        glm::mat4 modelMatrix;
    };

    PerInstanceData characterDatatoInstanceData(const PerCharacterData& character);
    std::vector<PerInstanceData> convertTextToInstancedSprites(
            const Font& font,
            const std::string_view text,
            const float boundingBoxWidth);
}
#endif //GAME_FRAMEWORKS_FONT_UTILS_H
