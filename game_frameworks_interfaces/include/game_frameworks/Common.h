#ifndef GAME_FRAMEWORKS_COMMON_H
#define GAME_FRAMEWORKS_COMMON_H


namespace game_frameworks {

    template<typename F>
    concept FloatingPointRef = requires {
        std::is_floating_point_v <std::remove_reference<F>>;
    };

}

#endif //GAME_FRAMEWORKS_COMMON_H
