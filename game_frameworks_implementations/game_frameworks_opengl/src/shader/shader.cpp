
#include <gf_opengl/shader/shader.h>
#include <gf_opengl/shader/shader_utils.h>
#include <GL/glew.h>
#include "spdlog/spdlog.h"

namespace game_frameworks {
    Shader::Shader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc) {
        spdlog::info("Compiling vertex shader for {}", name);
        const auto vertexShader = shader_utils::compile(vertexSrc, shader_utils::SHADER_TYPE::VERT);
        spdlog::info("Compiling fragment shader for {}", name);
        const auto fragmentShader = shader_utils::compile(fragmentSrc, shader_utils::SHADER_TYPE::FRAG);
        spdlog::info("linking shaders for {}", name);
        shaderProgram = shader_utils::link(vertexShader, fragmentShader);
        spdlog::info("shader {} loaded", name);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() {
        spdlog::info("destroy shader");
        glDeleteProgram(shaderProgram);
    }

    Shader::operator uint32_t() const {
        return shaderProgram;
    }

}