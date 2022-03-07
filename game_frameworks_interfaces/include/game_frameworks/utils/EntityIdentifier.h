#ifndef GAME_FRAMEWORKS_ENTITYIDENTIFIERCONCEPT_H
#define GAME_FRAMEWORKS_ENTITYIDENTIFIERCONCEPT_H

#include <concepts>
#include <iterator>
#include "game_frameworks/Common.h"

namespace game_frameworks {

    template<typename ID>
    concept EntityIdentifierConcept =
        std::is_invocable_v<
            const typename ID::Compare,
            const ID &,
            const ID &> &&
        std::is_invocable_v<
            const typename ID::Hasher,
            const ID> &&
        requires(ID entityId) {
        { entityId.hash } -> IntegralRef;
    };

    template<typename ID>
    concept EntityIdentifierConceptRef = requires {
        EntityIdentifierConcept <std::remove_reference<ID>>;
    };
}

#endif //GAME_FRAMEWORKS_ENTITYIDENTIFIERCONCEPT_H
