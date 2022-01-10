#include "gtest/gtest.h"
#include "dummy/dummy.h"
#include "game_frameworks/utils/filename_cache.h"
#include "game_frameworks/utils/entity_identifier.h"

#include <filesystem>
#include <fstream>
#include <iostream>

void createFile(const std::string& path, const std::string_view content) {
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
    auto file = std::ofstream{path};
    file << content;
    file.close();
}


TEST(FilenameCache, CacheSingle) {
    auto file = dummy<std::string>(5);
    auto cache = game_frameworks::FilenameCache{};
    EXPECT_EQ(cache.get(game_frameworks::EntityIdentifier(file)), std::optional<std::string_view>{});
    cache.addSingle(file);
    EXPECT_EQ(cache.get(game_frameworks::EntityIdentifier(file)), std::optional<std::string_view>{file});
}

TEST(FilenameCache, CacheRecursiveDir) {
    namespace fs = std::filesystem;
    const auto tmpDir = fs::path("/tmp/" + dummy<std::string>(5));
    fs::create_directory(tmpDir);

    auto fileCount = dummy<int>(3, 10);
    auto files = std::vector<std::string>{};
    for(int i = 0; i < fileCount; i++) {
        auto file = tmpDir.generic_string() + "/" + dummy<std::string>(5) + "/" + dummy<std::string>(5);
        createFile(file, dummy<std::string>(256));
        files.push_back(file);
    }

    auto cache = game_frameworks::FilenameCache{};
    EXPECT_EQ(cache.getCacheCount(), 0);
    cache.addRecursivePath(tmpDir.generic_string());

    auto all = cache.getAllCachedValues();
    EXPECT_EQ(cache.getCacheCount(), fileCount);

    for(const auto& file : files) {
        EXPECT_EQ(
                cache.get(game_frameworks::EntityIdentifier(file)),
                std::optional<std::string_view>{file});
    }

    fs::remove_all(tmpDir);
}