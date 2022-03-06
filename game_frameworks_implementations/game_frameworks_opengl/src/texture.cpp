#include <GL/glew.h>
#include <stdexcept>
#include "spdlog/spdlog.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "game_frameworks/utils/entity_identifier.h"
#include "gf_opengl/texture.h"

namespace game_frameworks {

    const Texture& tryLoadTexture(const EntityIdentifier& textureId, const Texture::TextureMap& textures) {
        try {
            return textures.at(textureId);
        } catch (const std::out_of_range& outOfRange) {
            spdlog::error(outOfRange.what());
            throw std::out_of_range(fmt::format("SpriteRenderer::Texture with ID:{} not found", textureId.hash));
        }
    }

    Texture::Texture(const std::string_view textureFileName): width(0), height(0) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        const auto data = stbi_load(
                textureFileName.data(),
                &width,
                &height,
                &colorChannels,
                0);

        if (data) {
            spdlog::info("Load Texture: {} [{}, {}] has {} channels", textureFileName, width, height, colorChannels);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        } else {
            stbi_image_free(data);
            throw std::runtime_error(fmt::format("Failed to load texture: {}", textureFileName));
        }

    }

    void Texture::bind() const {
        glBindTexture(GL_TEXTURE_2D, textureId);
    }

    Texture::Texture(OpenGLTexture openGlTexture, glm::ivec2 size, int colorChannels) :
            width(size.x),
            height(size.y),
            colorChannels(colorChannels),
            textureId(openGlTexture) {

    }

}

