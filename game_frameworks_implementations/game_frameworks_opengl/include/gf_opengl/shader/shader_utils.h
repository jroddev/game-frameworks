#ifndef GAME_FRAMEWORKS_OPENGL___SHADERUTILS_H
#define GAME_FRAMEWORKS_OPENGL___SHADERUTILS_H

#include <string>
#include <stdexcept>

namespace game_frameworks::shader_utils {
    enum class SHADER_TYPE {
        VERT,
        FRAG
    };

    struct shader_build_exception : public std::runtime_error {
        using runtime_error::runtime_error;
    };

    uint32_t compile(const std::string& src, SHADER_TYPE shaderType);
    uint32_t link(const uint32_t& vertexShader, const uint32_t& fragmentShader);
};

#endif