#ifndef GAME_FRAMEWORKS_OPENGL_RENDER_API_H
#define GAME_FRAMEWORKS_OPENGL_RENDER_API_H


#include "game_frameworks/graphics/RenderingApi.h"
#include "game_frameworks/graphics/Camera.h"
#include "game_frameworks/maths/Geometry.h"
#include "camera.h"

#include <glm/glm.hpp>

struct Line {
    glm::vec2 start;
    glm::vec2 end;
    glm::vec4 color;
};

class OpenGL_RenderApi {
public:
    using CameraType = Camera2D;
    using ViewportType = ViewportProperties;
    using LineType = Line;

    void setCamera(const CameraType& camera, const ViewportType& viewport);
    void drawLine(const LineType& line, float lineWidth);
    void drawSprite() const;
    void drawText() const;

private:
    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;
};

namespace game_frameworks {
    static_assert(Vector2<glm::vec2>);
    static_assert(Vector3<glm::vec3>);
    static_assert(Vector4<glm::vec4>);
    static_assert(Matrix4x4<glm::mat4>);

    static_assert(game_frameworks::LineConcept<Line>);
    static_assert(game_frameworks::RenderingApi<OpenGL_RenderApi>);
}

#endif //GAME_FRAMEWORKS_OPENGL_RENDER_API_H
