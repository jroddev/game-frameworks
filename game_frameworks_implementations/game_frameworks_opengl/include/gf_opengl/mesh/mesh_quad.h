#ifndef GAME_FRAMEWORKS_MESH_QUAD_H
#define GAME_FRAMEWORKS_MESH_QUAD_H

#include <gf_opengl/mesh/vertex.h>
#include <array>
#include <glm/glm.hpp>

namespace game_frameworks {

    namespace centered_unit_quad {
        constexpr const auto vertices = std::array<Vertex, 4>{
                // positions            // texture coords
                Vertex{{0.5F, 0.5F},
                       {1.0F, 1.0F}},   // top right
                Vertex{{0.5F, -0.5F},
                       {1.0F, 0.0F}},   // bottom right
                Vertex{{-0.5F, -0.5F},
                       {0.0F,  0.0F}},   // bottom left
                Vertex{{-0.5F, 0.5F},
                       {0.0F,  1.0F}}    // top left
        };
        constexpr const auto verticesIndexOffset = 0;
        constexpr const auto textureCoordIndexOffset = 2;

        constexpr const auto indices = std::array<int, 6>{
                0, 1, 3,   // first triangle
                1, 2, 3    // second triangle
        };

        constexpr const auto stride = sizeof(Vertex);
    }

    namespace quad_pivot_offset {
        static const float LEFT = 0.5F;
        static const float RIGHT = -0.5F;
        static const float TOP = 0.5F;
        static const float BOTTOM = -0.5F;
        static const glm::vec2 CENTER = glm::vec2{0.F, 0.F};            // NOLINT
        static const glm::vec2 TOP_LEFT = glm::vec2{LEFT, TOP};         // NOLINT
        static const glm::vec2 TOP_RIGHT = glm::vec2{RIGHT, TOP};       // NOLINT
        static const glm::vec2 BOTTOM_LEFT = glm::vec2{LEFT, BOTTOM};   // NOLINT
        static const glm::vec2 BOTTOM_RIGHT = glm::vec2{RIGHT, BOTTOM}; // NOLINT
    }

}

#endif //GAME_FRAMEWORKS_MESH_QUAD_H
