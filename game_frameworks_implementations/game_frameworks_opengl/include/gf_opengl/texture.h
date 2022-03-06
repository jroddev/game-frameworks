#ifndef GAME_FRAMEWORKS_OPENGL__TEXTURE_H
#define GAME_FRAMEWORKS_OPENGL__TEXTURE_H

#include <string>
#include <glm/glm.hpp>
#include "game_frameworks/utils/entity_identifier.h"

namespace game_frameworks {

    using OpenGLTexture = unsigned int;

    class Texture {
    public:
        using TextureMap = std::unordered_map<const EntityIdentifier, Texture, EntityIdentifier::Hasher, EntityIdentifier::Compare>;
        explicit Texture(std::string_view textureFileName);
        Texture(OpenGLTexture openGlTexture, glm::ivec2 size, int colorChannels);

        int width;
        int height;
        int colorChannels{};
        unsigned int textureId{}; // opengl resource id
        void bind() const;
    };

    const Texture& tryLoadTexture(const EntityIdentifier& textureId, const Texture::TextureMap& textures);

}
#endif