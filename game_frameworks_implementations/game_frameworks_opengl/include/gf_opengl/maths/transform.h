#ifndef GAME_FRAMEWORKS_TRANSFORM_H
#define GAME_FRAMEWORKS_TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace game_frameworks {

    struct Transform {
        using MatrixType = glm::mat4;

        static const constexpr MatrixType identityMatrix = glm::mat4{1.0f};
        glm::vec3 position = glm::vec3{0.0f};
        glm::vec3 rotation = glm::vec3{0.0f};
        glm::vec3 scale = glm::vec3{1.0f};

        [[nodiscard]] MatrixType toMatrix() const noexcept {
            const auto T = glm::translate(identityMatrix, position);
            const auto R = glm::eulerAngleYXZ(
                    glm::radians(rotation.y),
                    glm::radians(rotation.x),
                    glm::radians(rotation.z));
            const auto S = glm::scale(identityMatrix, scale);
            return T * R * S;
        }

        static Transform from(float x, float y, float rot, float width, float height) {
            return Transform{
                    {x,     y,      0.f},
                    {0.f,   0.f,    rot},
                    {width, height, 1.f}
            };
        }

        static Transform from(const MatrixType& matrix) {
            glm::vec3 scale;
            glm::quat rotation;
            glm::vec3 translation;
            glm::vec3 skew;
            glm::vec4 perspective;
            glm::decompose(matrix, scale, rotation, translation, skew, perspective);
            glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(rotation));
            return {
                    .position = translation,
                    .rotation = eulerRotation,
                    .scale = scale
            };
        }

        static Transform multi(const Transform& parent, const Transform& child) {
            return Transform::from(parent.toMatrix() * child.toMatrix());
        }
    };

    static_assert(Matrix4x4 < Transform::MatrixType > );
}
#endif //GAME_FRAMEWORKS_TRANSFORM_H
