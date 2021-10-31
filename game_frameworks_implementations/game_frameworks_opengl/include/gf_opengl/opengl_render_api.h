#ifndef GAME_FRAMEWORKS_OPENGL_RENDER_API_H
#define GAME_FRAMEWORKS_OPENGL_RENDER_API_H

#include "game_frameworks/graphics/RenderingApi.h"
#include "game_frameworks/graphics/Camera.h"
#include "camera.h"

#include <glm/glm.hpp>

struct Line {
    glm::vec2 start;
    glm::vec2 end;
    glm::vec4 color;
};

static_assert(game_frameworks::LineConcept<Line>);

class OpenGL_RenderApi {
public:
    using CameraType = Camera2D;
    using ViewportType = ViewportProperties;
    using LineType = Line;

    void setCamera(const CameraType& camera, const ViewportType& viewport);
    void drawLine(const LineType& line, float lineWidth);
    void drawSprite();
    void drawText();

private:
    glm::mat4 cameraViewMatrix;
    glm::mat4 cameraProjectionMatrix;
};

static_assert(game_frameworks::RenderingApi<OpenGL_RenderApi>);

#endif //GAME_FRAMEWORKS_OPENGL_RENDER_API_H
