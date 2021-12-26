#ifndef GAME_FRAMEWORKS_VERTEX_H
#define GAME_FRAMEWORKS_VERTEX_H

#include <glm/glm.hpp>

namespace game_frameworks {
    struct Vertex {
        glm::vec2 position;
        glm::vec2 textureCoords;
    };
}

#endif //GAME_FRAMEWORKS_VERTEX_H
