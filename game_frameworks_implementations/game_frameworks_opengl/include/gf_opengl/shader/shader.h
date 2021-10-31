
#ifndef GAME_FRAMEWORKS_OPENGL__SHADER_H
#define GAME_FRAMEWORKS_OPENGL__SHADER_H

#include <string_view>

namespace game_frameworks {
    struct shader {
        shader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc);

        ~shader();

        // Clang-Tidy: 'operator unsigned int' must be marked explicit to avoid unintentional implicit conversions
        // NOLINTNEXTLINE
        operator unsigned int() const;

    private:
        unsigned int shaderProgram;
    };
}

#endif //GAME_FRAMEWORKS_OPENGL__SHADER_H
