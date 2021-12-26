#ifndef GAME_FRAMEWORKS_MESH_PROPERTIES_H
#define GAME_FRAMEWORKS_MESH_PROPERTIES_H

#include <GL/glew.h>

namespace game_frameworks {
    struct OpenGLMeshProperties {
        GLuint vao, vbo, ebo;
        int indicesSize;
    };
}

#endif //GAME_FRAMEWORKS_MESH_PROPERTIES_H
