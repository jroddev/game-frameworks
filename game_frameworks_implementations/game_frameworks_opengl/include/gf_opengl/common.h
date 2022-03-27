#ifndef GAME_FRAMEWORKS_COMMONA_H
#define GAME_FRAMEWORKS_COMMONA_H

#include <glm/glm.hpp>
#include "gf_opengl/mesh/mesh_quad.h"
#include "gf_opengl/mesh/mesh_uploader.h"

namespace game_frameworks {

    struct PerInstanceData {
        glm::vec2 pivotPointOffset;
        glm::vec2 size;
        glm::vec4 textureRegion;
        glm::vec4 colorTint;
        glm::mat4 modelMatrix;
    };

    struct PerFrameData {
        glm::mat4 view;
        glm::mat4 projection;
    };


    struct Line {
        glm::vec2 start;
        glm::vec2 end;
        glm::vec4 color;
    };

    struct Sprite {
        glm::vec2 pivotPointOffset;
        glm::vec2 size;

        EntityIdentifier textureId;
        glm::vec4 textureColorTint;
        glm::vec2 textureRegionOffset;
        glm::vec2 textureRegionSize;
    };

    struct Quad {
        glm::vec2 pivotPointOffset;
        glm::vec2 size;
        glm::vec4 color;
    };

    inline auto uploadQuadMesh() {
        return uploadMeshToOpenGL(
                centered_unit_quad::vertices,
                centered_unit_quad::indices,
                centered_unit_quad::stride,
                centered_unit_quad::textureCoordIndexOffset);
    }
}

#endif //GAME_FRAMEWORKS_COMMONA_H
