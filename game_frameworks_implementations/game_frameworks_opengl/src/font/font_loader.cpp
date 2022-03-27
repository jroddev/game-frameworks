#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include <utility>
#include <fmt/format.h>
#include "spdlog/spdlog.h"

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include "gf_opengl/font/font_loader.h"


// https://learnopengl.com/In-Practice/Text-Rendering

namespace game_frameworks::font {

    using CharacterRange = std::pair<unsigned int, unsigned int>; // 0 -> 128

    // pixel coord to [0,1] normalised texture coord within atlas
    glm::vec4 getTextureRegion(const glm::ivec2 atlasSize, uint leftPixelPosition, uint rightPixelPosition, uint pixelHeight) {
        const auto a = float(leftPixelPosition) / float(atlasSize.x);
        const auto b = float(rightPixelPosition) / float(atlasSize.x);
        const auto x = a;
        const auto y = 0.F;
        const auto width = b-a;
        const auto height = float(pixelHeight) / float(atlasSize.y);
        return {x,y,width,height};
    }

    glm::ivec2 getTextureAtlasSize(const FT_Face &face, const CharacterRange range) {
        auto textureWidth = 0u;
        auto textureHeight = 0u;

        for (auto c = range.first; c < range.second; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                spdlog::warn("FREETYTPE::getTextureAtlasSize Failed to load Glyph for code: {}", c);
                continue;
            }
            textureWidth += face->glyph->bitmap.width;
            textureHeight = std::max(textureHeight, face->glyph->bitmap.rows);
        }

        return {textureWidth, textureHeight};
    }

    GLuint createEmptyTextureAtlas(const glm::ivec2 atlasSize) {
        GLuint texture;
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                atlasSize.x,
                atlasSize.y,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                nullptr // Will fill pixels later
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        return texture;
    }

    GLuint buildTextureAtlas(const FT_Face &face, const CharacterRange range, const glm::ivec2 atlasSize) {
        const auto texture = createEmptyTextureAtlas(atlasSize);
        auto xOffset = 0u;
        for (auto c = range.first; c < range.second; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                spdlog::warn("FREETYTPE::buildTextureAtlas Failed to load Glyph for code: {}", c);
                continue;
            }

            const auto& bitmap = face->glyph->bitmap;
            const auto bufferSize = bitmap.width*bitmap.rows;
            auto rgba = std::vector<unsigned char>();
            rgba.reserve(bufferSize*4);
            for(int i = 0; i < bufferSize; i++) {
                rgba.emplace_back(255);
                rgba.emplace_back(255);
                rgba.emplace_back(255);
                rgba.emplace_back(bitmap.buffer[i]);
            }

            glTexSubImage2D(
                    GL_TEXTURE_2D,
                    0,
                    static_cast<GLint>(xOffset),
                    0,
                    static_cast<GLsizei>(face->glyph->bitmap.width),
                    static_cast<GLsizei>(face->glyph->bitmap.rows),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    rgba.data());
            xOffset += face->glyph->bitmap.width;
        }
        return texture;
    }


    Font::CharacterInfoMap getCharacterInfo(const FT_Face &face, const CharacterRange range, const glm::ivec2 atlasSize) {
        Font::CharacterInfoMap characters;
        uint xPixelPos = 0;
        for (auto c = range.first; c < range.second; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                spdlog::warn("FREETYTPE::getCharacterInfo Failed to load Glyph for code: {}", c);
                continue;
            }

            const auto pixelSize = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
            const auto textureRegion = getTextureRegion(atlasSize, xPixelPos, xPixelPos + pixelSize.x, pixelSize.y);
            const auto info = Font::CharacterInfo{
                    .textureRegion = textureRegion,
                    .size = pixelSize,
                    .bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    .advance = static_cast<unsigned int>(face->glyph->advance.x)
            };
            characters.try_emplace(c, info);
            xPixelPos += pixelSize.x;
        }
        return characters;
    }


    std::tuple<Font, Texture> loadFontFromFile(std::string_view fontFilePath, int fontPixelSize) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            spdlog::error("FREETYPE::loadFromFontFile Could not init FreeType Library");
            throw std::runtime_error("Could not init FreeType Library");
        }

        FT_Face face;
        if (FT_New_Face(ft, fontFilePath.data(), 0, &face)) {
            spdlog::error("FREETYPE::loadFromFontFile Failed to load font: {}", fontFilePath);
            throw std::runtime_error("Failed to load font");
        }

        // Set Font Size
        FT_Set_Pixel_Sizes(face, 0, fontPixelSize);

        const auto characterRange = CharacterRange{0, 128};
        const auto textureAtlasSize = getTextureAtlasSize(face, characterRange);
        const auto textureAtlas = buildTextureAtlas(face, characterRange, textureAtlasSize);
        const auto characters = getCharacterInfo(face, characterRange, textureAtlasSize);
        spdlog::info("{}: {}, {}", fontFilePath, textureAtlasSize.x, textureAtlasSize.y);

        FT_Done_Face(face);
        FT_Done_FreeType(ft);
//        glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // untested

        auto fontName = Font::getFontName(fontFilePath, fontPixelSize);
        auto font = Font{
                .name{fontName},
                .id{EntityIdentifier{fontName}},
                .characters{characters},
                .size = fontPixelSize
        };
        auto texture = Texture{textureAtlas, textureAtlasSize, 1};
        return {font, std::move(texture)};
    }
}