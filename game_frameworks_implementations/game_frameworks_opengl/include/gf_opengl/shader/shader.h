
#ifndef GAME_FRAMEWORKS_OPENGL__SHADER_H
#define GAME_FRAMEWORKS_OPENGL__SHADER_H

#include <string_view>

namespace game_frameworks {
    struct Shader {
        Shader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc);
        Shader(const Shader&) = delete;
        Shader(Shader&&) = default;
        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = default;
        ~Shader();

        // Clang-Tidy: 'operator unsigned int' must be marked explicit to avoid unintentional implicit conversions
        // NOLINTNEXTLINE
        explicit operator uint32_t() const;

    private:
        unsigned int shaderProgram;
    };
}

#endif //GAME_FRAMEWORKS_OPENGL__SHADER_H
