#include "gtest/gtest.h"
#include "dummy/dummy.h"
#include <gf_opengl/texture.h>
#include <glm/glm.hpp>

template<>
game_frameworks::Texture dummy(){
    return {
            dummy<unsigned int>(),
            glm::ivec2(dummy<unsigned int>(), dummy<unsigned int>()),
            dummy<int>()
    };
}