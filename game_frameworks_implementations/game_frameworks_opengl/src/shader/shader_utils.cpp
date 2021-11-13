#include "gf_opengl/shader/shader_utils.h"
#include <unordered_map>
#include <GL/glew.h>

namespace game_frameworks::shader_utils {

    using std::runtime_error;

    static const auto shaderTypeToGLType = std::unordered_map<const SHADER_TYPE, unsigned int>{ // NOLINT(cert-err58-cpp)
            {SHADER_TYPE::VERT, GL_VERTEX_SHADER},
            {SHADER_TYPE::FRAG, GL_FRAGMENT_SHADER},
    };


    uint32_t compile(const std::string& src, SHADER_TYPE shaderType) {
        const auto csrc = src.c_str();
        const auto glShaderType = shaderTypeToGLType.at(shaderType);
        auto shader = glCreateShader(glShaderType);
        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];  //NOSONAR
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw shader_build_exception(std::string{"Shader::compile::failed: "} + infoLog);
        }
        return shader;
    }

    uint32_t link(const uint32_t& vertexShader, const uint32_t& fragmentShader) {
        auto shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512]; //NOSONAR
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            throw shader_build_exception(std::string{"Shader::link::failed: "} + infoLog);
        }

        glValidateProgram(shaderProgram);
        glGetShaderiv(shaderProgram, GL_VALIDATE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            throw shader_build_exception(std::string{"Shader::validate::failed: "} + infoLog);
        }

        return shaderProgram;
    }
}