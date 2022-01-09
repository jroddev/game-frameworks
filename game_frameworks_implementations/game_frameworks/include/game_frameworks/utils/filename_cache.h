#ifndef GAME_FRAMEWORKS_FILENAME_CACHE_H
#define GAME_FRAMEWORKS_FILENAME_CACHE_H

#include "game_frameworks/utils/entity_identifier.h"
#include <string>
#include <optional>

namespace game_frameworks {
    class FilenameCache {
        std::unordered_map<
                const EntityIdentifier,
                std::string,
                EntityIdentifier::Hasher,
                EntityIdentifier::Compare> cache;

        void addSingle(const std::string& value);
        void addRecursivePath(std::string_view path);
        std::optional<std::string_view> get(const EntityIdentifier& key) const;
    };
}

#endif //GAME_FRAMEWORKS_FILENAME_CACHE_H
