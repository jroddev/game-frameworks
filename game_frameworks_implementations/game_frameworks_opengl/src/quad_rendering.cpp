#include "gf_opengl/opengl_render_api.h"
#include <gf_opengl/shader/shader.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace game_frameworks {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform vec2 pivotPointOffset;
        uniform vec2 size;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec4 color;

        out vec4 outputColor;

        void main() {
            outputColor = color;
            gl_Position = projection * view * model * vec4((aPos + pivotPointOffset) * size, 0.0, 1.0);
        }
    )"""";

        constexpr const auto fragmentShader = R""""(
        #version 330 core
        in vec4 outputColor;
        out vec4 fragmentColor;

        void main() {
            fragmentColor = outputColor;
        }
    )"""";

    }

    void OpenGL_RenderApi::draw(const QuadType &quad, const TransformType &worldTransform) const {
        static const auto shader = game_frameworks::Shader{"quad-wireframe-shader", std::string{vertexShader},
                                                           std::string{fragmentShader}};
        static const auto shaderId = static_cast<uint32_t>(shader);
        static const auto pivotPointOffsetLocation = glGetUniformLocation(shaderId, "pivotPointOffset");
        static const auto sizeLocation = glGetUniformLocation(shaderId, "size");
        static const auto modelMatrixLocation = glGetUniformLocation(shaderId, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shaderId, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shaderId, "projection");
        static const auto colorLocation = glGetUniformLocation(shaderId, "color");

        //////////////////////////

        glBindVertexArray(quad_mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_mesh.ebo);
        glUseProgram(shaderId);
        glUniform2fv(pivotPointOffsetLocation, 1, glm::value_ptr(quad.pivotPointOffset));
        glUniform2fv(sizeLocation, 1, glm::value_ptr(quad.size));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransform.toMatrix()));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraProjectionMatrix));
        glUniform4fv(colorLocation, 1, glm::value_ptr(quad.color));
        glDrawElements(GL_TRIANGLES, quad_mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGL_RenderApi::drawWireframe(const QuadType &quad, const TransformType &worldTransform,
                                         float borderWidth) const {
        static const auto shader = game_frameworks::Shader{"quad-wireframe-shader", std::string{vertexShader},
                                                           std::string{fragmentShader}};
        static const auto shaderId = static_cast<uint32_t>(shader);
        static const auto pivotPointOffsetLocation = glGetUniformLocation(shaderId, "pivotPointOffset");
        static const auto sizeLocation = glGetUniformLocation(shaderId, "size");
        static const auto modelMatrixLocation = glGetUniformLocation(shaderId, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shaderId, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shaderId, "projection");
        static const auto colorLocation = glGetUniformLocation(shaderId, "color");

        //////////////////////////

        glBindVertexArray(quad_mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_mesh.ebo);
        glUseProgram(shaderId);
        glLineWidth(borderWidth);
        glUniform2fv(pivotPointOffsetLocation, 1, glm::value_ptr(quad.pivotPointOffset));
        glUniform2fv(sizeLocation, 1, glm::value_ptr(quad.size));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransform.toMatrix()));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraProjectionMatrix));
        glUniform4fv(colorLocation, 1, glm::value_ptr(quad.color));
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}