#include "gtest/gtest.h"
#include "dummy/dummy.h"
#include <gf_opengl/texture.h>

using game_frameworks::Texture;
using game_frameworks::tryLoadTexture;


TEST(GF_OpenGL, tryLoadTextureSuccessReturnsTexture) {
    const auto textureKey = dummy<game_frameworks::EntityIdentifier>();
    const auto texture = dummy<Texture>();
    auto textures = Texture::TextureMap{};
    textures.try_emplace(textureKey, texture);
    const auto result = tryLoadTexture(textureKey, textures);
    EXPECT_EQ(result.textureId, texture.textureId);
}

TEST(GF_OpenGL, tryLoadTextureFailureThrows) {
    const auto textureKey = dummy<game_frameworks::EntityIdentifier>();
    auto textures = Texture::TextureMap{};

    EXPECT_THROW(tryLoadTexture(textureKey, textures), std::out_of_range);
}