#ifndef GAME_FRAMEWORKS_OPENGL_RENDER_API_H
#define GAME_FRAMEWORKS_OPENGL_RENDER_API_H


#include "game_frameworks/graphics/RenderingApi.h"
#include "game_frameworks/graphics/Camera.h"
#include "game_frameworks/maths/Geometry.h"
#include "camera.h"
#include "gf_opengl/mesh/mesh_properties.h"
#include "gf_opengl/maths/transform.h"

#include <glm/glm.hpp>

namespace game_frameworks {

    struct Line {
        glm::vec2 start;
        glm::vec2 end;
        glm::vec4 color;
    };

    struct Sprite {
        glm::mat4 localTransform;
        glm::vec2 pivotPointOffset;
        glm::vec2 size;
        glm::vec4 textureCoords;
    };

    struct Quad {
        glm::vec2 pivotPointOffset;
        glm::vec2 size;
        glm::vec4 color;
    };


    class OpenGL_RenderApi {
    public:
        using CameraType = Camera2D;
        using ViewportType = ViewportProperties;
        using LineType = Line;
        using QuadType = Quad;
        using SpriteType = Sprite;
        using TransformType = Transform;

        OpenGL_RenderApi();

        void setCamera(const CameraType &camera, const ViewportType &viewport);

        void draw(const LineType &line, float lineWidth);
        void draw(const QuadType &quad, const TransformType &worldTransform) const;
        void drawWireframe(const QuadType &quad, const TransformType &worldTransform, float borderWidth) const;
//    void drawSprite(const Sprite& sprite, const glm::mat4& model, const glm::mat4& view) const;
//    void drawText() const;

    private:
        glm::mat4 cameraViewMatrix;
        glm::mat4 cameraProjectionMatrix;
        OpenGLMeshProperties quad_mesh;
    };

    static_assert(Vector2<glm::vec2>);
    static_assert(Vector3<glm::vec3>);
    static_assert(Vector4<glm::vec4>);
    static_assert(Matrix4x4<glm::mat4>);
    static_assert(LineConcept<Line>);
    static_assert(QuadConcept<Quad>);

    static_assert(LineConcept<Line>);
    static_assert(RenderingApi<OpenGL_RenderApi>);
}

#endif //GAME_FRAMEWORKS_OPENGL_RENDER_API_H
