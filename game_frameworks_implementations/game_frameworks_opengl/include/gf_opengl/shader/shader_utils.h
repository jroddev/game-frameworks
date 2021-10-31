#ifndef GAME_FRAMEWORKS_OPENGL___SHADERUTILS_H
#define GAME_FRAMEWORKS_OPENGL___SHADERUTILS_H

#include <string>

namespace game_frameworks::shader_utils {
    enum class SHADER_TYPE {
        VERT,
        FRAG
    };

    unsigned int compile(const std::string& src, SHADER_TYPE shaderType);
    unsigned int  link(unsigned int &vertexShader, unsigned int &fragmentShader);
};

#endif