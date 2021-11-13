#ifndef GAME_FRAMEWORKS_CAMERA_H
#define GAME_FRAMEWORKS_CAMERA_H

#include <game_frameworks/graphics/Camera.h>
#include <glm/glm.hpp>

struct Camera2D {
    glm::vec2 position = {0.F, 0.F};
    float rotation = 0.F;
    float zoom = 1.F;
};

struct ViewportProperties {
    glm::vec2 size;
    game_frameworks::UP_AXIS up;
};

static_assert(game_frameworks::Camera2DConcept<Camera2D>);
static_assert(game_frameworks::ViewportPropertiesConcept<ViewportProperties>);

#endif //GAME_FRAMEWORKS_CAMERA_H
