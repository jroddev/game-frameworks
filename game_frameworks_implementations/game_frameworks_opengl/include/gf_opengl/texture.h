#ifndef GAME_FRAMEWORKS_OPENGL__TEXTURE_H
#define GAME_FRAMEWORKS_OPENGL__TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include "game_frameworks/utils/entity_identifier.h"

namespace game_frameworks {

    using OpenGLTexture = unsigned int;

    struct texture_load_exception : public std::runtime_error {
        using runtime_error::runtime_error;
    };

    class Texture {
    public:
        using TextureMap = std::unordered_map<const EntityIdentifier, Texture, EntityIdentifier::Hasher, EntityIdentifier::Compare>;
        explicit Texture(std::string_view textureFileName);
        Texture(OpenGLTexture openGlTexture, glm::ivec2 size, int colorChannels);
        Texture(Texture&& other) noexcept;
        Texture operator=(Texture&& other) noexcept;
        Texture(const Texture& other) = delete;
        Texture operator=(const Texture& other) = delete;
        ~Texture();

        int width;
        int height;
        int colorChannels{};
        OpenGLTexture textureId{}; // opengl resource id
        void bind() const;

    private:
        bool hasOpenglResource = false;
    };

    const Texture& tryLoadTexture(const EntityIdentifier& textureId, const Texture::TextureMap& textures);

}
#endif