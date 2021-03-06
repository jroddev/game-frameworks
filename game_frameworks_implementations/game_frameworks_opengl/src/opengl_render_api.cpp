#include "gf_opengl/opengl_render_api.h"
#include "gf_opengl/mesh/mesh_quad.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace game_frameworks {

    void OpenGL_RenderApi::setCamera(const Camera2D &camera, const ViewportProperties &viewport) {
        static const constexpr auto identityMatrix = glm::mat4{1.0f};

        const auto halfWidth = (viewport.size.x * camera.zoom) / 2.f;
        const auto halfHeight = (viewport.size.y * camera.zoom) / 2.f;
        const auto up = static_cast<float>(viewport.up);
        this->cameraProjectionMatrix = glm::ortho(
                -halfWidth,
                halfWidth,
                -up * halfHeight,
                up * halfHeight,
                -100.f,
                100.0f);

        const auto T = glm::translate(identityMatrix, {-camera.position.x, camera.position.y, 0.F});
        const auto R = glm::eulerAngleYXZ(0.F, 0.F, glm::radians(camera.rotation));
        this->cameraViewMatrix = T * R;
    }



    OpenGL_RenderApi::OpenGL_RenderApi() :
            cameraViewMatrix(),
            cameraProjectionMatrix(){

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);

        textures.try_emplace(EntityIdentifier{"black"}, Texture{{
            static_cast<char>(0),
            static_cast<char>(0),
            static_cast<char>(0),
            static_cast<char>(255)}});
        textures.try_emplace(EntityIdentifier{"white"}, Texture{{
            static_cast<char>(255),
            static_cast<char>(255),
            static_cast<char>(255),
            static_cast<char>(255)}});
    }

    void OpenGL_RenderApi::loadTexture(const std::string_view texturePath) {
        const auto textureId = EntityIdentifier{texturePath};
        textures.try_emplace(textureId, Texture{texturePath});
    }

    void OpenGL_RenderApi::unloadTexture(const std::string_view texturePath) {
        const auto textureId = EntityIdentifier{texturePath};
        textures.erase(textureId);
    }

    void OpenGL_RenderApi::unloadAllTextures() {
        textures.clear();
    }

}