#include "game_frameworks/utils/filename_cache.h"
#include <filesystem>

namespace game_frameworks {

    std::optional<std::string_view> FilenameCache::get(const EntityIdentifier &key) const {
        if (const auto entry = cache.find(key); entry != cache.end()) {
            return entry->second;
        }
        return {};
    }

    void FilenameCache::addSingle(const std::string& value) {
        cache[EntityIdentifier{value}] = value;
    }

    void FilenameCache::addRecursivePath(std::string_view path) {
        for (const auto& file : std::filesystem::recursive_directory_iterator{path}) {
            addSingle(file.path());
        }
    }
}