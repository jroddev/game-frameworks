#include "gf_opengl/opengl_render_api.h"
#include <gf_opengl/shader/shader.h>
#include <gf_opengl/texture.h>
#include <GL/glew.h>
#include <numeric>

namespace game_frameworks {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 460 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;

        layout(std140, binding = 0) uniform PerFrameData {
            mat4 viewMatrix;
            mat4 projectionMatrix;
        };

        struct InstanceData {
            vec2 pivotPointOffset;
            vec2 size;
            vec4 textureRegion;
            vec4 colorTint;
            mat4 modelMatrix;
        };

        layout(std140, binding = 1) restrict readonly buffer PerInstanceData {
            InstanceData instanceData[];
        };

        out vec4 textureColorTint;
        out vec2 textureCoord;

        void main() {
            InstanceData instance = instanceData[gl_InstanceID];
            mat4 mvp =  projectionMatrix * viewMatrix * instance.modelMatrix;
            gl_Position = mvp * vec4((aPos + instance.pivotPointOffset) * instance.size, 0.0, 1.0);
            textureCoord = instance.textureRegion.xy + (aTexCoord * instance.textureRegion.zw);
            textureColorTint = instance.colorTint;
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


        GLuint createBufferHandle(std::size_t numberOfBytes) {
            GLuint handle;
            auto placeholder = std::vector<char>();
            placeholder.resize(numberOfBytes);
            std::iota(placeholder.begin(), placeholder.end(), 1);
            glCreateBuffers(1, &handle);
            glNamedBufferStorage(handle, static_cast<long>(numberOfBytes), placeholder.data(), GL_DYNAMIC_STORAGE_BIT);
            return handle;
        }

        void prepareInstancedSprite(
                const Texture& texture,
                const PerFrameData& perFrameData,
                const OpenGLMeshProperties& mesh,
                const void* instanceData, //NOSONAR
                const int instanceDataCount
                ) {
            static const auto shader = game_frameworks::Shader{
                    "sprite-shader",
                    std::string{vertexShader},
                    std::string{fragmentShader}
            };
            static const auto shaderId = static_cast<uint32_t>(shader);

            const auto instanceDataSize = static_cast<int>(instanceDataCount * sizeof(PerInstanceData));
            static const auto PER_FRAME_SIZE = sizeof(PerFrameData);
            static const auto MAX_BATCH_SIZE = 128;

            static GLuint perFrameDataBuffer = createBufferHandle(PER_FRAME_SIZE);
            glNamedBufferSubData(perFrameDataBuffer, 0, PER_FRAME_SIZE, &perFrameData);

            static GLuint perInstanceDataBuffer = createBufferHandle(sizeof(PerInstanceData) * MAX_BATCH_SIZE);
            glNamedBufferSubData(perInstanceDataBuffer, 0, instanceDataSize, instanceData);

            texture.bind();

            glBindVertexArray(mesh.vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, perFrameDataBuffer);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, perInstanceDataBuffer);
            glUseProgram(shaderId);
        }

    }

    void OpenGL_RenderApi::draw(const EntityIdentifier& textureId,
                                const PerInstanceData& instance) const {
        const auto perFrameData = PerFrameData{
                .view{cameraViewMatrix},
                .projection{cameraProjectionMatrix}
        };
        const auto& texture = tryLoadTexture(textureId, textures);
        prepareInstancedSprite(texture, perFrameData, quad_mesh, &instance, 1);
        glDrawElementsInstanced(GL_TRIANGLES, quad_mesh.indicesSize, GL_UNSIGNED_INT, nullptr, 1);
    }

    void OpenGL_RenderApi::drawWireframe(
            const std::vector<PerInstanceData>& instances,
            float borderWidth) const {

        glLineWidth(borderWidth);
        const auto perFrameData = PerFrameData{
                .view{cameraViewMatrix},
                .projection{cameraProjectionMatrix}
        };
        const auto& texture = tryLoadTexture(EntityIdentifier{"white"}, textures);

        // TODO: may be able to batch this using glMultiDrawArrays
        for(const auto& instance: instances) {
            prepareInstancedSprite(texture, perFrameData, quad_mesh, &instance, 1);
            glDrawArrays(GL_LINE_LOOP, 0, 4);
        }
    }

    void OpenGL_RenderApi::drawInstanced(
            const EntityIdentifier& textureId,
            const std::vector<PerInstanceData>& instances) const {

        const auto perFrameData = PerFrameData{
                .view{cameraViewMatrix},
                .projection{cameraProjectionMatrix}
        };
        const auto instanceCount = static_cast<int>(instances.size());
        const auto& texture = tryLoadTexture(textureId, textures);
        prepareInstancedSprite(texture, perFrameData, quad_mesh, instances.data(), instanceCount);
        glDrawElementsInstanced(GL_TRIANGLES, quad_mesh.indicesSize, GL_UNSIGNED_INT, nullptr, instanceCount);
    }

}