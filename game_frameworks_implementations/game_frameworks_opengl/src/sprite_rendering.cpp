#include "gf_opengl/opengl_render_api.h"
#include <gf_opengl/shader/shader.h>
#include <gf_opengl/texture.h>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

namespace game_frameworks {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;

        uniform vec2 pivotPointOffset;
        uniform vec2 size;
        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec4 colorTint;
        uniform vec2 textureRegionOffset;
        uniform vec2 textureRegionSize;

        out vec4 textureColorTint;
        out vec2 textureCoord;

        void main() {
            textureCoord = textureRegionOffset + (aTexCoord * textureRegionSize);
            textureColorTint = colorTint;
            gl_Position = projection * view * model * vec4((aPos + pivotPointOffset) * size, 0.0, 1.0);
        }
    )"""";

        constexpr const auto fragmentShader = R""""(
        #version 330 core
        in vec2 textureCoord;
        in vec4 textureColorTint;
        uniform sampler2D textureSampler;

        out vec4 fragmentColor;

        void main() {
            vec4 textureColor = texture(textureSampler, textureCoord);
            fragmentColor = textureColor * textureColorTint;
        }
    )"""";

        inline void prepareSpriteDrawCall(
                const OpenGLMeshProperties& mesh,
                const OpenGL_RenderApi::SpriteType& sprite,
                const Texture& texture,
                const OpenGL_RenderApi::TransformType& worldTransform,
                const glm::mat4& cameraViewMatrix,
                const glm::mat4& cameraProjectionMatrix) {
            static const auto shader = game_frameworks::Shader{"quad-wireframe-shader", std::string{vertexShader},
                                                               std::string{fragmentShader}};
            static const auto shaderId = static_cast<uint32_t>(shader);
            static const auto pivotPointOffsetLocation = glGetUniformLocation(shaderId, "pivotPointOffset");
            static const auto sizeLocation = glGetUniformLocation(shaderId, "size");
            static const auto modelMatrixLocation = glGetUniformLocation(shaderId, "model");
            static const auto viewMatrixLocation = glGetUniformLocation(shaderId, "view");
            static const auto projectionMatrixLocation = glGetUniformLocation(shaderId, "projection");
            static const auto colorTintLocation = glGetUniformLocation(shaderId, "colorTint");
            static const auto textureRegionOffsetLocation = glGetUniformLocation(shaderId, "textureRegionOffset");
            static const auto textureRegionSizeLocation = glGetUniformLocation(shaderId, "textureRegionSize");

            texture.bind();

            //////////////////////////

            glBindVertexArray(mesh.vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
            glUseProgram(shaderId);
            glUniform2fv(pivotPointOffsetLocation, 1, glm::value_ptr(sprite.pivotPointOffset));
            glUniform2fv(sizeLocation, 1, glm::value_ptr(sprite.size));
            glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(worldTransform.toMatrix()));
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraViewMatrix));
            glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(cameraProjectionMatrix));
            glUniform4fv(colorTintLocation, 1, glm::value_ptr(sprite.textureColorTint));
            glUniform2fv(textureRegionOffsetLocation, 1, glm::value_ptr(glm::vec2{sprite.textureRegionOffset.x, sprite.textureRegionOffset.y}));
            glUniform2fv(textureRegionSizeLocation, 1, glm::value_ptr(glm::vec2{sprite.textureRegionSize.x, sprite.textureRegionSize.y}));
        }
    }

    void OpenGL_RenderApi::draw(const SpriteType &sprite, const TransformType &worldTransform) const {
        auto& texture = tryLoadTexture(sprite.textureId, textures);
        prepareSpriteDrawCall(quad_mesh, sprite, texture, worldTransform, cameraViewMatrix, cameraProjectionMatrix);
        glDrawElements(GL_TRIANGLES, quad_mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGL_RenderApi::drawWireframe(const SpriteType &sprite, const TransformType &worldTransform,
                                         float borderWidth) const {
        auto& texture = tryLoadTexture(sprite.textureId, textures);
        prepareSpriteDrawCall(quad_mesh, sprite, texture, worldTransform, cameraViewMatrix, cameraProjectionMatrix);
        glLineWidth(borderWidth);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}