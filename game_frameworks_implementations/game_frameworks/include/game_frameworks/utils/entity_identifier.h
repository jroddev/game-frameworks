#ifndef GAME_FRAMEWORKS_ENTITYIDENTIFIER_H
#define GAME_FRAMEWORKS_ENTITYIDENTIFIER_H

#include <concepts>
#include <functional>
#include <string_view>
#include "game_frameworks/interfaces/utils/EntityIdentifier.h"

namespace game_frameworks {

    struct EntityIdentifier {
        using KeyType = size_t;
        KeyType hash;
        explicit EntityIdentifier(const std::string_view name) :
                hash(std::hash<std::string_view>()(name)) {
        }

        constexpr bool operator==(const EntityIdentifier &other) const = default;

        constexpr explicit operator KeyType() const {
            return hash;
        }

        struct Compare {
            constexpr bool operator()(const EntityIdentifier &a, const EntityIdentifier &b) const {
                return static_cast<EntityIdentifier::KeyType>(a) == static_cast<EntityIdentifier::KeyType>(b);
            }
        };

        struct Hasher {
            constexpr size_t operator()(EntityIdentifier const &key) const {
                return static_cast<size_t>(key);
            }
        };
    };

    static_assert(game_frameworks::EntityIdentifierConcept<EntityIdentifier>);
}

#endif //GAME_FRAMEWORKS_ENTITYIDENTIFIER_H
