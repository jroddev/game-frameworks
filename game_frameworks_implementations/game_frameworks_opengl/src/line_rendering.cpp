#include "gf_opengl/opengl_render_api.h"
#include <gf_opengl/shader/shader.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace game_frameworks {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        uniform mat4 view;
        uniform mat4 projection;

        uniform vec2 lineStart;
        uniform vec2 lineEnd;
        uniform vec4 inputLineColor;

        out vec4 lineColor;

        void main() {
            lineColor = inputLineColor;
            vec2 vertexPosition = mix(lineStart, lineEnd, gl_VertexID);
            vec4 worldSpacePosition = vec4(vertexPosition.x, vertexPosition.y, 0, 1);
            gl_Position = projection * view * worldSpacePosition;
        }
    )"""";

        constexpr const auto fragmentShader = R""""(
        #version 330 core
        in vec4 lineColor;
        out vec4 fragmentColor;

        void main() {
            fragmentColor = lineColor;
        }
    )"""";

        GLuint getVertexArrayObject() {
            GLuint vao;
            glGenVertexArrays(1, &vao); // glDeleteVertexArrays
            glBindVertexArray(vao);
            return vao;
        }

    }

    void OpenGL_RenderApi::draw(const Line &line, float lineWidth) const {
        static const auto shader = game_frameworks::Shader{"line-shader", std::string{vertexShader},
                                                           std::string{fragmentShader}};
        static const auto shaderId = static_cast<uint32_t>(shader);
        static const auto projectionMatrixLocation = glGetUniformLocation(shaderId, "projection");
        static const auto viewMatrixLocation = glGetUniformLocation(shaderId, "view");
        static const auto startLocation = glGetUniformLocation(shaderId, "lineStart");
        static const auto endLocation = glGetUniformLocation(shaderId, "lineEnd");
        static const auto colorLocation = glGetUniformLocation(shaderId, "inputLineColor");
        static const auto vao = getVertexArrayObject();

        //////////////////////////

        glBindVertexArray(vao);
        glUseProgram(shaderId);
        glLineWidth(lineWidth);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(this->cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(this->cameraProjectionMatrix));
        glUniform2fv(startLocation, 1, glm::value_ptr(line.start));
        glUniform2fv(endLocation, 1, glm::value_ptr(line.end));
        glUniform4fv(colorLocation, 1, glm::value_ptr(line.color));
        glDrawArrays(GL_LINES, 0, 2);
    }

}
