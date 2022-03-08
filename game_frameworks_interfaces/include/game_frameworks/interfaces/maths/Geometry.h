#ifndef GAME_FRAMEWORKS_GEOMETRY_H
#define GAME_FRAMEWORKS_GEOMETRY_H

#include <concepts>
#include <game_frameworks/interfaces/Common.h>

namespace game_frameworks {

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

    template<typename V>
    concept Vector4 = requires(V v) {
        { v.x } -> FloatingPointRef;
        { v.y } -> FloatingPointRef;
        { v.z } -> FloatingPointRef;
        { v.w } -> FloatingPointRef;
    };

    template<typename R>
    concept Rect = requires(R r) {
        { r.x } -> FloatingPointRef;
        { r.y } -> FloatingPointRef;
        { r.w } -> FloatingPointRef;
        { r.h } -> FloatingPointRef;
    };

    template<typename M>
    concept Matrix4x4 = requires(M m, float f) {
        { M(f) } -> std::same_as<M>;
    };

    template<typename T>
    concept TransformConcept =
            Matrix4x4<typename T::MatrixType> &&
            requires(T t, float f, typename T::MatrixType m) {
        { t.toMatrix() } -> Matrix4x4;
        { T::from(m) } -> std::same_as<T>;
        { T::from(f,f,f,f,f)} -> std::same_as<T>;
        { T::multi(t, t)} -> std::same_as<T>;
    };


    namespace {                         //NOSONAR
        struct V2 { float x,y; };       //NOSONAR
        static_assert(Vector2<V2>);

        struct V3 { double x,y,z; };    //NOSONAR
        static_assert(Vector3<V3>);

        struct V4 { double x,y,z,w; };    //NOSONAR
        static_assert(Vector3<V4>);
    }
}
#endif //GAME_FRAMEWORKS_GEOMETRY_H

