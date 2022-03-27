#ifndef EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H
#define EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H

#include "gf_opengl/texture.h"
#include "gf_opengl/font/font.h"

#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>


namespace game_frameworks::font {

    std::tuple<Font, Texture> loadFontFromFile(std::string_view fontFilePath, int fontPixelSize = 48);
}
#endif
