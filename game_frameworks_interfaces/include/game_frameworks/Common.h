#ifndef GAME_FRAMEWORKS_COMMON_H
#define GAME_FRAMEWORKS_COMMON_H


namespace game_frameworks {

    consteval auto stripConst(const auto& value) {
        // Only used as a workaround for concepts
        return const_cast<std::remove_const_t<typeof value>&>(value); //NOSONAR
    }

    template<typename F>
    concept FloatingPointRef = requires {
        std::is_floating_point_v <std::remove_reference<F>>;
    };

    template<typename F>
    concept IntegralRef = requires {
        std::is_integral_v <std::remove_reference<F>>;
    };

}

#endif //GAME_FRAMEWORKS_COMMON_H
