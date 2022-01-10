#include "game_frameworks/utils/filename_cache.h"
#include <filesystem>

namespace game_frameworks {

    size_t FilenameCache::getCacheCount() const {
        return cache.size();
    }

    std::vector<std::string> FilenameCache::getAllCachedValues() const {
        auto output = std::vector<std::string>();
        output.reserve(cache.size());
        for(const auto& [key, value] : cache) {
            output.emplace_back(value);
        }
        return output;
    }

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
            if (file.is_regular_file()) // exclude directories
                addSingle(file.path());
        }
    }
}