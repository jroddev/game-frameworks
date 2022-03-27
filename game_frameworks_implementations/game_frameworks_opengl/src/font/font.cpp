
#include "gf_opengl/font/font.h"
#include "gf_opengl/font/font_utils.h"

#include <spdlog/spdlog.h>
#include <fmt/format.h>

namespace game_frameworks {

    std::string Font::getFontName(std::string_view fontFilePath, int fontSize){
        return fmt::format("{}:{}", fontFilePath, fontSize);
    }

    std::vector<PerInstanceData> Font::generateSprites(std::string_view text, float boundingBoxWidth) const {
        return font::convertTextToInstancedSprites(*this, text, boundingBoxWidth);
    }
}