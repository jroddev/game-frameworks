#ifndef GAME_FRAMEWORKS_GEOMETRY_H
#define GAME_FRAMEWORKS_GEOMETRY_H

#include <concepts>

namespace game_frameworks {

    template<typename F>
    concept FloatingPointRef = requires {
        std::is_floating_point_v<std::remove_reference<F>>;
    };

    template<typename V>
    concept Vector2 = requires(V v) {
        { v.x } -> FloatingPointRef;
        { v.y } -> FloatingPointRef;
    };

    template<typename V>
    concept Vector3 = requires(V v) {
        { v.x } -> FloatingPointRef;
        { v.y } -> FloatingPointRef;
        { v.z } -> FloatingPointRef;
    };


    namespace {                         //NOSONAR
        struct V2 { float x,y; };       //NOSONAR
        static_assert(Vector2<V2>);

        struct V3 { double x,y,z; };    //NOSONAR
        static_assert(Vector3<V3>);
    }
}
#endif //GAME_FRAMEWORKS_GEOMETRY_H

