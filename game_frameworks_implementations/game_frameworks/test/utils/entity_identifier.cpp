#include "gtest/gtest.h"
#include "dummy/dummy.h"
#include "game_frameworks/utils/entity_identifier.h"

TEST(EntityIdentifier, SameStringGeneratesSameId) {
    const auto str = dummy<std::string>(10);
    EXPECT_EQ(
            game_frameworks::EntityIdentifier{str},
            game_frameworks::EntityIdentifier{str}
            );
}